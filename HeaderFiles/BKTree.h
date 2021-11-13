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
#include "EntryList.h"
#include "core.h"

typedef struct bk_tree_node_tag{

	Entry *entry;
	struct bk_tree_node_tag** children;

}bk_tree_node;
typedef bk_tree_node* BKTreeNode;

typedef struct{

	BKTreeNode root;
	MatchType matchType;
}bktree;
typedef bktree* BKTree;

BKTree BKT_Create(MatchType );
BKTreeNode BKT_CreateNode(Entry *);
BKTreeNode BKT_Insert(const BKTree , Entry *);
BKTreeNode BKT_InsertNode(const BKTree , const BKTreeNode , Entry *);
BKTree BKT_InsertFromEntryList(const BKTree , const List *);
WList BKT_Search(const BKTree , const Entry *, int );
int BKT_Destroy(BKTree );
int BKT_DestroyNode(BKTreeNode );