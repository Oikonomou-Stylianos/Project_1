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
HashTable HT_Rehash(const HashTable );
int HT_GetSize(const HashTable );
int HT_GetCapacity(const HashTable );
int HT_Print(const HashTable );
int HT_Destroy(HashTable );


// HashTable HT_InsertFromFile(const HashTable , const char *);
// WList HT_ToList(const HashTable );
// WList deduplicate(const char *);