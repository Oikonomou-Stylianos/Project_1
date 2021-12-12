///////////////////////////////////
// University: UoA DIT
// Course : [K23a] Software Development for Computer Systems
// Semester : Fall 2021-2022
// Professor : Yannis Ioannidis 
// --------------------------------
// Students: Stylianos Oikonomou , Anastasios Triantafyllou
// ID : 1115201500243 , 1115201600173 
// --------------------------------
// Project : Assignment_1
// File : WordList.c
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
    
    int i;

    INDEX.entry_list = LL_Create(EntryType, &destroyEntry, &compareEntry);

    INDEX.exact_match_ht = HT_Create(EntryType, &djb2, NULL, &compareEntry);
    INDEX.edit_distance_bkt = BKT_Create(MT_EDIT_DIST, EntryType, NULL);
    for(i = 0; i < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; i++)
        INDEX.hamming_distance_bkt[i] = BKT_Create(MT_HAMMING_DIST, EntryType, NULL);

    INDEX.query_list = LL_Create(QueryType, &destroyQuery, &compareQuery);
    INDEX.result_list = LL_Create(QueryResultType, &destroyQueryResult, &compareQueryResult);

    return EC_SUCCESS;
}

ErrorCode DestroyIndex(){
    printf("DestroyIndex\n");
    int i;

    if(HT_Destroy(INDEX.exact_match_ht) == 1) return EC_FAIL;
    if(BKT_Destroy(INDEX.edit_distance_bkt) == 1) return EC_FAIL;
    for(i = 0; i < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; i++)
        if(BKT_Destroy(INDEX.hamming_distance_bkt[i]) == 1) return EC_FAIL;

    if(LL_Destroy(INDEX.query_list) == 1) return EC_FAIL;
    if(LL_Destroy(INDEX.result_list) == 1) return EC_FAIL;
    
    if(LL_Destroy(INDEX.entry_list) == 1) return EC_FAIL;

    return EC_SUCCESS;
}

ErrorCode StartQuery(QueryID        query_id,
                     const char*    query_str,
                     MatchType      match_type,
                     unsigned int   match_dist)
{
    
    LLNode temp_lln, entry_lln, search_lln, query_lln;
    // Insert a new Query at the tail of the Index's Query List
    query_lln = LL_InsertTail(INDEX.query_list, (Pointer )createQuery(query_id, match_type, match_dist));
    if(query_lln == NULL) return EC_FAIL;

    // Tokenize the Query string and insert the words in a List
    char token[MAX_WORD_LENGTH + 1];
    int index = 0;
    LList tokenList = LL_Create(StringType, &destroyString, &compareString);
    while(1){
        if(*query_str == '\0' || *query_str == ' '){
            token[index] = '\0';
            LL_InsertTail(tokenList, (Pointer )createString(token));
            index = 0;
            if(*query_str == '\0')
                break;
        }
        else{
            token[index] = *query_str;
            index++;
        }
        query_str++;
    }
    // Insert the words of the Query string in the Index's data structures
    temp_lln = LL_GetHead(tokenList);
    while(temp_lln != NULL){

        search_lln = LL_Search(INDEX.entry_list, (Pointer )LL_GetValue(temp_lln ));
        
        if(search_lln == NULL){     // If the word does not have an entry...

            entry_lln = LL_InsertTail(INDEX.entry_list, createEntry((char *)LL_GetValue(temp_lln )));
            HT_Insert(INDEX.exact_match_ht, entry_lln->data);
            BKT_Insert(INDEX.edit_distance_bkt, entry_lln->data);
            BKT_Insert(INDEX.hamming_distance_bkt[strlen((char *)LL_GetValue(temp_lln )) - MIN_WORD_LENGTH], entry_lln->data);
        
            // Link the Query with the Entry and vise versa
            LL_InsertTail(((Query )(query_lln->data))->query_words, (Pointer )(entry_lln->data));
            LL_InsertTail(((Entry )(entry_lln->data))->payload,     (Pointer )(query_lln->data));
        }
        else{
            // Link the Query with the Entry and vise versa
            LL_InsertTail(((Query )(query_lln->data))->query_words, (Pointer )(search_lln->data));
            LL_InsertTail(((Entry )(search_lln->data))->payload,    (Pointer )(query_lln->data));
        }

        temp_lln = LL_Next(tokenList, temp_lln);
    }
    LL_Destroy(tokenList);



    return EC_SUCCESS;
}

