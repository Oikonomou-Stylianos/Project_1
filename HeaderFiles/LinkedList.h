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
// File : LinkedList.h
///////////////////////////////////

#pragma once

#include "common_types.h"

LList LL_Create(DataType , DestroyFunction , CompareFunction );

LLNode LL_InsertHead(const LList , Pointer );
LLNode LL_InsertTail(const LList , Pointer );
LLNode LL_InsertSort(const LList , Pointer );
LLNode LL_InsertSortUnique(const LList , Pointer);
LLNode LL_InsertAfter(const LList , const LLNode , Pointer );
LLNode LL_InsertAt(const LList , Pointer , const unsigned int );

LLNode LL_Search(const LList , Pointer); // Iterative
LLNode LL_SearchRec(const LList , const LLNode , Pointer); // Recursive
int LL_Exists(const LList , Pointer );

int LL_DeleteHead(const LList );
int LL_DeleteTail(const LList );
int LL_DeleteNth(const LList , const unsigned int );

LList LL_Join(const LList , LList );
Pointer LL_ToArray(const LList );

Pointer LL_GetValue(const LLNode );
LLNode LL_GetHead(const LList );
LLNode LL_GetTail(const LList );
LLNode LL_GetNth(const LList , const unsigned int );
LLNode LL_Next(const LList , const LLNode );
LLNode LL_Previous(const LList , const LLNode );

int LL_Print(const LList );
int LL_IsEmpty(const LList );
unsigned int LL_GetSize(const LList );

LList LL_Clean(const LList );
int LL_Destroy(LList );