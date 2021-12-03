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

#include "WordList.h"
#include "DataStructs.h"

#define MAX_LOAD_FACTOR 0.9

typedef struct{
	void **buckets;
    int size;       // Number of entries
    int capacity;   // Number of buckets

    DataType dataType;
}hash_table;

typedef hash_table *HashTable;

unsigned int hash_string(const char *);

HashTable HT_Create();
WLNode HT_Insert(const HashTable , const char *);
HashTable HT_Rehash(const HashTable );
HashTable HT_InsertFromFile(const HashTable , const char *);
WList HT_ToList(const HashTable );
int HT_Destroy(HashTable );

WList deduplicate(const char *);