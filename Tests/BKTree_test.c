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

void test_BKT_Create(void){

    BKTree bkt = BKT_Create();
    TEST_CHECK(bkt != NULL);
    BKT_Destroy(bkt);
}

void test_BKT_CreateNode(void){

    TEST_CHECK(BKT_CreateNode(NULL) == NULL);
    char *a = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    strcpy(a, "abcd");
    BKTreeNode bktn = BKT_CreateNode(a);
    TEST_CHECK(bktn != NULL);
    TEST_CHECK(bktn->children != NULL);
    int i;
    for(i = 0; i < MAX_WORD_LENGTH; i++)
        TEST_CHECK(bktn->children[i] == NULL);
    BKT_DestroyNode(bktn);
    free(a);
}

void test_BKT_Insert(void){

    TEST_CHECK(BKT_Insert(NULL, NULL) == NULL);
    char *a = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    strcpy(a, "abcd");
    TEST_CHECK(BKT_Insert(NULL, a) == NULL);
    BKTree bkt = BKT_Create();
    TEST_CHECK(BKT_Insert(bkt, NULL) == NULL);
    TEST_CHECK(BKT_Insert(bkt, a) != NULL);
    BKT_Destroy(bkt);
    free(a);
}

void test_BKT_InsertNode(void){

    TEST_CHECK(BKT_InsertNode(NULL, NULL) == NULL);
    char *a = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    strcpy(a, "abcd");
    TEST_CHECK(BKT_InsertNode(NULL, a) == NULL);
    BKTree bkt = BKT_Create();
    BKT_Insert(bkt, a);
    TEST_CHECK(BKT_InsertNode(bkt->root, NULL) == NULL);    
    char *b = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    strcpy(b, "abcde");
    TEST_CHECK(BKT_InsertNode(bkt->root, b) != NULL);
    BKT_Destroy(bkt);
    free(a); free(b);
}

void test_BKT_Search(void){

    TEST_CHECK(BKT_Search(NULL, NULL, 0) == NULL);
    TEST_CHECK(BKT_Search(NULL, NULL, 1) == NULL);
    char *a = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    strcpy(a, "abcd");
    TEST_CHECK(BKT_Search(NULL, a, 0) == NULL);
    BKTree bkt = BKT_Create();
    TEST_CHECK(BKT_Search(bkt, NULL, 0) == NULL);
    TEST_CHECK(BKT_Search(bkt, a, 0) == NULL);
    TEST_CHECK(BKT_Search(bkt, NULL, 1) == NULL);
    TEST_CHECK(BKT_Search(NULL, a, 0) == NULL);
    TEST_CHECK(BKT_Search(bkt, a, 1) == NULL);  // Empty BKT, bkt->root == NULL
    BKT_Insert(bkt, a);
    WList wl = BKT_Search(bkt, "aaaa", 1);
    TEST_CHECK( wl != NULL);
    TEST_CHECK( WL_IsEmpty(wl) == 0);
    WL_Destroy(wl);
    wl = BKT_Search(bkt, "abcc", 1);
    TEST_CHECK( WL_IsEmpty(wl) == 1);
    WL_Destroy(wl);
    BKT_Destroy(bkt);
    free(a);
}


TEST_LIST = {
    
	{ "BKT_Create", test_BKT_Create },
	{ "BKT_CreateNode", test_BKT_CreateNode },
	{ "BKT_Insert", test_BKT_Insert },
	{ "BKT_InsertNode", test_BKT_InsertNode },
	{ "BKT_Search", test_BKT_Search },
	{ NULL, NULL }
};