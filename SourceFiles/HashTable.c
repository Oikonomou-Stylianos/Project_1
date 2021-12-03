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
// File : HashTable.c
///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "DataStructs.h"
#include "HashTable.h"
#include "WordList.h"

int prime_sizes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

// djb2 Hash Function
unsigned int hash_string(const char *s){
    
    if(s == NULL) return -1;

    unsigned int hash = 5381;
    for(; *s != '\0'; s++) 
        hash = hash * 33 + *s;

    return hash;
}
// Create a Hash Table
HashTable HT_Create(DataType dt){

    HashTable ht = (HashTable )malloc(sizeof(hash_table));
    ht->dataType = dt;
    switch(ht->dataType){
        case string:
            (WList *)ht->buckets = (WList *)malloc(sizeof(WList ) * prime_sizes[0]);
            break;
        case other:
            (List **)ht->buckets = (List **)malloc(sizeof(List *) * prime_sizes[0]);
            break;
        default:
            printf("Error : [HT_Create] : Unsupported data type\n");
            return NULL;
    }
    if(ht == NULL || ht->buckets == NULL) return NULL;
    int i;
    for(i = 0; i < prime_sizes[0]; i++)
        ht->buckets[i] = NULL;
    ht->size = 0;
    ht->capacity = prime_sizes[0];

    return ht;
}
// Insert a word in a Hash Table
WLNode HT_Insert(const HashTable ht, const void *data){

    if(ht == NULL || data == NULL) return NULL;

    int hash, index; 
    switch(ht->dataType){
        case string:
            if((hash = (int )(hash_string((char *)data) % INT_MAX)) == -1) return NULL; 
            break;
        case entry:
            if((hash = (int )(hash_string((char *)((Entry *)data->word) % INT_MAX)) == -1) return NULL; 
            break;
        default:
            print("Error : [HT_Insert] : Unsupported data type\n");
            return NULL;
    }
    index = hash % ht->capacity;
    
    // printf("Size = %d Capacity = %d Hash = %d Index = %d\n", ht->size, ht->capacity, hash, index);
    WLNode wln;
    if(ht->buckets[index] == NULL){  // If the bucket is not initialized initialize it
        switch(ht->dataType){
            case string:
                if(!(ht->buckets[index] = WL_Create())) return NULL;
                if(!(wln = WL_InsertSortUnique(ht->buckets[index], (char *)data))) return NULL;
                break;
            case entry:
                if(create_entry_list(&(ht->buckets[index])) != EC_SUCCESS) return NULL;
                break;
            default:
                print("Error : [HT_Insert] : Unsupported data type\n");
                return NULL;
        }
    }    
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
            if(WL_Destroy(old_buckets[i]) != 0) return NULL;
    free(old_buckets);  // Free the old buckets array

    // printf("%d -> %d\n", old_capacity, ht->capacity);

    return ht;
}
// Insert the words of a file in a Hash Table
HashTable HT_InsertFromFile(const HashTable ht, const char *file){

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
    if(fclose(fp) != 0) return NULL;
     
    return ht;
}
// Insert the contents of a Hash Table in a Word List 
WList HT_ToList(const HashTable ht){

    if(ht == NULL) return NULL;

    WList wl;
    if(!(wl = WL_Create())) return NULL;

    WLNode wln_temp;
    int i;
    for(i = 0; i < ht->capacity; i++){

        if(ht->buckets[i] != NULL){
            wln_temp = ht->buckets[i]->head;
            while(wln_temp != NULL){        // ...insert its values in the new buckets array

                if(!(WL_Insert(wl, wln_temp->word))) { WL_Destroy(wl); return NULL; } 
                wln_temp = wln_temp->next;
            }
        }
    }
    return wl;
}
// Destroy a Hash Table
int HT_Destroy(HashTable ht){

    if(ht == NULL) return 1;

    int i;
    for(i = 0; i < ht->capacity; i++)
        if(ht->buckets[i] != NULL)
            if(WL_Destroy(ht->buckets[i])) return 1;
    free(ht->buckets);
    free(ht);

    return 0;
}
// Deduplicate the words of a given file and put them in a Word List
WList deduplicate(const char *file){

    if(file == NULL) return NULL;

    HashTable ht;
    WList wl;
    if(!(ht = HT_Create(string))) return NULL;
    if(!(HT_InsertFromFile(ht, file))) { HT_Destroy(ht); return NULL; }
    if(!(wl = HT_ToList(ht))) { HT_Destroy(ht); return NULL; }
    if(HT_Destroy(ht)) return NULL;

    return wl;
}