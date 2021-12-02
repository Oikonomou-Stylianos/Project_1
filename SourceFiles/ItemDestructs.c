#include <stdlib.h>

#include "core.h"
#include "ItemDestructs.h"
#include "DataStructs.h"

//This file contains all potential list-item destructors which will be used by the list destructor - Separated for good dependency tree structure

ErrorCode destroy_entry(Entry *e){

    if (!e) return EC_FAIL;
    
    e->payload = NULL;  //Might revisit to support any added payload functionality
    free(e->word);
    free(e);
    return EC_SUCCESS;
}

ErrorCode destroy_query(Query *q){
    if (!q) return EC_FAIL;
    int i;
    for (i = 0; i < q->word_count; i++) free(q->entries[i]);
    free(q->entries);
    free(q);
    return EC_SUCCESS;
}