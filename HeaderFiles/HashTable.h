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

#include "WordList.h"

#define MAX_LOAD_FACTOR 0.9

typedef struct{
	WList *buckets;
    int size;       // Number of entries
    int capacity;   // Number of buckets
}hash_table;

typedef hash_table *HashTable;

HashTable HT_Create();
WLNode HT_Insert(const HashTable , const char *);
HashTable HT_Rehash(const HashTable );
HashTable HT_InitializeFromFile(const HashTable , const char *);

unsigned int hash_string(const char *);