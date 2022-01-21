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
// File : core.c
///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "LinkedList.h"
#include "BKTree.h"
#include "HashTable.h"

#include "constructors.h"
#include "common_types.h"
#include "core.h"

#define MAX_DISTANCE 3

static Index INDEX;

ErrorCode InitializeIndex(){

    INDEX.exact_match_ht = HT_Create(EntryType, &djb2, NULL, &compareEntry);
    int i;
    for(i = 0; i < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; i++)
        INDEX.hamming_distance_bkt[i] = BKT_Create(MT_HAMMING_DIST, EntryType, NULL);
    INDEX.edit_distance_bkt = BKT_Create(MT_EDIT_DIST, EntryType, NULL);

    INDEX.entry_list = LL_Create(EntryType, &destroyEntry, &compareEntry);
    INDEX.query_list = HT_Create(QueryType, NULL, &destroyQuery, &compareQuery);
    INDEX.result_list = LL_Create(QueryResultType, &destroyQueryResult, &compareQueryResult);

    return EC_SUCCESS;
}

ErrorCode DestroyIndex(){

    int i;
    if(HT_Destroy(INDEX.exact_match_ht) == 1) return EC_FAIL;
    for(i = 0; i < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; i++)
        if(BKT_Destroy(INDEX.hamming_distance_bkt[i]) == 1) return EC_FAIL;
    if(BKT_Destroy(INDEX.edit_distance_bkt) == 1) return EC_FAIL;

    if(LL_Destroy(INDEX.entry_list) == 1) return EC_FAIL;
    if(HT_Destroy(INDEX.query_list) == 1) return EC_FAIL;
    if(LL_Destroy(INDEX.result_list) == 1) return EC_FAIL;

    return EC_SUCCESS;
}

ErrorCode StartQuery(QueryID        query_id,
                     const char*    query_str,
                     MatchType      match_type,
                     unsigned int   match_dist)
{
    //...

    //Crete query and initialize entry list as empty

    Query q = createQuery(query_id, match_type, match_dist);
    HT_Insert(INDEX.query_list, (Pointer )q);
    //Create entries or update existing entries based on the query string tokens and update query's entry list pointers/contents

    char token[MAX_WORD_LENGTH + 1];
    int i = 0;
    while(1){

        if (*query_str != ' ' && *query_str) {
            token[i++] = *query_str++;
            continue;
        }
        token[i] = '\0';
        
        if(i >= MIN_WORD_LENGTH && i <= MAX_WORD_LENGTH){   //i = current token length

            LLNode node = HT_Search(INDEX.exact_match_ht, (Pointer )token);
            Entry e;
            if (!node){
                //Create new entry and add it to list
                
                e = createEntry(token);
                LL_InsertTail(INDEX.entry_list, (Pointer )e);
                
                //Update Index pointers on any new entries | (done below) and update all entries' payloads to contain new query

                HT_Insert(INDEX.exact_match_ht, (Pointer )e);
                BKT_Insert(INDEX.hamming_distance_bkt[i - MIN_WORD_LENGTH], (Pointer )e);
                BKT_Insert(INDEX.edit_distance_bkt, (Pointer )e);
            } 
            else 
                e = (Entry )(node->data);

            LL_InsertTail(e->payload, (Pointer )q);      // Add Query to Payload
            LL_InsertTail(q->query_words, (Pointer )e);  // Add Entry to Query_word entry list
        }

        //Prepare for next iteration if not at end of query_string
        i = 0;
        if (*query_str) query_str++; else break;
    }

    printf("Exiting StartQuery | query_id = %d\n", query_id);

    if(query_id == 47) HT_Print(INDEX.query_list);

    return EC_SUCCESS;
}

ErrorCode EndQuery(QueryID query_id){

    //Toggle query active status
    LLNode node = HT_Search(INDEX.query_list, (Pointer )&query_id);
    if (!node) return EC_FAIL;
    Query q = (Query )(node->data);
    query_active_false(q);
    
    printf("Exiting EndQuery | query_id = %d\n", query_id);

    return EC_SUCCESS;
}

