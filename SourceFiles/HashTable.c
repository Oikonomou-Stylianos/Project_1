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
// File : HashTable.c
///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "HashTable.h"
#include "LinkedList.h"

#include "constructors.h"
#include "common_types.h"

int prime_sizes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

// djb2 Hash Function
unsigned int djb2(Pointer s){
    
    unsigned int hash = 5381;
    for(; *((char *)s) != '\0'; s++) 
        hash = hash * 33 + *((char *)s);

    return hash;
}
// Create a Hash Table
HashTable HT_Create(DataType dt, HashFunction hf, DestroyFunction df, CompareFunction cf){

    HashTable ht = (HashTable )malloc(sizeof(hash_table ));
    ht->buckets = (LList *)malloc(sizeof(LList ) * prime_sizes[0]);

    if(ht == NULL || ht->buckets == NULL) return NULL;
    
    int i;
    for(i = 0; i < prime_sizes[0]; i++)
        ht->buckets[i] = NULL;
    ht->size = 0;
    ht->capacity = prime_sizes[0];

    ht->dataType = dt;
    ht->hashFunction = hf;
    ht->destroyFunction = df;   // Used by the bucket
    ht->compareFunction = cf;   // ...

    return ht;
}
// Return the hash value of the given data
int HT_Hash(HashTable ht, Pointer data){

    if(ht == NULL || data == NULL) return -1;

    unsigned int hash;
    switch(ht->dataType){
        case StringType:
            hash = ht->hashFunction((Pointer )data);
            break;
        case EntryType:
            hash = ht->hashFunction((Pointer )((Entry )data)->word);
            break;
        default:
            printf("Error: [HT_Hash] : Unsupported data type\n");
            return -1;
    }

    return (int )(hash % INT_MAX);
}
// Insert the given data in the Hash Table
LLNode HT_Insert(const HashTable ht, Pointer data){

    if(ht == NULL || data == NULL) return NULL;

    int hash, index;
    if((hash = HT_Hash(ht, data)) == -1) return NULL; 
    index = hash % ht->capacity;
    
    // printf("Size = %d Capacity = %d Hash = %d Index = %d\n", ht->size, ht->capacity, hash, index);
    LLNode lln;
    if(ht->buckets[index] == NULL)  // If the bucket is not initialized initialize it
        if(!(ht->buckets[index] = LL_Create(ht->dataType, ht->destroyFunction, ht->compareFunction))) return NULL;

    if(!(lln = LL_InsertSortUnique(ht->buckets[index], data))) return NULL;
    ht->size++;

    float load_factor = (float)ht->size / ht->capacity;
    if(load_factor > MAX_LOAD_FACTOR)
        if(!(HT_Rehash(ht))) return NULL;

    return lln;
}
// Search the HashTable for a given data
LLNode HT_Search(const HashTable ht, char *word){

    if(ht == NULL || word == NULL) return NULL;

    int hash, index;

    Pointer temp = NULL;
    switch(ht->dataType){
        case StringType:
            temp = (Pointer )createString(word);
            break;
        case EntryType:
            temp = (Pointer )createEntry(word);
            break;
        default:
            printf("Error: [HT_Search] : Unsupported data type\n");
            return NULL;
    }
    if((hash = HT_Hash(ht, temp)) == -1) return NULL;
    index = hash % ht->capacity;

    LLNode lln;
    lln = LL_Search(ht->buckets[index], word);

    switch(ht->dataType){
        case StringType:
            destroyString(temp);
            break;
        case EntryType:
            destroyEntry(temp);
            break;
        default:
            printf("Error: [HT_Search] : Unsupported data type\n");
            return NULL;
    }

    return lln;
}
// Rehash the data of a Hash Table
HashTable HT_Rehash(const HashTable ht){

    if(ht == NULL) return NULL;

    LList *old_buckets = ht->buckets;
    int i, old_capacity = ht->capacity, primes = sizeof(prime_sizes) / sizeof(int);   // Size of prime_sizes table
    
    for(i = 0; i < primes; i++){    // Calculate the new capacity 
		if(prime_sizes[i] > old_capacity){
            ht->capacity = prime_sizes[i]; 
			break;
		}
	}
    if(old_capacity == ht->capacity)    // If all prime numbers have been used duplicate the previous capacity
        ht->capacity *= 2;

    ht->size = 0;   // Reset the size of the HashTable as the data are going to be reinserted 
    if(!(ht->buckets = (LList *)malloc(sizeof(LList ) * ht->capacity))) return NULL;   // Allocate a new buckets array
    for(i = 0; i < ht->capacity; i++)
        ht->buckets[i] = NULL;   // Initialize every new bucket to NULL

    LLNode lln_temp;
    for(i = 0; i < old_capacity; i++){  // For every old bucket...

        if(old_buckets[i] != NULL){
            lln_temp = LL_GetHead(old_buckets[i]);
            while(lln_temp != NULL){        // ...insert its values in the new buckets array

                if(!(HT_Insert(ht, lln_temp->data))) return NULL;
                lln_temp = LL_Next(old_buckets[i], lln_temp);
            }
        }
    }

    for(i = 0; i < old_capacity; i++)   // Destroy the old buckets
        if(old_buckets[i] != NULL)
            if(LL_Destroy(old_buckets[i]) != 0) return NULL;
    free(old_buckets);  // Free the old buckets array

    // printf("%d -> %d\n", old_capacity, ht->capacity);

    return ht;
}
// Insert the data of a Hash Table in a Linked List and return it
LList HT_ToList(const HashTable ht, DestroyFunction df){

    if(ht == NULL) return NULL;

    LList newList;
    switch(ht->dataType){
        case StringType:
            newList = LL_Create(StringType, df, &compareString);
            break;
        default:
            printf("Error: [HT_ToList] : Unsupported data type\n");
            return NULL;
    }
    if(newList == NULL) return NULL;

    LLNode temp;
    int i;
    for(i = 0; i < HT_GetCapacity(ht); i++){

        if(ht->buckets[i] != NULL){

            temp = LL_GetHead(ht->buckets[i]);
            while(temp != NULL){

                LL_InsertTail(newList, (Pointer )temp->data);

                temp = LL_Next(ht->buckets[i], temp);
            }
        }
    }

    return newList;
}
// Return the size of a Hash Table
int HT_GetSize(const HashTable ht){

    if(ht == NULL) return -1;

    return (int )ht->size;
}
// Return the capacity of a Hash Table
int HT_GetCapacity(const HashTable ht){

    if(ht == NULL) return -1;

    return (int )ht->capacity;
}
// Print a Hash Table
int HT_Print(const HashTable ht){

    if(ht == NULL) return 1;

    int i, capacity;
    if((capacity = HT_GetCapacity(ht)) == -1) return 1;
    
    for(i = 0; i < capacity; i++){

        printf("bucket[%d] ", i);
        if(LL_Print(ht->buckets[i]) == 1)   // If the bucket is not initialized it will return 1
            printf("[ ]\n");
    }

    return 0;
}
// Destroy a Hash Table
int HT_Destroy(HashTable ht){

    if(ht == NULL) return 1;

    int i;
    for(i = 0; i < ht->capacity; i++)
        if(ht->buckets[i] != NULL)
            if(LL_Destroy(ht->buckets[i])) return 1;
    free(ht->buckets);
    free(ht);

    return 0;
}