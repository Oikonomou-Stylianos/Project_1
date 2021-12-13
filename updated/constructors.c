#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "LinkedList.h"
#include "HashTable.h"

#include "constructors.h"
#include "common_types.h"
#include "core.h"

char *createString(char *str){

    char *newStr = (char *)malloc(sizeof(char ) * (strlen(str) + 1));
    if(newStr == NULL) return NULL;

    strcpy(newStr, str);

    return newStr;
}
void destroyString(Pointer str){

    if(str == NULL) return;

    free((char *)str);
}
int compareString(Pointer str1, Pointer str2){

    if(str1 == NULL || str2 == NULL) return -2;

    return strcmp((char *)str1, (char *)str2);
}
//////////////////////////////////////////////
int *createInt(int n){

    int *newInt = (int *)malloc(sizeof(int ));
    if(newInt == NULL) return NULL;

    *newInt = n;

    return newInt;
}
void destroyInt(Pointer n){

    if(n == NULL) return;

    free((int *)n);
}
int compareInt(Pointer n1, Pointer n2){

    if(n1 == NULL || n2 == NULL) return -2;

    return *(int *)n1 == *(int *)n2 ? 0 : *(int *)n1 < *(int *)n2 ? -1 : 1; 
}
//////////////////////////////////////////////
unsigned int *createUInt(unsigned int n){

    unsigned int *newUInt = (unsigned int *)malloc(sizeof(unsigned int ));
    if(newUInt == NULL) return NULL;

    *newUInt = n;

    return newUInt;
}
void destroyUInt(Pointer n){

    if(n == NULL) return;

    free((unsigned int *)n);
}
int compareUInt(Pointer n1, Pointer n2){

    if(n1 == NULL || n2 == NULL) return -2;

    return *(unsigned int *)n1 == *(unsigned int *)n2 ? 0 : *(unsigned int *)n1 < *(unsigned int *)n2 ? -1 : 1; 
}
//////////////////////////////////////////////
Entry createEntry(char *w){

    if(w == NULL) return NULL;

    Entry e = (Entry )malloc(sizeof(entry ));
    if(e == NULL) return NULL;
    e->word = (char *)malloc(sizeof(char ) * (strlen(w) + 1));
    if(e->word == NULL) { free(e); return NULL; }
    strcpy(e->word, w);
    if((e->payload = LL_Create(QueryType, NULL, &compareQuery)) == NULL) { free(e->word); free(e); return NULL; }
    
    return e; 
}
void destroyEntry(Pointer e){

    if(e == NULL) return;

    free(((Entry )e)->word);
    if(LL_Destroy(((Entry )e)->payload) == 1) return;
    free(((Entry )e));
}
int compareEntry(Pointer e1, Pointer e2){

    if(e1 == NULL || e2 == NULL) return -2;

    return strcmp(((Entry )e1)->word, ((Entry )e2)->word);
}
//////////////////////////////////////////////
Query createQuery(unsigned int id, MatchType mt, unsigned int md){

    Query newQuery = (Query )malloc(sizeof(query ));
    if(newQuery == NULL) return NULL;

    if((newQuery->query_words = LL_Create(EntryType, NULL, &compareEntry)) == NULL){
        free(newQuery);
        return NULL;
    }
    
    newQuery->query_id = id;
    newQuery->match_type = mt;
    newQuery->match_dist = md;
    newQuery->active = 1;

    return newQuery;
}
void destroyQuery(Pointer q){

    if(q == NULL) return;

    if(LL_Destroy(((Query )q)->query_words) == 1) return;
    free(q);
}
int compareQuery(Pointer q1, Pointer q2){

    if(q1 == NULL || q2 == NULL) return -2;

    return ((Query )q1)->query_id == ((Query )q2)->query_id ? 0 : ((Query )q1)->query_id < ((Query )q2)->query_id ? -1 : 1;  
}
//////////////////////////////////////////////
char toggle_query_active(Query q){
    return (q->active = !q->active);
}
void query_active_false(Query q){
    q->active = 0; return;
}
void query_active_true(Query q){
    q->active = 1; return;
}
//////////////////////////////////////////////
int compareBKTNPtrString(Pointer w1, Pointer w2){

    if(w1 == NULL || w2 == NULL) return -2;

    return strcmp((char *)((*(BKTreeNode *)w1)->data), (char *)((*(BKTreeNode *)w2)->data));
}
int compareBKTNPtrEntry(Pointer w1, Pointer w2){

    if(w1 == NULL || w2 == NULL) return -2;

    return strcmp((char *)((*(Entry *)((*(BKTreeNode *)w1)->data))->word), (char *)((*(Entry *)((*(BKTreeNode *)w2)->data))->word));
}
//////////////////////////////////////////////
QueryResult createQueryResult(unsigned int doc_id, unsigned int num_res, unsigned int *query_ids){

    QueryResult newQR = (QueryResult )malloc(sizeof(query_result ));
    if(newQR == NULL) return NULL;

    newQR->doc_id = doc_id;
    newQR->num_res = num_res;
    newQR->query_ids = query_ids;

    return newQR;
}
void destroyQueryResult(Pointer qr){

    if(qr == NULL) return;

    //free(((QueryResult )qr)->query_ids); //Is free'd by the testdriver executable, for some reason
    free(qr);
}
int compareQueryResult(Pointer qr1, Pointer qr2){

    if(qr1 == NULL || qr2 == NULL) return -2;

    return compareUInt((Pointer )(&((QueryResult )qr1)->doc_id), (Pointer )(&((QueryResult )qr2)->doc_id));
}