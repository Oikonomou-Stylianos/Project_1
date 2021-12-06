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
    //Add query to main index.querylist
    
    //Create entries or update existing entries based on the query string tokens and update query's entry list pointers/contents



    //Update Index pointers on any new entries and update all entries' payloads to contain new query



    // Below code will be converted to tokenize each word and follow the above guideline
    // Split the query string into words and insert them in the query words List
    char *word = (char *)malloc(sizeof(char ) * (MAX_WORD_LENGTH + 1));
    int index = 0;
    for(; ; query_str++){
        if(*query_str == 32 || *query_str == '\0'){
            word[index] = '\0';
                
            LL_InsertTail(newQuery->query_words, createString(word));

            index = 0;
            free(word);
            if(*query_str == '\0') break;
            word = (char *)malloc(sizeof(char ) * (MAX_WORD_LENGTH + 1));
        }
        else{
            word[index] = *query_str;
            index++;
        }
    }


    return EC_SUCCESS;
}

ErrorCode EndQuery(QueryID query_id){

    return EC_SUCCESS;
}

ErrorCode MatchDocument(DocID doc_id, const char *doc_str){

    return EC_SUCCESS;
}

ErrorCode GetNextAvailRes(DocID *p_doc_id, unsigned int *p_num_res, QueryID **p_query_ids){

    return EC_SUCCESS;
}