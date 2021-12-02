#include <stdlib.h>
#include <string.h>

#include "core.h"

#include "DataStructs.h"
#include "EntryList.h"
#include "QueryList.h"
#include "HashTable.h"
#include "BKTree.h"
#include "HashTable.h"
//#include "distance.h" //Not needed (?)
#include "common_types.h"

//Will use, unfortunately and unevadably, global structures

static List *el, *ql;
static BKTree bke, bkh[28];
static HashTable hte;


ErrorCode InitializeIndex(){
    //Typical null initialization
    el = ql = NULL;
    bke = NULL;
    hte = NULL;
    //Actual initialization with proper memory deallocation in case of error
    for (i = 0; i < 28; i++) bkh[i] = NULL;
    if (create_entry_list(&el) != EC_SUCCESS) return EC_FAIL;
    if (create_entry_list(&ql) != EC_SUCCESS) { free(el); return EC_FAIL;}
    if (!(bke = BKT_Create(MT_EDIT_DIST))) { free(el); free(ql); return EC_FAIL;}
    if (!(hte = HT_Create(entry))) { free(el); free(ql); free(bke); return EC_FAIL;}
    int i, j;
    for (i = 0; i < 28; i++){
        if (!(bkh[i] = BKT_Create(MT_HAMMING_DIST))) {
            for (j = 0; j < i; j++) free(bkh[j]);
            free(el); free(ql); free(bke); free(hte); return EC_FAIL;
        }
    }
    //Getting down to business...
    
    //Might be done here, will expand if needed

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