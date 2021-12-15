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
// File : HashTable_test.c
///////////////////////////////////

#include "acutest.h"

#include "HashTable.h"
#include "LinkedList.h"

#include "common_types.h"
#include "constructors.h"
#include "core.h"

void test_HT_Create(void){
    
    HashTable ht;
    TEST_CHECK((ht = HT_Create(StringType, NULL, NULL, NULL)) != NULL);
    HT_Destroy(ht);
}
void test_HT_Hash(void){

    int hash;
    HashTable ht = HT_Create(StringType, &djb2, NULL, NULL);
    char *str = createString("aaaa");

    TEST_CHECK((hash = HT_Hash(NULL, NULL)) == -1);
    TEST_CHECK((hash = HT_Hash(ht, NULL)) == -1);
    TEST_CHECK((hash = HT_Hash(NULL, str)) == -1);
    TEST_CHECK((hash = HT_Hash(ht, str)) != -1);
    HT_Destroy(ht);
    destroyString(str);
}
void test_HT_Insert(void){

    LLNode lln;
    char *str = createString("aaaa");
    HashTable ht = HT_Create(StringType, &djb2, &destroyString, &compareString);

    TEST_CHECK((lln = HT_Insert(NULL, NULL)) == NULL);
    TEST_CHECK((lln = HT_Insert(ht, NULL)) == NULL);
    TEST_CHECK((lln = HT_Insert(NULL, str)) == NULL);
    TEST_CHECK((lln = HT_Insert(ht, str)) != NULL);
    TEST_CHECK(ht->size == 1);
    TEST_CHECK(compareString(lln->data, str) == 0);
    HT_Destroy(ht);
}
void test_HT_Search(void){

    LLNode lln;
    char *str = createString("aaaa");
    HashTable ht = HT_Create(StringType, &djb2, &destroyString, &compareString);

    TEST_CHECK((lln = HT_Search(NULL, NULL)) == NULL);
    TEST_CHECK((lln = HT_Search(ht, NULL)) == NULL);
    TEST_CHECK((lln = HT_Search(NULL, str)) == NULL);
    TEST_CHECK((lln = HT_Search(ht, str)) == NULL);
    HT_Insert(ht, str);
    TEST_CHECK((lln = HT_Search(ht, str)) != NULL);
    TEST_CHECK(compareString(lln->data, str) == 0);
    HT_Destroy(ht);
}
void test_HT_Rehash(void){

    HashTable ht = HT_Create(StringType, &djb2, &destroyString, &compareString);
    TEST_CHECK(HT_Rehash(NULL) == NULL);
    TEST_CHECK(HT_Rehash(ht) != NULL);
    TEST_CHECK(ht->capacity == 97);     // HT Capacity is equal to the second prime
    HT_Destroy(ht);
}
void test_HT_ToList(void){
    
    LList ll;
    char *str = createString("aaaa");
    HashTable ht = HT_Create(StringType, &djb2, &destroyString, &compareString);
    HT_Insert(ht, str);
    TEST_CHECK((ll = HT_ToList(NULL, NULL)) == NULL);
    TEST_CHECK((ll = HT_ToList(ht, NULL)) != NULL);
    TEST_CHECK(LL_GetSize(ll) == 1);
    HT_Destroy(ht);
    LL_Destroy(ll);
}
void test_HT_GetSize(void){

    char *str = createString("aaaa");
    HashTable ht = HT_Create(StringType, &djb2, &destroyString, &compareString);
    TEST_CHECK(HT_GetSize(NULL) == -1);
    TEST_CHECK(HT_GetSize(ht) == 0);
    HT_Insert(ht, str);
    TEST_CHECK(HT_GetSize(ht) == 1);
    HT_Destroy(ht);
}
void test_HT_GetCapacity(void){

    HashTable ht = HT_Create(StringType, &djb2, &destroyString, &compareString);
    TEST_CHECK(HT_GetCapacity(NULL) == -1);
    TEST_CHECK(HT_GetCapacity(ht) == 53);
    HT_Rehash(ht);
    TEST_CHECK(HT_GetCapacity(ht) == 97);
    HT_Destroy(ht);
}
void test_HT_Print(void){

    char *str = createString("test");
    HashTable ht = HT_Create(StringType, &djb2, &destroyString, &compareString);
    HT_Insert(ht, str);
    TEST_CHECK(HT_Print(NULL) == 1);
    TEST_CHECK(HT_Print(ht) == 0);
    HT_Destroy(ht);
}
void test_HT_Destroy(void){

    char *str = createString("test");
    HashTable ht = HT_Create(StringType, &djb2, &destroyString, &compareString);
    HT_Insert(ht, str);
    TEST_CHECK(HT_Destroy(NULL) == 1);
    TEST_CHECK(HT_Destroy(ht) == 0);
}

TEST_LIST = {

    { "HT_Create", test_HT_Create },
    { "HT_Hash", test_HT_Hash },
    { "HT_Insert", test_HT_Insert },
    { "HT_Search", test_HT_Search },
    { "HT_Rehash", test_HT_Rehash },
    { "HT_ToList", test_HT_ToList },
    { "HT_GetSize", test_HT_GetSize },
    { "HT_GetCapacity", test_HT_GetCapacity },
    { "HT_Print", test_HT_Print },
    { "HT_Destroy", test_HT_Destroy },
    { NULL, NULL }
};