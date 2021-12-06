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
// File : DataStructs
///////////////////////////////////

#pragma once

#include "core.h"

typedef enum { 
    entry,
    query,
    string,
    WListType,
    other
} DataType;

typedef struct {
    char *word;
    void *payload;
} Entry;

typedef struct {
    QueryID id;
    char isActive;
    MatchType match_type;
    unsigned int match_dist;
    unsigned int word_count;
    Entry **entries;
} Query;

typedef struct lnode {
    void *data;
    struct lnode *next;
} listnode;

typedef struct {
    listnode *head;
    listnode *tail;
    unsigned int size;
} List;


typedef struct bk_tree_node_tag{

	Entry *entry;
	struct bk_tree_node_tag** children;

}bk_tree_node;
typedef bk_tree_node* BKTreeNode;

typedef struct{

	BKTreeNode root;
	MatchType matchType;
}bktree;

typedef bktree *BKTree;
typedef BKTree *Index;