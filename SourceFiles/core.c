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
#include <pthread.h>
#include <errno.h>

#include "LinkedList.h"
#include "BKTree.h"
#include "HashTable.h"

#include "Scheduler.h"
#include "core_routines.h"

#include "constructors.h"
#include "common_types.h"
#include "core.h"

#define MAX_DISTANCE 3

Index INDEX;
JobScheduler JOB_SCHEDULER;

ErrorCode InitializeIndex(){

    INDEX.entry_list    = LL_Create(EntryType, &destroyEntry, &compareEntry);
    INDEX.query_list    = LL_Create(QueryType, &destroyQuery, &compareQuery);
    INDEX.query_ht      = HT_Create(QueryType, NULL, NULL, &compareQuery);
    INDEX.result_list   = LL_Create(QueryResultType, &destroyQueryResult, &compareQueryResult);

    INDEX.exact_match_ht = HT_Create(EntryType, &djb2, NULL, &compareEntry);
    int i;
    for(i = 0; i < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; i++)
        INDEX.hamming_distance_bkt[i] = BKT_Create(MT_HAMMING_DIST, EntryType, NULL);
    INDEX.edit_distance_bkt = BKT_Create(MT_EDIT_DIST, EntryType, NULL);

    JobScheduler_Initialize(MAX_THREADS);
    if(JOB_SCHEDULER == NULL) return EC_FAIL;

    pthread_t j_sch;
    if(pthread_create(&j_sch, NULL, &JobScheduler_Run, NULL) != 0) return EC_FAIL;

    return EC_SUCCESS;
}

ErrorCode DestroyIndex(){

    if(LL_Destroy(INDEX.entry_list) == 1)  return EC_FAIL;
    if(LL_Destroy(INDEX.query_list) == 1)  return EC_FAIL;
    if(HT_Destroy(INDEX.query_ht) == 1)    return EC_FAIL;
    if(LL_Destroy(INDEX.result_list) == 1) return EC_FAIL;

    int i;
    if(HT_Destroy(INDEX.exact_match_ht) == 1) return EC_FAIL;
    for(i = 0; i < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; i++)
        if(BKT_Destroy(INDEX.hamming_distance_bkt[i]) == 1) return EC_FAIL;
    if(BKT_Destroy(INDEX.edit_distance_bkt) == 1) return EC_FAIL;

    if(JobScheduler_Destroy(JOB_SCHEDULER) == 1) return EC_FAIL;

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
    LL_InsertTail(INDEX.query_list, (Pointer )q);
    HT_Insert(INDEX.query_ht, (Pointer )q);
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

    // printf("Exiting StartQuery | query_id = %d\n", query_id);
    // fflush(stdout);

    return EC_SUCCESS;
}

ErrorCode EndQuery(QueryID query_id){

    //Toggle query active status
    LLNode query_node = HT_Search(INDEX.query_ht, (Pointer )&query_id);
    if (!query_node) return EC_FAIL;

    Query q = (Query )(query_node->data);
    query_active_false(q);
    
    printf("Exiting EndQuery | query_id = %d\n", query_id);
    fflush(stdout);

    return EC_SUCCESS;
}

ErrorCode MatchDocument(DocID doc_id, const char *doc_str){

    void **parameters = (void **)malloc(sizeof(void *) * 2);
    if(parameters == NULL) return EC_FAIL;
    parameters[0] = (void *)malloc(sizeof(DocID ));
    *(DocID *)parameters[0] = doc_id; 
    parameters[1] = (void *)malloc(sizeof(char ) * (strlen(doc_str) + 1));
    strcpy((char *)parameters[1], doc_str); 

    if(JobScheduler_EnqueueJob(createJob(&MatchDocument_routine, parameters)) == 1) return EC_FAIL;

    // printf("Exiting MatchDocument | doc_id = %d\n", doc_id);
    // fflush(stdout);

    return EC_SUCCESS;
}

ErrorCode GetNextAvailRes(DocID *p_doc_id, unsigned int *p_num_res, QueryID **p_query_ids){

    pthread_mutex_lock(&(JOB_SCHEDULER->mutex_query_result));
    while(LL_IsEmpty(INDEX.result_list) == 1){

        pthread_cond_wait(&(JOB_SCHEDULER->cond_query_result), &(JOB_SCHEDULER->mutex_query_result));
    }

    LLNode next_result = LL_GetHead(INDEX.result_list);
    if(next_result == NULL) return EC_NO_AVAIL_RES;

    *p_doc_id = ((QueryResult )(next_result->data))->doc_id;
    *p_num_res = ((QueryResult )(next_result->data))->num_res;
    *p_query_ids = ((QueryResult )(next_result->data))->query_ids;

    if(LL_DeleteHead(INDEX.result_list) == 1) return EC_FAIL;

    pthread_mutex_unlock(&(JOB_SCHEDULER->mutex_query_result));

    // printf("Exiting GetNextAvailRes\n");
    // fflush(stdout);

    return EC_SUCCESS;
}