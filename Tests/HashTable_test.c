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

#include "acutest.h"

#include "HashTable.h"
#include "WordList.h"

void test_hash_string(void){

    TEST_CHECK(hash_string(NULL) == -1);
    TEST_CHECK(hash_string("abcd") != -1);
}
void test_HT_Create(void){

    HashTable ht;
    TEST_CHECK((ht = HT_Create()) != NULL);
    TEST_CHECK(ht->capacity == 53); // First prime
    TEST_CHECK(ht->size == 0); // First prime
    HT_Destroy(ht);
}
void test_HT_Insert(void){

    WLNode wln;
    HashTable ht = HT_Create();
    TEST_CHECK(HT_Insert(NULL, NULL) == NULL);
    TEST_CHECK(HT_Insert(ht, NULL) == NULL);
    TEST_CHECK(HT_Insert(NULL, "abcd") == NULL);
    TEST_CHECK((wln = HT_Insert(ht, "abcd")) != NULL);
    TEST_CHECK(strcmp(wln->word, "abcd") == 0);
    TEST_CHECK((wln = HT_Insert(ht, "abcd")) == NULL); // Insert a word that already exists in the HashTable
    HT_Destroy(ht);
}
void test_HT_Rehash(void){

    HashTable ht = HT_Create();
    TEST_CHECK(HT_Rehash(NULL) == NULL);
    TEST_CHECK(ht->capacity == 53); // Rehash failed, capacity remains the same 
    TEST_CHECK((ht = HT_Rehash(ht)) != NULL);
    TEST_CHECK(ht->capacity == 97); // Rehash succeeded, capacity becomes equal to the second prime
    HT_Destroy(ht);
}
void test_HT_InsertFromFile(void){

    HashTable ht = HT_Create();
    TEST_CHECK(HT_InsertFromFile(NULL, NULL) == NULL);
    TEST_CHECK(HT_InsertFromFile(ht, NULL) == NULL);
    TEST_CHECK(HT_InsertFromFile(NULL, "./Tests/HashTable_test.c") == NULL);
    TEST_CHECK(HT_InsertFromFile(ht, "./hlahslkdhla.txt") == NULL); // Invalid file name
    TEST_CHECK(HT_InsertFromFile(ht, "./Tests/HashTable_test.c") != NULL); // Valid file name
    HT_Destroy(ht);
}
void test_HT_ToList(void){

    HashTable ht = HT_Create();
    WList wl;
    TEST_CHECK(HT_ToList(NULL) == NULL);
    TEST_CHECK((wl = HT_ToList(ht)) != NULL);
    TEST_CHECK(WL_GetSize(wl) == 0);
    WL_Destroy(wl);
    HT_Insert(ht, "abcd");
    TEST_CHECK((wl = HT_ToList(ht)) != NULL);
    TEST_CHECK(WL_GetSize(wl) != 0);
    WL_Destroy(wl);
    HT_Destroy(ht);
}
void test_HT_Destroy(void){

    HashTable ht = HT_Create();
    TEST_CHECK(HT_Destroy(NULL) == 1);
    TEST_CHECK(HT_Destroy(ht) == 0);
}
void test_deduplicate(void){

    WList wl;
    TEST_CHECK(deduplicate(NULL) == NULL);
    TEST_CHECK((wl = deduplicate("./aushgdkj.txt")) == NULL); // Invalid file name
    WL_Destroy(wl);
    TEST_CHECK((wl = deduplicate("./Tests/HashTable_test.c")) != NULL); // Invalid file name
    WL_Destroy(wl);
}

TEST_LIST = {

    { "hash_string", test_hash_string},
    { "HT_Create", test_HT_Create},
    { "HT_Insert", test_HT_Insert},
    { "HT_Rehash", test_HT_Rehash},
    { "HT_InsertFromFile", test_HT_InsertFromFile},
    { "HT_ToList", test_HT_ToList},
    { "HT_Destroy", test_HT_Destroy},
    { "deduplicate", test_deduplicate},
    { NULL, NULL }
};