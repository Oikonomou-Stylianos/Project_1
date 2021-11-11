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

int prime_sizes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

typedef struct{
	WList *buckets;
    int size;       // Number of entries in the Hash table
    int capacity;   // Size of the Hash table
}hash_table;

typedef hash_table *HashTable;

HashTable HT_Create();
WLNode HT_Insert(const HashTable , const char *);
HashTable HT_Rehash(const HashTable );
HashTable InitializeFromFile(const HashTable , const char *);

int hash_string(const char *);