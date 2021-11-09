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

#include "BKTree.h"
#include "core.h"

void test_BKT_Create(void){

    BKTree bkt = BKT_Create(MT_EDIT_DIST);
    TEST_CHECK(bkt != NULL);
    BKT_Destroy(bkt);
}

void test_BKT_CreateNode(void){

    TEST_CHECK(BKT_CreateNode(NULL) == NULL);
    BKTreeNode bktn = BKT_CreateNode("abcd");
    TEST_CHECK(bktn != NULL);
    TEST_CHECK(bktn->children != NULL);
    int i;
    for(i = 0; i < MAX_WORD_LENGTH; i++)
        TEST_CHECK(bktn->children[i] == NULL);
    BKT_DestroyNode(bktn);
}

void test_BKT_Insert(void){

    TEST_CHECK(BKT_Insert(NULL, NULL) == NULL);
    TEST_CHECK(BKT_Insert(NULL, "abcd") == NULL);
    BKTree bkt = BKT_Create(MT_EDIT_DIST);
    TEST_CHECK(BKT_Insert(bkt, NULL) == NULL);
    TEST_CHECK(BKT_Insert(bkt, "abcd") != NULL);
    BKT_Destroy(bkt);
}

void test_BKT_InsertNode(void){

    TEST_CHECK(BKT_InsertNode(NULL, NULL, NULL) == NULL);
    BKTree bkt = BKT_Create(MT_EDIT_DIST);
    BKT_Insert(bkt, "abcd");
    TEST_CHECK(BKT_InsertNode(bkt, NULL, "abcde") == NULL);
    TEST_CHECK(BKT_InsertNode(NULL, bkt->root, NULL) == NULL);
    TEST_CHECK(BKT_InsertNode(NULL, NULL, "abcde") == NULL);
    TEST_CHECK(BKT_InsertNode(bkt, bkt->root, NULL) == NULL);
    TEST_CHECK(BKT_InsertNode(bkt, NULL, "abcde") == NULL);
    TEST_CHECK(BKT_InsertNode(NULL, bkt->root, "abcde") == NULL);
    TEST_CHECK(BKT_InsertNode(bkt, bkt->root, "abcde") != NULL);
    BKT_Destroy(bkt);
}

void test_BKT_Search(void){

    TEST_CHECK(BKT_Search(NULL, NULL, 0) == NULL);
    TEST_CHECK(BKT_Search(NULL, NULL, 1) == NULL);
    TEST_CHECK(BKT_Search(NULL, "abcd", 0) == NULL);
    BKTree bkt = BKT_Create(MT_EDIT_DIST);
    TEST_CHECK(BKT_Search(bkt, NULL, 0) == NULL);
    TEST_CHECK(BKT_Search(bkt, "abcd", 0) == NULL);
    TEST_CHECK(BKT_Search(bkt, NULL, 1) == NULL);
    TEST_CHECK(BKT_Search(NULL, "abcd", 1) == NULL);
    TEST_CHECK(BKT_Search(bkt, "abcd", 1) == NULL);  // Empty BKT, bkt->root == NULL
    BKT_Insert(bkt, "abcd");
    WList wl = BKT_Search(bkt, "aaaa", 1);
    TEST_CHECK( wl != NULL);    // Successful search...
    TEST_CHECK( WL_IsEmpty(wl) == 0);   // ...but no words found
    WL_Destroy(wl);
    wl = BKT_Search(bkt, "abcc", 1);
    TEST_CHECK( wl != NULL);    // Successful search...
    TEST_CHECK( WL_IsEmpty(wl) == 1);   //...with found words
    WL_Destroy(wl);
    BKT_Destroy(bkt);
}

void test_BKT_Destroy(void){

    TEST_CHECK(BKT_Destroy(NULL) == 1);
    BKTree bkt = BKT_Create(MT_EDIT_DIST);
    TEST_CHECK(BKT_Destroy(bkt) == 0);
}

void test_BKT_DestroyNode(void){

    TEST_CHECK(BKT_DestroyNode(NULL) == 1);
    BKTreeNode bktn = BKT_CreateNode("abcd");
    TEST_CHECK(BKT_DestroyNode(bktn) == 0);
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