ErrorCode EndQuery(QueryID query_id){

    LLNode query_lln = LL_Search(INDEX.query_list, (Pointer )(&query_id));
    if (query_lln == NULL) return EC_FAIL;
  
    ((Query )(query_lln->data))->active = 0;

    return EC_SUCCESS;
}

ErrorCode MatchDocument(DocID doc_id, const char *doc_str){

    char token[MAX_WORD_LENGTH + 1];
    int i, j, index = 0, word_length;
    LList tokenList = LL_Create(StringType, &destroyString, &compareString);
    while(1){
        if(*doc_str == '\0' || *doc_str == ' '){
            token[index] = '\0';
            LL_InsertSortUnique(tokenList, (Pointer )createString(token));              // CHANGE TO DUPLICATE
            index = 0;
            if(*doc_str == '\0')
                break;
        }
        else{
            token[index] = *doc_str;
            index++;
        }
        doc_str++;
    }

    LList res_exact;
    LList *res_edit = (LList *)malloc(sizeof(LList) * MAX_DISTANCE);                                // res_edit[distance]
    LList **res_hamm = (LList **)malloc(sizeof(LList *) * MAX_DISTANCE);                            // ~ ~ ~ ~
    for(i = 0; i < MAX_DISTANCE; i++)                                                               // res_ham[distance][word_length]
        res_hamm[i] = (LList *)malloc(sizeof(LList ) * (MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1));    // ~ ~ ~ ~

    res_exact = NULL;
    for(i = 0; i < MAX_DISTANCE; i++)
        res_edit[i] = NULL;
    for(i = 0; i < MAX_DISTANCE; i++)
        for(j = 0; j < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; j++)
            res_hamm[i][j] = NULL;


    LList temp_list;
    Query current_query;
    LLNode query_lln = LL_GetHead(INDEX.query_list), docword_lln, temp_lln;
    while(query_lln != NULL){
        
        current_query = (Query )LL_GetValue(query_lln);
        if(current_query->active == 1){         // If the Query is not active continue
        
            if(current_query->match_type == MT_EXACT_MATCH){

                if(res_exact == NULL){

                    res_exact = LL_Create(EntryType, NULL, &compareEntry);
                }

                docword_lln = LL_GetHead(tokenList);
                while(docword_lln != NULL){

                    temp_lln = HT_Search(INDEX.exact_match_ht, (char *)LL_GetValue(docword_lln));
                    if(temp_lln != NULL)
                        LL_InsertTail(res_exact, temp_lln->data);

                    docword_lln = LL_Next(tokenList, docword_lln);
                }
            }
            else if(current_query->match_type == MT_EDIT_DIST){

                if(res_edit[current_query->match_dist - 1] == NULL){

                    res_edit[current_query->match_dist - 1] = LL_Create(EntryType, NULL, &compareEntry);
                }

                docword_lln = LL_GetHead(tokenList);
                while(docword_lln != NULL){

                    temp_list = BKT_Search(INDEX.edit_distance_bkt, (char *)LL_GetValue(docword_lln), current_query->match_dist);
                    LL_Join(res_edit[current_query->match_dist - 1], temp_list);

                    docword_lln = LL_Next(tokenList, docword_lln);
                }
            }
            else if(current_query->match_type == MT_HAMMING_DIST){

                docword_lln = LL_GetHead(tokenList);
                while(docword_lln != NULL){
                    
                    word_length = strlen((char *)LL_GetValue(docword_lln));
                    if(res_hamm[current_query->match_dist - 1][word_length - MIN_WORD_LENGTH] == NULL){

                        res_hamm[current_query->match_dist - 1][word_length - MIN_WORD_LENGTH] = LL_Create(EntryType, NULL, &compareEntry);
                    }

                    temp_list = BKT_Search(INDEX.hamming_distance_bkt[word_length - MIN_WORD_LENGTH], (char *)LL_GetValue(docword_lln), current_query->match_dist);
                    LL_Join(res_hamm[current_query->match_dist - 1][word_length - MIN_WORD_LENGTH], temp_list); // Dont check for return value

                    docword_lln = LL_Next(tokenList, docword_lln);
                }
            }
            else{

                printf("Error : [MatchDocument] : Unsupported MatchType\n");
                return EC_FAIL;
            }
        }

        query_lln = LL_Next(INDEX.query_list, query_lln);
    }

    LList succesful_queries = LL_Create(UIntType, &destroyUInt, &compareUInt);
    
    int hits;
    query_lln = LL_GetHead(INDEX.query_list);
    while(query_lln != NULL){

        current_query = (Query )LL_GetValue(query_lln);
        if(current_query->active == 1){
            
            hits = 0;
            temp_lln = LL_GetHead(current_query->query_words);
            while(temp_lln != NULL){

                word_length = strlen((char *)((Entry )(temp_lln->data))->word);
                if(current_query->active == 1){

                    if(current_query->match_type == MT_EXACT_MATCH){
                        if(LL_Exists(res_exact, (Pointer )((Entry )(temp_lln->data))->word) == 1)
                            hits++;
                    }
                    else if(current_query->match_type == MT_EDIT_DIST){
                        if(LL_Exists(res_edit[current_query->match_dist - 1], (Pointer )((Entry )(temp_lln->data))->word) == 1)
                            hits++;
                    }
                    else if(current_query->match_type == MT_HAMMING_DIST){
                        if(LL_Exists(res_hamm[current_query->match_dist - 1][word_length - MIN_WORD_LENGTH], (Pointer )((Entry )(temp_lln->data))->word) == 1)
                            hits++;
                    }
                    else{
                        printf("Error : [MatchDocument] : Unsupported MatchType\n");
                        return EC_FAIL;                
                    }
                }
                temp_lln = LL_Next(current_query->query_words, temp_lln);
            }
            if(hits == LL_GetSize(current_query->query_words))
                LL_InsertSortUnique(succesful_queries, (Pointer )createUInt(current_query->query_id));
        }

        query_lln = LL_Next(INDEX.query_list, query_lln);
    }

    printf("Doc_id = %u, ", doc_id);
    LL_Print(succesful_queries);

    // Insert the query result in the QueryResultList
    LL_InsertTail(INDEX.result_list, (Pointer )createQueryResult(doc_id, LL_GetSize(succesful_queries), (unsigned int *)LL_ToArray(succesful_queries)));

    // Free structures
    LL_Destroy(tokenList);
    LL_Destroy(succesful_queries);
    LL_Destroy(res_exact);
    for(i = 0; i < MAX_DISTANCE; i++)
        LL_Destroy(res_edit[i]);
    for(i = 0; i < MAX_DISTANCE; i++){
        for(j = 0; j < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; j++)
            LL_Destroy(res_hamm[i][j]);
        free(res_hamm[i]);
    }
    free(res_edit);
    free(res_hamm);

    return EC_SUCCESS;
}

ErrorCode GetNextAvailRes(DocID *p_doc_id, unsigned int *p_num_res, QueryID **p_query_ids){

    // Get the first result from the Index's ResultList
    LLNode next_result = LL_GetHead(INDEX.result_list);
    if(next_result == NULL) return EC_NO_AVAIL_RES;
    // Return the QueryResult values
    *p_doc_id = ((QueryResult )(next_result->data))->doc_id;
    *p_num_res = ((QueryResult )(next_result->data))->num_res;
    *p_query_ids = ((QueryResult )(next_result->data))->query_ids;
    // if(LL_DeleteHead(INDEX.result_list) == 1) return EC_FAIL;
    (INDEX.result_list)->head = LL_Next(INDEX.result_list, (INDEX.result_list)->head); 

    return EC_SUCCESS;
}