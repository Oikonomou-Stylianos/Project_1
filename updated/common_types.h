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
// File : WordList.h
///////////////////////////////////

#pragma once

#include "LinkedList.h"
#include "core.h"

typedef void *Pointer;

typedef int (*CompareFunction)(Pointer , Pointer );
typedef void (*DestroyFunction)(Pointer );
typedef unsigned int (*HashFunction)(Pointer );

typedef enum{ 

    StringType,
    EntryType,
    EntryPtrType,
    IntType,
    UIntType,
    QueryType,
    QueryPtrType,
    BKTNodePtrType,      // Candidate List in BK-Tree
    QueryResultType

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

    unsigned int query_id;
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
	
    HashTable exact_match_ht;
    BKTree hamming_distance_bkt[MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1];
    BKTree edit_distance_bkt;

    LList entry_list;
    LList query_list;
    LList result_list;

}index_data_structures;

typedef index_data_structures *IndexDataStructures;