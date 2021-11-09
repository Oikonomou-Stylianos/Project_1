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
// File : 
///////////////////////////////////

#pragma once

#include "common_types.h"
#include "WordList.h"

typedef struct bk_tree_node_tag{

	char word[MAX_WORD_LENGTH];
	struct bk_tree_node_tag** children;

}bk_tree_node;
typedef bk_tree_node* BKTreeNode;

typedef struct{

	BKTreeNode root;

}bktree;
typedef bktree* BKTree;

BKTree BKT_Create();
BKTreeNode BKT_CreateNode(const char *);
BKTreeNode BKT_Insert(BKTree , const char *);
BKTreeNode BKT_InsertNode(BKTreeNode , const char *);
WList BKT_Search(BKTree , const char *, int );
int BKT_Destroy(BKTree );
int BKT_DestroyNode(BKTreeNode );