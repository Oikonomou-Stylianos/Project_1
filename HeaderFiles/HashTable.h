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
// File : HashTable.h
///////////////////////////////////

#pragma once

#include "LinkedList.h"
#include "common_types.h"

#define MAX_LOAD_FACTOR 0.9

unsigned int djb2(Pointer );

HashTable HT_Create(DataType , HashFunction , DestroyFunction , CompareFunction );
int HT_Hash(HashTable , Pointer );
LLNode HT_Insert(const HashTable , Pointer );
LLNode HT_InsertUnique(const HashTable , Pointer );
HashTable HT_InsertFromList(const HashTable , LList );
LLNode HT_Search(const HashTable , Pointer );
HashTable HT_Rehash(const HashTable );
LList HT_ToList(const HashTable , DestroyFunction );
int HT_GetSize(const HashTable );
int HT_GetCapacity(const HashTable );
// LLNode HT_GetFirst(const HashTable );
// LLNode HT_Next(const HashTable , LLNode );
int HT_Print(const HashTable );
int HT_Destroy(HashTable );