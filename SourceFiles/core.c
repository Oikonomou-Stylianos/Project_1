#include <stdlib.h>
#include <string.h>

#include "core.h"

#include "DataStructs.h"
#include "EntryList.h"
#include "BKTree.h"
#include "HashTable.h"
//#include "distance.h" //Not needed (?)
#include "common_types.h"

//Will use, unfortunately and unevadably, global structures
ErrorCode InitializeIndex(){

    return EC_SUCCESS;
}

ErrorCode DestroyIndex(){

    return EC_SUCCESS;
}

ErrorCode StartQuery(QueryID query_id, const char *query_str, MatchType match_type, unsigned int match_dist){

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