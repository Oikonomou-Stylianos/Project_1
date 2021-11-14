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
// File : BKTree_test.c
///////////////////////////////////

#include "acutest.h"

#include "BKTree.h"
#include "EntryList.h"
#include "DataStructs.h"
#include "core.h"

void test_BKT_Create(void){

    BKTree bkt;
    TEST_CHECK((bkt = BKT_Create(MT_EXACT_MATCH)) == NULL);
    TEST_CHECK((bkt = BKT_Create(MT_HAMMING_DIST)) != NULL);
    BKT_Destroy(bkt);
    TEST_CHECK((bkt = BKT_Create(MT_EDIT_DIST)) != NULL);
    BKT_Destroy(bkt);
}
void test_BKT_CreateNode(void){

    Entry *e = create_entry("abcd", NULL);
    TEST_CHECK(BKT_CreateNode(NULL) == NULL);
    BKTreeNode bktn = BKT_CreateNode(e);
    TEST_CHECK(bktn != NULL);
    TEST_CHECK(bktn->children != NULL);
    int i;
    for(i = 0; i < MAX_WORD_LENGTH; i++)
        TEST_CHECK(bktn->children[i] == NULL);
    TEST_CHECK(strcmp(bktn->entry->word, e->word) == 0);
    TEST_CHECK(bktn->entry->payload == e->payload);
    BKT_DestroyNode(bktn);
    destroy_entry(e);
}
void test_BKT_Insert(void){

    Entry *e = create_entry("abcd", NULL);
    TEST_CHECK(BKT_Insert(NULL, NULL) == NULL);
    TEST_CHECK(BKT_Insert(NULL, e) == NULL);
    BKTree bkt = BKT_Create(MT_EDIT_DIST);
    TEST_CHECK(BKT_Insert(bkt, NULL) == NULL);
    BKTreeNode bktn;
    TEST_CHECK((bktn = BKT_Insert(bkt, e)) != NULL);
    TEST_CHECK(strcmp(bktn->entry->word, "abcd") == 0);
    BKT_Destroy(bkt);
    destroy_entry(e);
}
void test_BKT_InsertNode(void){

    Entry *e1 = create_entry("abcd", NULL), *e2 = create_entry("abcde", NULL);
    BKTree bkt = BKT_Create(MT_EDIT_DIST);
    BKT_Insert(bkt, e1);
    TEST_CHECK(BKT_InsertNode(NULL, NULL, NULL) == NULL);
    TEST_CHECK(BKT_InsertNode(NULL, NULL, e2) == NULL);
    TEST_CHECK(BKT_InsertNode(NULL, bkt->root, NULL) == NULL);
    TEST_CHECK(BKT_InsertNode(bkt, NULL, NULL) == NULL);
    TEST_CHECK(BKT_InsertNode(bkt, NULL, e2) == NULL);
    TEST_CHECK(BKT_InsertNode(bkt, bkt->root, NULL) == NULL);
    BKTreeNode bktn;
    TEST_CHECK((bktn = BKT_InsertNode(bkt, bkt->root, e2)) != NULL);
    TEST_CHECK(strcmp(bktn->entry->word, "abcde") == 0);
    BKT_Destroy(bkt);
    destroy_entry(e1); destroy_entry(e2);
}
void test_BKT_Search(void){

    List *l;
    Entry *e = create_entry("abcd", NULL);
    TEST_CHECK(BKT_Search(NULL, NULL, 0) == NULL);
    TEST_CHECK(BKT_Search(NULL, NULL, 1) == NULL);
    TEST_CHECK(BKT_Search(NULL, "abcd", 0) == NULL);
    BKTree bkt = BKT_Create(MT_EDIT_DIST);
    TEST_CHECK(BKT_Search(bkt, NULL, 0) == NULL);
    TEST_CHECK(BKT_Search(bkt, "abcd", 0) == NULL);
    TEST_CHECK(BKT_Search(bkt, NULL, 1) == NULL);
    TEST_CHECK(BKT_Search(NULL, "abcd", 1) == NULL);
    TEST_CHECK(BKT_Search(bkt, "abcd", 1) == NULL);  // Empty BKT, bkt->root == NULL
    BKT_Insert(bkt, e);
    TEST_CHECK((l = BKT_Search(bkt, "abcd", 1)) != NULL); // Successful search with 1 word found
    TEST_CHECK(l->head != NULL);
    destroy_entry_list(l);
    TEST_CHECK((l = BKT_Search(bkt, "abcdefg", 1)) != NULL); // Successful search with 0 words found
    TEST_CHECK(l->size == 0);
    destroy_entry_list(l);
    BKT_Destroy(bkt);
    destroy_entry(e);
}
void test_BKT_Destroy(void){

    TEST_CHECK(BKT_Destroy(NULL) == 1);
    BKTree bkt = BKT_Create(MT_EDIT_DIST);
    TEST_CHECK(BKT_Destroy(bkt) == 0);
}
void test_BKT_DestroyNode(void){

    Entry *e = create_entry("abcd", NULL);
    TEST_CHECK(BKT_DestroyNode(NULL) == 1);
    BKTreeNode bktn = BKT_CreateNode(e);
    TEST_CHECK(BKT_DestroyNode(bktn) == 0);
    destroy_entry(e);
}

TEST_LIST = {
    
	{ "BKT_Create", test_BKT_Create },
	{ "BKT_CreateNode", test_BKT_CreateNode },
	{ "BKT_Insert", test_BKT_Insert },
	{ "BKT_InsertNode", test_BKT_InsertNode },
	{ "BKT_Search", test_BKT_Search },
	{ "BKT_Destroy", test_BKT_Destroy },
	{ "BKT_DestroyNode", test_BKT_DestroyNode },
	{ NULL, NULL }
};