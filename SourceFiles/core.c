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

    // Initilize Index
    INDEX.entry_list    = LL_Create(EntryType, &destroyEntry, &compareEntry);
    INDEX.query_list    = LL_Create(QueryType, &destroyQuery, &compareQuery);
    INDEX.query_ht      = HT_Create(QueryType, NULL, NULL, &compareQuery);
    INDEX.result_list   = LL_Create(QueryResultType, &destroyQueryResult, &compareQueryResult);

    INDEX.exact_match_ht = HT_Create(EntryType, &djb2, NULL, &compareEntry);
    int i;
    for(i = 0; i < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; i++)
        INDEX.hamming_distance_bkt[i] = BKT_Create(MT_HAMMING_DIST, EntryType, NULL);
    INDEX.edit_distance_bkt = BKT_Create(MT_EDIT_DIST, EntryType, NULL);

    JOB_SCHEDULER = JobScheduler_Create(MAX_THREADS);
    if(JOB_SCHEDULER == NULL) return EC_FAIL;

    pthread_t sch;
    if(pthread_create(&sch, NULL, &JobScheduler_Run, (void *)JOB_SCHEDULER) != 0){
        printf("Error : [InitializeIndex] : Failed to create a thread, errno = %d\n", errno);
        return EC_FAIL;
    }

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

    if(JobSceduler_Destroy(JOB_SCHEDULER) return EC_FAIL;

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

    printf("Exiting StartQuery | query_id = %d\n", query_id);

    return EC_SUCCESS;
}

ErrorCode EndQuery(QueryID query_id){

    //Toggle query active status
    LLNode node = HT_Search(INDEX.query_ht, (Pointer )&query_id);
    if (!node) return EC_FAIL;
    Query q = (Query )(node->data);
    query_active_false(q);
    
    printf("Exiting EndQuery | query_id = %d\n", query_id);

    return EC_SUCCESS;
}

ErrorCode MatchDocument(DocID doc_id, const char *doc_str){

    unsigned int offset = 0;
    void *parameters = (void *)malloc(sizeof(int *) + sizeof(DocID) + sizeof(char *));
    if(parameters == NULL) return EC_FAIL;
    offset += sizeof(int *);
    *(parameters+offset) = doc_id; 
    offset += sizeof(DocID);
    strcpy(parameters+offset, doc_str); 

    if(JobSceduler_Submit(JOB_SCHEDULER, createJob(&MatchDocument_routine, parameters)) == 1) return EC_FAIL;

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

    printf("Exiting GetNextAvailRes\n");

    return EC_SUCCESS;
}