#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DataStructs.h"
#include "QueryList.h"
#include "List.h"

#include "core.h"

ErrorCode create_query_list(List **l){
    *l = create_list()
    return (*l) ? EC_SUCCESS : EC_FAIL;
}

ErrorCode destroy_query_list(List *l){
    if (!l) return EC_FAIL;
    
    destroy_list(l, query);
    return EC_SUCCESS;
}

Query *create_query(const QueryID id, const MatchType mt, const unsigned int md, const unsigned int wc){
    Query *q = (Query *)malloc(sizeof(Query));
    if (!q) return NULL;
    q->id = id; q->match_type = mt; q->match_dist = md; q->word_count = wc; q->isActive = 1;
    q->entries = (Entry **)malloc(wc*sizeof(Entry *));
    if (!q->entries){ free(q); return NULL; }
    int i;
    for (i = 0; i < wc;) q->entries[i++] = NULL;
    return q;
}

Query *copy_query(const Query *q){
    if (!q) return NULL;
    Query newq = create_query(q->id, q->match_type, q->match_dist, q->word_count);
    int i;
    for (i = 0; i < q->word_count; i++) newq->entries[i] = q->entries[i];
    return q;
}

ErrorCode add_query(List *l, const Query *q){
    if (!l || !q) return EC_FAIL;
    return (insert_list(l, (Query *)q)) ? EC_SUCCESS : EC_FAIL;
}

char query_active(Query *q){
    return (!q) ? 0 : q->isActive;
}

char toggle_query_active(Query *q){
    return (!q) ? 0 : (q->isActive = !(q->isActive));
}