ErrorCode MatchDocument(DocID doc_id, const char *doc_str){

    //Process:
    //Read every query's type and distance and apply search for every word in the document
    //that matches those parameters and save the results
    //Check to see if an exact same lookup has been done before by an earlier query
    //and skip redoing it, link that query's results to the one's with the same search parameters
    
    //Will be used to iterate all queries, checked first because there is no
    //point in continuing if this information is invalid
    unsigned int qcount = HT_GetSize(INDEX.query_list);
    LLNode node = HT_GetFirst(INDEX.query_list);
    if (!qcount || !node) return EC_FAIL;

    //Tokenize and deduplicate document
    HashTable doc_words_ht = HT_Create(StringType, &djb2, NULL, &compareString);
    if (!doc_words_ht) return EC_FAIL;

    char token[MAX_WORD_LENGTH + 1], *word = NULL;
    int i = 0;
    while(!0){
        if (*doc_str != ' ' && *doc_str) {
            token[i++] = *doc_str++;
            continue;
        }
        token[i] = '\0';

        word = (char *)malloc((i + 1) * sizeof(char ));     // i = length of the word
        if (!word) { HT_Destroy(doc_words_ht); return EC_FAIL; }
        strcpy(word, token);
        
        if (!HT_Insert(doc_words_ht, (Pointer )word)) free(word);

        i = 0;  // Reset the word index
        if (*doc_str) doc_str++; else break;
    }

    LList doc_words = HT_ToList(doc_words_ht, &destroyString);
    HT_Destroy(doc_words_ht);
    //Definitions and allocations of helper structures
    LList res_exact = NULL;
    LList *res_edit = (LList *)malloc((MAX_DISTANCE) * sizeof(LList));
    if (!res_edit) { LL_Destroy(doc_words); return EC_FAIL; }
    LList **res_hamm = (LList **)malloc((MAX_DISTANCE) * sizeof(LList *));
    if (!res_hamm) { free(res_edit); LL_Destroy(doc_words); return EC_FAIL; }

    int j = 0;
    for (i = 0; i < MAX_DISTANCE; i++) {
        res_edit[i] = NULL;
        res_hamm[i] = (LList *)malloc((MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1) * sizeof(LList));
        if (!res_hamm[i]){
            for (j = i; j > 0; j--){
                free(res_hamm[j-1]);
            }
            free(res_edit);
            free(res_hamm);
            LL_Destroy(doc_words);
            return EC_FAIL;
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

        Query q = (Query )(node->data);
        if (q->active){
            MatchType mt = q->match_type;
            unsigned int md = q->match_dist;
            QueryID id = q->query_id;
            LList qw = q->query_words;

            //Flagging which structures are to be initialized and searched and which are not
            //Flags can be implemented way more efficiently than this
            char exact_flag, edit_flag[MAX_DISTANCE], hamm_flag[MAX_DISTANCE];
            switch(mt){
                case MT_EXACT_MATCH:
                    exact_flag = (!res_exact) ? 1 : 0;
                    break;
                case MT_HAMMING_DIST:
                    for (i = 0; i < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; i++){
                        if (res_hamm[md-1][i]) break;
                    }
                    hamm_flag[md-1] = (i == MAX_WORD_LENGTH-MIN_WORD_LENGTH+1) ? 1 : 0;
                    break;
                case MT_EDIT_DIST:
                    edit_flag[md-1] = (!res_edit[md-1]) ? 1 : 0;
                    break;
                default:
                    //Destroy all lists
                    for (i = 0; i < MAX_DISTANCE; i++) {
                        LL_Destroy(res_edit[i]);
                        for(j = 0; j < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; j++){
                            LL_Destroy(res_hamm[i][j]);
                        }
                        free(res_hamm[i]);
                    }
                    free(res_edit);
                    free(res_hamm);
                    LL_Destroy(res_exact);
                    LL_Destroy(doc_words);
                    LL_Destroy(res_ids);
                    return EC_FAIL;
            }


            LLNode doc_node = LL_GetHead(doc_words);
            while(doc_node){
                word = (char *)(doc_node->data);
                //If already searched, skip re-searching and mimic post search functionality of previous clone query based on words
                switch(mt){
                    case MT_EXACT_MATCH:
                        if (exact_flag){
                            if (!res_exact) res_exact = LL_Create(EntryType, NULL, &compareEntry);
                            //Start the search
                            LLNode temp = HT_Search(INDEX.exact_match_ht, word);
                            if (temp) LL_InsertTail(res_exact, (Pointer)(temp->data));
                        }
                        break;
                    case MT_HAMMING_DIST:
                        if (hamm_flag[md-1]){
                            if (!res_hamm[md-1][strlen(word)-MIN_WORD_LENGTH]) res_hamm[md-1][strlen(word)-MIN_WORD_LENGTH] = LL_Create(EntryType, NULL, &compareEntry);
                            //Commence the investigation and merge lists
                            LL_Join(res_hamm[md-1][strlen(word)-MIN_WORD_LENGTH], BKT_Search(INDEX.hamming_distance_bkt[strlen(word)-MIN_WORD_LENGTH], word, md));
                        }
                        break;
                    case MT_EDIT_DIST:
                        if (edit_flag[md-1]){
                            if (!res_edit[md-1]) res_edit[md-1] = LL_Create(EntryType, NULL, &compareEntry);
                            //Let the query begin and join lists
                            LL_Join(res_edit[md-1], BKT_Search(INDEX.edit_distance_bkt, word, md));
                        }
                        break;
                    default:
                        //Destroy all lists
                        for (i = 0; i < MAX_DISTANCE; i++) {
                            LL_Destroy(res_edit[i]);
                            for(j = 0; j < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; j++){
                                LL_Destroy(res_hamm[i][j]);
                            }
                            free(res_hamm[i]);
                        }
                        free(res_edit);
                        free(res_hamm);
                        LL_Destroy(res_exact);
                        LL_Destroy(doc_words);
                        LL_Destroy(res_ids);
                        return EC_FAIL;
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
                        if (LL_Exists(res_exact, (Pointer) word) > 0) hits--;
                        break;
                    case MT_HAMMING_DIST:
                        if (LL_Exists(res_hamm[md-1][strlen(word)-MIN_WORD_LENGTH], (Pointer) word) > 0) hits--;
                        break;
                    case MT_EDIT_DIST:
                        if (LL_Exists(res_edit[md-1], (Pointer) word) > 0) hits--;
                        break;
                    default:
                        //Destroy all lists
                        for (i = 0; i < MAX_DISTANCE; i++) {
                            LL_Destroy(res_edit[i]);
                            for(j = 0; j < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; j++){
                                LL_Destroy(res_hamm[i][j]);
                            }
                            free(res_hamm[i]);
                        }
                        free(res_edit);
                        free(res_hamm);
                        LL_Destroy(res_exact);
                        LL_Destroy(doc_words);
                        LL_Destroy(res_ids);
                        return EC_FAIL;
                }
                q_word_node = LL_Next(qw, q_word_node);
            }
            if (!hits) LL_InsertSort(res_ids, createUInt(id));
        }
        node = HT_Next(INDEX.query_list, node);
    }

    //Save doc_id, res_ids->size and res_ids contents in INDEX.result_list

    LL_InsertTail(INDEX.result_list, (Pointer)createQueryResult(doc_id, LL_GetSize(res_ids), (unsigned int *)LL_ToArray(res_ids)));

    //Free all allocated memory
    
    for (i = 0; i < MAX_DISTANCE; i++) {
        LL_Destroy(res_edit[i]);
        for(j = 0; j < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; j++){
            LL_Destroy(res_hamm[i][j]);
        }
        free(res_hamm[i]);
    }
    free(res_edit);
    free(res_hamm);
    LL_Destroy(res_exact);
    LL_Destroy(doc_words);
    LL_Destroy(res_ids);

    printf("Exiting MatchDocument | doc_id = %d\n", doc_id);

    return EC_SUCCESS;
}

ErrorCode GetNextAvailRes(DocID *p_doc_id, unsigned int *p_num_res, QueryID **p_query_ids){
    static unsigned int N = 0;
    // Get the Nth result from the Index's ResultList
    LLNode next_result = LL_GetNth(INDEX.result_list, N++);
    if(next_result == NULL) return EC_NO_AVAIL_RES;
    // Return the QueryResult values
    *p_doc_id = ((QueryResult )(next_result->data))->doc_id;
    *p_num_res = ((QueryResult )(next_result->data))->num_res;
    *p_query_ids = ((QueryResult )(next_result->data))->query_ids;

    return EC_SUCCESS;
}