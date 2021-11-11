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

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "HashTable.h"
#include "WordList.h"
#include "common_types.h"

int prime_sizes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

HashTable HT_Create(){

    HashTable ht = (HashTable )malloc(sizeof(hash_table));
    ht->buckets = (WList *)malloc(sizeof(WList ) * prime_sizes[0]);
    if(ht == NULL || ht->buckets == NULL) return NULL;
    int i;
    for(i = 0; i < prime_sizes[0]; i++)
        ht->buckets[i] = NULL;
    ht->size = 0;
    ht->capacity = prime_sizes[0];

    return ht;
}
// Insert a word in a Hash Table
WLNode HT_Insert(const HashTable ht, const char *word){

    if(ht == NULL || word == NULL) return NULL;

    int hash, index; 
    if((hash = (int )hash_string(word)) == -1) return NULL; 
    index = hash % ht->capacity;
    
    // printf("Size = %d Capacity = %d Hash = %d Index = %d\n", ht->size, ht->capacity, hash, index);
    WLNode wln;
    if(ht->buckets[index] == NULL)  // If the bucket is not initialized initialize it
        if(!(ht->buckets[index] = WL_Create())) return NULL;
    if(!(wln = WL_InsertSortUnique(ht->buckets[index], word))) return NULL;
    ht->size++;

    float load_factor = (float)ht->size / ht->capacity;
    if(load_factor > MAX_LOAD_FACTOR)
        if(!(HT_Rehash(ht))) return NULL;

    return wln;
}
// Rehash a Hash Table
HashTable HT_Rehash(const HashTable ht){

    if(ht == NULL) return NULL;

    WList *old_buckets = ht->buckets;
    int i, old_capacity = ht->capacity, primes = sizeof(prime_sizes) / sizeof(int);   // Size of prime_sizes table
    
    for(i = 0; i < primes; i++){    // Calculate the new capacity 
		if(prime_sizes[i] > old_capacity){
            ht->capacity = prime_sizes[i]; 
			break;
		}
	}
    if(old_capacity == ht->capacity)    // If all prime numbers have been used duplicate the previous capacity
        ht->capacity *= 2;

    ht->size = 0;   // Reset the size of the HashTable as the words are going to be reinserted 
    if(!(ht->buckets = (WList *)malloc(sizeof(WList ) * ht->capacity))) return NULL;   // Allocate a new buckets array
    for(i = 0; i < ht->capacity; i++)
        ht->buckets[i] = NULL;   // Initialize every new bucket to NULL

    WLNode wln_temp;
    for(i = 0; i < old_capacity; i++){  // For every old bucket...

        if(old_buckets[i] != NULL){
            wln_temp = old_buckets[i]->head;
            while(wln_temp != NULL){        // ...insert its values in the new buckets array

                if(!(HT_Insert(ht, wln_temp->word))) return NULL;
                wln_temp = wln_temp->next;
            }
        }
    }
    
    for(i = 0; i < old_capacity; i++)   // Destroy the old buckets
        if(old_buckets[i] != NULL)
            if(!(WL_Destroy(old_buckets[i]))) return NULL;
    free(old_buckets);  // Free the old buckets array

    return ht;
}
//
HashTable HT_InitializeFromFile(HashTable ht, const char *file){

    if(ht == NULL || file == NULL) return NULL;

    FILE *fp = fopen(file, "r");
    if(fp == NULL) return NULL;

    int c, index = 0;
    char word[MAX_WORD_LENGTH + 1];
    while(!feof(fp)){

        c = fgetc(fp);
        if(c == ' ' || c == '\n' || feof(fp)){

            word[index] = '\0'; // Incert the null character at the end of the word
            index = 0;  // Reset the index for the next word

            HT_Insert(ht, word);
        }
        else{

            if(index > MAX_WORD_LENGTH) // If the word has exceeded the MAX_WORD_LENGTH ignore the next characters
                continue;

            word[index] = c;
            index++;
        }
    }

    return ht;
}
// 
WList HT_TransferToList()
// djb2 Hash Function
unsigned int hash_string(const char *s){
    
    if(s == NULL) return -1;

    unsigned int hash = 5381;
    for(; *s != '\0'; s++) 
        hash = hash * 33 + *s;

    return hash % INT_MAX;
}

WList deduplication(const char *file){


}