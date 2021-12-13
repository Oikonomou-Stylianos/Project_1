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

#include "BKTree.h"
#include "LinkedList.h"
#include "common_types.h"
#include "constructors.h"
#include "core.h"

void test_BKT_Create(void){
    
    BKTree bkt;
    TEST_CHECK((bkt = BKT_Create(MT_EXACT_MATCH, StringType, &destroyString)) == NULL);
    TEST_CHECK((bkt = BKT_Create(MT_EDIT_DIST, StringType, &destroyString)) != NULL);
    BKT_Destroy(bkt);
}
void test_BKT_CreateNode(void){
    
    char *str = createString("a");
    BKTreeNode bktn;
    TEST_CHECK((bktn = BKT_CreateNode(NULL)) == NULL);
    TEST_CHECK((bktn = BKT_CreateNode(str)) != NULL);
    TEST_CHECK(strcmp((char *)(bktn->data), str) == 0);
    destroyString(bktn->data);
    free(bktn->children);
    free(bktn);
}
void test_BKT_Insert(void){

    char *str = createString("aaaa");
    BKTree bkt = BKT_Create(MT_EDIT_DIST, StringType, &destroyString);
    BKTreeNode bktn;
    TEST_CHECK((bktn = BKT_Insert(NULL, NULL)) == NULL);
    TEST_CHECK((bktn = BKT_Insert(bkt, NULL)) == NULL);
    TEST_CHECK((bktn = BKT_Insert(NULL, str)) == NULL);
    TEST_CHECK((bktn = BKT_Insert(bkt, str)) != NULL);
    TEST_CHECK(bktn == bkt->root);
    TEST_CHECK(strcmp((char *)(bktn->data), str) == 0);
    BKT_Destroy(bkt);
}
void test_BKT_InsertNode(void){

    char *str1 = createString("aaaa"), *str2 = createString("bbbb");
    BKTree bkt = BKT_Create(MT_EDIT_DIST, StringType, &destroyString);
    BKTreeNode bktn;
    BKT_Insert(bkt, str1);
    TEST_CHECK((bktn = BKT_InsertNode(NULL, NULL, NULL)) == NULL);
    TEST_CHECK((bktn = BKT_InsertNode(bkt, NULL, NULL)) == NULL);
    TEST_CHECK((bktn = BKT_InsertNode(NULL, bkt->root, NULL)) == NULL);
    TEST_CHECK((bktn = BKT_InsertNode(NULL, NULL, str2)) == NULL);
    TEST_CHECK((bktn = BKT_InsertNode(bkt, bkt->root, NULL)) == NULL);
    TEST_CHECK((bktn = BKT_InsertNode(bkt, NULL, str2)) == NULL);
    TEST_CHECK((bktn = BKT_InsertNode(NULL, bkt->root, str2)) == NULL);
    TEST_CHECK((bktn = BKT_InsertNode(bkt, bkt->root, str2)) != NULL);
    BKT_Destroy(bkt);
}
void test_BKT_Search(void){
    
    char *str = createString("aaaa");
    BKTree bkt = BKT_Create(MT_EDIT_DIST, StringType, &destroyString);
    BKT_Insert(bkt, str);
    LList ll;
    TEST_CHECK((ll = BKT_Search(NULL, NULL, 0)) == NULL);
    TEST_CHECK((ll = BKT_Search(bkt, NULL, 0)) == NULL);
    TEST_CHECK((ll = BKT_Search(NULL, "aaab", 0)) == NULL);
    TEST_CHECK((ll = BKT_Search(NULL, NULL, 1)) == NULL);
    TEST_CHECK((ll = BKT_Search(bkt, "aaab", 0)) == NULL);
    TEST_CHECK((ll = BKT_Search(NULL, "aaab", 1)) == NULL);
    TEST_CHECK((ll = BKT_Search(bkt, NULL, 1)) == NULL);
    TEST_CHECK((ll = BKT_Search(bkt, "aaab", 1)) != NULL);
    TEST_CHECK(LL_GetSize(ll) == 1);
    LL_Destroy(ll);
    BKT_Destroy(bkt);
}
void test_BKT_Destroy(void){
    
    BKTree bkt = BKT_Create(MT_EDIT_DIST, StringType, &destroyString);
    TEST_CHECK(BKT_Destroy(NULL) == 1);
    TEST_CHECK(BKT_Destroy(bkt) == 0);
}
void test_BKT_DestroyNode(void){

    char *str = createString("aaaa");
    BKTree bkt = BKT_Create(MT_EDIT_DIST, StringType, &destroyString);
    BKT_Insert(bkt, str);
    TEST_CHECK(BKT_DestroyNode(NULL, NULL) == 1);
    TEST_CHECK(BKT_DestroyNode(bkt, NULL) == 1);
    TEST_CHECK(BKT_DestroyNode(NULL, bkt->root) == 1);
    TEST_CHECK(BKT_DestroyNode(bkt, bkt->root) == 0);
    free(bkt);
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