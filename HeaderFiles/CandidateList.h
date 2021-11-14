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

#include "DataStructs.h"

typedef struct candidate_list_node_tag{
	BKTreeNode *candidate;
	struct candidate_list_node_tag *next;
}candidate_list_node;

typedef candidate_list_node *CLNode;

typedef struct{
	CLNode head;
	CLNode tail;
}clist;

typedef clist *CList;

CList CL_Create();
CLNode CL_Insert(const CList , BKTreeNode *);
int CL_RemoveFirst(const CList );
CLNode CL_GetFirst(const CList );
int CL_IsEmpty(const CList );
int CL_GetSize(const CList );
int CL_Destroy(CList );