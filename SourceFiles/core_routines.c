///////////////////////////////////
// University: UoA DIT
// Course : [K23a] Software Development for Computer Systems
// Semester : Fall 2021-2022
// Professor : Yannis Ioannidis 
// Assistant : Sarantis Paskalis
// --------------------------------
// Students: Stylianos Oikonomou , Anastasios Triantafyllou
// ID : 1115201500243 , 1115201600173 
// --------------------------------
// File : core_routines.c
///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>

#include "LinkedList.h"
#include "BKTree.h"
#include "HashTable.h"

#include "Scheduler.h"
#include "core_routines.h"

#include "constructors.h"
#include "common_types.h"
#include "core.h"

#define MAX_DISTANCE 3

extern Index INDEX;
extern JobScheduler JOB_SCHEDULER;

void *MatchDocument_routine(void *args){

    if(args == NULL) return NULL;

    unsigned int offset = 0;
    int thread_flag = *(int *)(args+offset);
    offset += sizeof(int *);

    DocID doc_id = *(DocID *)(args+offset);
    offset += sizeof(DocID);

    char *doc_str = (char *)malloc(sizeof(char) * (strlen((char *)(args+offset)) + 1));
    strcpy(doc_str, (char *)(args+offset));

    free(args);

    //Process:
    //Read every query's type and distance and apply search for every word in the document
    //that matches those parameters and save the results
    //Check to see if an exact same lookup has been done before by an earlier query
    //and skip redoing it, link that query's results to the one's with the same search parameters
    
    //Will be used to iterate all queries, checked first because there is no
    //point in continuing if this information is invalid
    unsigned int qcount = LL_GetSize(INDEX.query_list);
    LLNode query_node = LL_GetHead(INDEX.query_list);
    if(!query_node) return NULL;

    //Tokenize and deduplicate document string
    HashTable doc_words_ht = HT_Create(StringType, &djb2, NULL, &compareString);
    if(!doc_words_ht) return NULL;

    char token[MAX_WORD_LENGTH + 1], *word = NULL;
    int i = 0;
    while(1){
        // Create document word
        if (*doc_str != ' ' && *doc_str) {
            token[i++] = *doc_str++;
            continue;
        }
        token[i] = '\0';

        word = (char *)malloc((i + 1) * sizeof(char ));     // i = length of the word
        if (!word) { HT_Destroy(doc_words_ht); return NULL; }
        strcpy(word, token);
        
        if (!HT_InsertUnique(doc_words_ht, (Pointer )word)) { free(word); HT_Destroy(doc_words_ht); return NULL; }

        i = 0;  // Reset the word index
        if (*doc_str) doc_str++; else break;
    }

    LList doc_words = HT_ToList(doc_words_ht, &destroyString);
    HT_Destroy(doc_words_ht);
    
    //Definitions and allocations of helper structures
    HashTable res_exact = NULL;
    HashTable *res_edit = (HashTable *)malloc((MAX_DISTANCE) * sizeof(LList));
    if (!res_edit) { LL_Destroy(doc_words); return NULL; }
    HashTable **res_hamm = (HashTable **)malloc((MAX_DISTANCE) * sizeof(LList *));
    if (!res_hamm) { free(res_edit); LL_Destroy(doc_words); return NULL; }

    int j = 0;
    for (i = 0; i < MAX_DISTANCE; i++) {
        res_edit[i] = NULL;
        res_hamm[i] = (HashTable *)malloc((MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1) * sizeof(LList));
        if (!res_hamm[i]){
            for (j = i; j > 0; j--){
                free(res_hamm[j-1]);
            }
            free(res_edit);
            free(res_hamm);
            LL_Destroy(doc_words);
            return NULL;
        }
        for (j = 0; j < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; j++) res_hamm[i][j] = NULL;
    }
    //The above code initializes 3 helper structures to save every query calculation
    //based on match_distance and match_type; res_exact is only used when match_distance
    //is 0. The above allocations are as follows: A single list for exact match results,
    //One list for each different distance value for edit distance queries
    //And one list for every distance value for every word length for hamming distance queries.

    //They are initlalized as NULL and created mid-search if needed, reason being
    //the NULL value denotes a calculation of the corresponding cell has not been
    //yet executed. The alternative of an empty list cannot be trusted, as
    //a query can return an empty list of results after execution.

    //Another helper structure to save result query ids in
    LList res_ids = LL_Create(UIntType, &destroyUInt, &compareUInt);

    //Start of query iterations
    while (qcount--){

        Query q = (Query )(query_node->data);
        if (q->active){
            MatchType mt = q->match_type;
            unsigned int md = q->match_dist;
            QueryID id = q->query_id;
            LList qw = q->query_words;

            //Flagging which structures are to be initialized and searched and which are not
            //Flags can be implemented way more efficiently than this
            char exact_flag, edit_flag[MAX_DISTANCE], hamm_flag[MAX_DISTANCE], flag = 1;
            switch(mt){
                case MT_EXACT_MATCH:
                    exact_flag = (!res_exact) ? 1 : 0;
                    flag = exact_flag;
                    break;
                case MT_HAMMING_DIST:
                    for (i = 0; i < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; i++){
                        if (res_hamm[md-1][i]) break;
                    }
                    hamm_flag[md-1]= (i == MAX_WORD_LENGTH-MIN_WORD_LENGTH+1) ? 1 : 0;
                    flag = hamm_flag[md-1];
                    break;
                case MT_EDIT_DIST:
                    edit_flag[md-1] = (!res_edit[md-1]) ? 1 : 0;
                    flag = edit_flag[md-1];
                    break;
                default:
                    //Destroy all lists
                    for (i = 0; i < MAX_DISTANCE; i++) {
                        HT_Destroy(res_edit[i]);
                        for(j = 0; j < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; j++){
                            HT_Destroy(res_hamm[i][j]);
                        }
                        free(res_hamm[i]);
                    }
                    free(res_edit);
                    free(res_hamm);
                    HT_Destroy(res_exact);
                    LL_Destroy(doc_words);
                    LL_Destroy(res_ids);
                    return NULL;
            }

            LLNode doc_node = LL_GetHead(doc_words);
            while(doc_node && flag){
                word = (char *)(doc_node->data);
                //If already searched, skip re-searching and mimic post search functionality of previous clone query based on words
                switch(mt){
                    case MT_EXACT_MATCH:
                        if (exact_flag){
                            if (!res_exact) res_exact = HT_Create(EntryType, &djb2, NULL, &compareEntry);
                            //Start the search
                            LLNode temp = HT_Search(INDEX.exact_match_ht, word);
                            if (temp) HT_Insert(res_exact, (Pointer)(temp->data));
                        }
                        break;
                    case MT_HAMMING_DIST:
                        if (hamm_flag[md-1]){
                            if (!res_hamm[md-1][strlen(word)-MIN_WORD_LENGTH]) res_hamm[md-1][strlen(word)-MIN_WORD_LENGTH] = HT_Create(EntryType, &djb2, NULL, &compareEntry);
                            //Commence the investigation and merge lists
                            HT_InsertFromList(res_hamm[md-1][strlen(word)-MIN_WORD_LENGTH], BKT_Search(INDEX.hamming_distance_bkt[strlen(word)-MIN_WORD_LENGTH], word, md));
                        }
                        break;
                    case MT_EDIT_DIST:
                        if (edit_flag[md-1]){
                            if (!res_edit[md-1]) res_edit[md-1] = HT_Create(EntryType, &djb2, NULL, &compareEntry);
                            //Let the query begin and join lists
                            HT_InsertFromList(res_edit[md-1], BKT_Search(INDEX.edit_distance_bkt, word, md));
                        }
                        break;
                    default:
                        //Destroy all lists
                        for (i = 0; i < MAX_DISTANCE; i++) {
                            HT_Destroy(res_edit[i]);
                            for(j = 0; j < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; j++){
                                HT_Destroy(res_hamm[i][j]);
                            }
                            free(res_hamm[i]);
                        }
                        free(res_edit);
                        free(res_hamm);
                        HT_Destroy(res_exact);
                        LL_Destroy(doc_words);
                        LL_Destroy(res_ids);
                        return NULL;
                }

                doc_node = LL_Next(doc_words, doc_node);
            }

            //Time to check if query belongs to the results of the document
            //If query was successful, save it to res_ids

            Entry temp = NULL;
            LLNode q_word_node = LL_GetHead(qw);
            unsigned int hits = LL_GetSize(qw);
            while(q_word_node){
                temp = LL_GetValue(q_word_node);
                word = temp->word;
                switch(mt){
                    case MT_EXACT_MATCH:
                        if (HT_Search(res_exact, (Pointer) word)) hits--;
                        break;
                    case MT_HAMMING_DIST:
                        if (HT_Search(res_hamm[md-1][strlen(word)-MIN_WORD_LENGTH], (Pointer) word)) hits--;
                        break;
                    case MT_EDIT_DIST:
                        if (HT_Search(res_edit[md-1], (Pointer) word)) hits--;
                        break;
                    default:
                        //Destroy all lists
                        for (i = 0; i < MAX_DISTANCE; i++) {
                            HT_Destroy(res_edit[i]);
                            for(j = 0; j < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; j++){
                                HT_Destroy(res_hamm[i][j]);
                            }
                            free(res_hamm[i]);
                        }
                        free(res_edit);
                        free(res_hamm);
                        HT_Destroy(res_exact);
                        LL_Destroy(doc_words);
                        LL_Destroy(res_ids);
                        return NULL;
                }
                q_word_node = LL_Next(qw, q_word_node);
            }
            if (!hits) LL_InsertTail(res_ids, createUInt(id));
        }

        query_node = LL_Next(INDEX.query_list, query_node);
    }

    //Save doc_id, res_ids->size and res_ids contents in INDEX.result_list

    LL_InsertTail(INDEX.result_list, (Pointer)createQueryResult(doc_id, LL_GetSize(res_ids), (unsigned int *)LL_ToArray(res_ids)));

    //Free all allocated memory
    
    for (i = 0; i < MAX_DISTANCE; i++) {
        HT_Destroy(res_edit[i]);
        for(j = 0; j < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; j++){
            HT_Destroy(res_hamm[i][j]);
        }
        free(res_hamm[i]);
    }
    free(res_edit);
    free(res_hamm);
    HT_Destroy(res_exact);
    LL_Destroy(doc_words);
    LL_Destroy(res_ids);

    printf("Exiting MatchDocument | doc_id = %d\n", doc_id);

    JOB_SCHEDULER->active_threads_flags[thread_flag] = 0;           // Set thread flag to 0, indicates that the thread id is inactive

    pthread_mutex_lock(&(JOB_SCHEDULER->mutex_thread_count));
    JOB_SCHEDULER->active_threads_count--;                          // Reduces the active thread count
    pthread_mutex_unlock(&(JOB_SCHEDULER->mutex_thread_count));

    pthread_cond_signal(&(JOB_SCHEDULER->cond_threads));           // Signal the JobScheduler that a thread has finished its excecution

    return NULL;
}