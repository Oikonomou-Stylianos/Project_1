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

static Index INDEX;

ErrorCode InitializeIndex(){

    INDEX.exact_match_ht = HT_Create(EntryPtrType, &djb2, NULL, &compareEntryPtr);
    int i;
    for(i = 0; i < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; i++)
        INDEX.hamming_distance_bkt[i] = BKT_Create(MT_HAMMING_DIST, EntryPtrType, NULL);
    INDEX.edit_distance_bkt = BKT_Create(MT_EDIT_DIST, EntryPtrType, NULL);

    INDEX.entry_list = LL_Create(EntryType, &destroyEntry, &compareEntry);
    INDEX.query_list = LL_Create(QueryType, &destroyQuery, &compareQuery);
    INDEX.result_list = LL_Create(QueryResultType, NULL, NULL);

    return EC_SUCCESS;
}

ErrorCode DestroyIndex(){

    if(HT_Destroy(INDEX.exact_match_ht) == 1) return EC_FAIL;
    for(i = 0; i < MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1; i++)
        if(BKT_Destroy(INDEX.hamming_distance_bkt[i] == 1) return EC_FAIL;
    if(BKT_Destroy(INDEX.edit_distance_bkt == 1) return EC_FAIL;

    if(LL_Destroy(INDEX.entry_list) == 1) return EC_FAIL;
    if(LL_Destroy(INDEX.query_list) == 1) return EC_FAIL;
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
    LL_InsertTail(INDEX.query_list, (Pointer)q);
    
    //Create entries or update existing entries based on the query string tokens and update query's entry list pointers/contents

    char token[MAX_WORD_LENGTH+1];
    int i = 0;
    while(*query_str){

        if (*query_str != ' ' && *query_str) {
            token[i++] = *query_str++;
            continue;
        }
        token[i] = '\0';

        LLNode node = LL_Search(INDEX.entry_list, (Pointer)token);
        Entry e = NULL;
        if (!node){
            //Create new entry and add it to list
            
            e = createEntry(token);
            LL_InsertTail(INDEX.entry_list, (Pointer)e);
            
            //Update Index pointers on any new entries | (done below) and update all entries' payloads to contain new query

            HT_Insert(INDEX.exact_match_ht, (Pointer)&e);
            BKT_Insert(INDEX.hamming_distance_bkt[i-MIN_WORD_LENGTH], (Pointer)&e);   //i holds the current token length
            BKT_Insert(INDEX.edit_distance_bkt, (Pointer)&e);

        } else e = (Entry)(node->data);

        LL_InsertTail(e->payload, (Pointer)q);  // Add Query to Payload
        LL_InsertTail(q->query_words, (Pointer)e);  // Add Entry to Query_word entry list
    
        //Prepare for next iteration if not at end of query_string
        i = 0;
        if (*query_str) query_str++;
    }

    return EC_SUCCESS;
}

ErrorCode EndQuery(QueryID query_id){

    //Toggle query active status
    LLNode node = LL_Search(INDEX.query_list, query_id);
    if (!q) return EC_FAIL;
    Query q = (Query)(node->data);
    query_active_false(q);
    return EC_SUCCESS;
}

ErrorCode MatchDocument(DocID doc_id, const char *doc_str){

    //Process:
    //Read every query's type and distance and apply search for every word in the document
    //that matches those parameters and save the results
    //Check to see if an exact same lookup has been done before by an earlier query
    //and skip redoing it, link that query's results to the one's with the same search parameters
    
    //Tokenize document
    LList doc_words = LL_Create(StringType, &destroyString, &compareString);
    char token[MAX_WORD_LENGTH + 1], *word = NULL;
    int i = 0;
    
    while(*doc_str){
        if (*doc_str != ' ' && *doc_str) {
            token[i++] = *doc_str++;
            continue;
        }
        token[i] = '\0';
        word = malloc((i+1)*sizeof(char));
        if (!word) { LL_Destroy(doc_words); return EC_FAIL; }
        LL_InsertTail(doc_words, (char *)word);

        i = 0;
        if (*doc_str) doc_str++;
    }

    //Apply search for all queries
    unsigned int qcount = LL_GetSize(INDEX.query_list);
    LLNode node = LL_GetHead(INDEX.query_list);
    if (!qcount || !node) return EC_FAIL;

    while (qcount--){
        Query q = (Query)(node->data);
        MatchType mt = q->match_type;
        unsigned int md = q->match_dist;
        QueryID id = query_id;
        LList qw = q->query_words;

        if (q->active){
            //Make search for all document words and save results
        }
        node = LL_Next(INDEX.query_list, node);
    }

    //Save all query_id results in INDEX.result_list based on individual query results

    return EC_SUCCESS;
}

ErrorCode GetNextAvailRes(DocID *p_doc_id, unsigned int *p_num_res, QueryID **p_query_ids){

    return EC_SUCCESS;
}