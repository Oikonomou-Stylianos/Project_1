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

#include "core.h"

typedef struct word_list_node_tag{
	char word[MAX_WORD_LENGTH];
	struct word_list_node_tag *next;
}word_list_node;

typedef word_list_node *WLNode;

typedef struct{
	WLNode head;
	WLNode tail;
}wlist;

typedef wlist *WList;

WList WL_Create();
WLNode WL_Insert(WList , char *);
WLNode WL_InsertSortUnique(const WList , const char *);
int WL_RemoveFirst(WList );
WLNode WL_GetFirst(WList );
int WL_Print(WList );
int WL_IsEmpty(WList );
int WL_GetSize(WList );
int WL_Destroy(WList );