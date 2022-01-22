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
// File : common_types.h
///////////////////////////////////

#pragma once

#include "core.h"

typedef void *Pointer;

typedef int (*CompareFunction)(Pointer , Pointer );
typedef void (*DestroyFunction)(Pointer );
typedef unsigned int (*HashFunction)(Pointer );

typedef enum{ 

    StringType,
    EntryType,
    IntType,
    UIntType,
    QueryType,
    BKTNodeType,      // Candidate List in BK-Tree
    QueryResultType,
    JobType

}DataType;

//////////////////////////////////////////////
typedef struct llist_node_tag{
	
    Pointer data;
	struct llist_node_tag *next;

}llnode;

typedef llnode *LLNode;
///////////////////////
typedef struct{

	LLNode head;
	LLNode tail;
    unsigned int size;

    DataType dataType;
    DestroyFunction destroyFunction;
    CompareFunction compareFunction;

}llist;

typedef llist *LList;
//////////////////////////////////////////////
typedef struct{

    char *word;
    LList payload;

}entry;

typedef entry *Entry;
//////////////////////////////////////////////
typedef struct{

    QueryID query_id;
	LList query_words;
	MatchType match_type;
	unsigned int match_dist;

    char active;    // 1 if True, 0 if False

}query;

typedef query *Query;
//////////////////////////////////////////////
typedef struct{
	
    LList *buckets;
    unsigned int size;       // Number of entries
    unsigned int capacity;   // Number of buckets

    HashFunction hashFunction;
    DataType dataType;
    DestroyFunction destroyFunction;
    CompareFunction compareFunction;

}hash_table;

typedef hash_table *HashTable;
//////////////////////////////////////////////
typedef struct bk_tree_node_tag{

	Pointer data;
	struct bk_tree_node_tag** children;

}bk_tree_node;

typedef bk_tree_node* BKTreeNode;
///////////////////////
typedef struct{

	BKTreeNode root;
	MatchType matchType;

    DataType dataType;
    DestroyFunction destroyFunction;

}bktree;

typedef bktree *BKTree;
//////////////////////////////////////////////
typedef struct{

    unsigned int doc_id;
    unsigned int num_res;
    unsigned int *query_ids;

}query_result;

typedef query_result *QueryResult;
//////////////////////////////////////////////
typedef struct{
	
    LList entry_list;
    LList query_list;
    HashTable query_ht;
    LList result_list;

    HashTable exact_match_ht;
    BKTree edit_distance_bkt;
    BKTree hamming_distance_bkt[MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1];

}Index;
//////////////////////////////////////////////
typedef struct{

    ErrorCode (*routine)(void *);
    void *parameters;
}job;

typedef job *Job;
///////////////////////
typedef struct{

    unsigned int max_threads, active_threads_count;
    LList queue;
    pthread_t *tids;
    char *active_threads_flags;

    //mutex, condvar...
    pthread_mutex_t mutex_threads;
    pthread_cond_t cond_threads;
    pthread_mutex_t mutex_thread_count;

}jobscheduler;

typedef jobscheduler *JobScheduler;
//////////////////////////////////////////////