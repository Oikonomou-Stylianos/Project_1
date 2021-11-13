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
#include "core.h"

#include "CandidateList.h"

void test_CL_Create(void){

    CList cl;
    TEST_CHECK((cl = CL_Create()) != NULL);
    CL_Destroy(cl);
}

void test_CL_Insert(void){

    TEST_CHECK(!CL_Insert(NULL, NULL));
    CList cl = CL_Create();
    CLNode first, second, node;
    BKTreeNode *bktn = NULL, *bktn2;
    TEST_CHECK(!CL_Insert(cl, bktn));
    bktn = malloc(sizeof(BKTreeNode));
    bktn2 = malloc(sizeof(BKTreeNode));
    TEST_CHECK((first = CL_Insert(cl, bktn)) != NULL);
    TEST_CHECK((second = CL_Insert(cl, bktn2)) != NULL);
    node = CL_GetFirst(cl);
    TEST_CHECK(first == node);
    CL_RemoveFirst(cl);
    node = CL_GetFirst(cl);
    TEST_CHECK(second == node);
    CL_Destroy(cl);
    free(bktn);
    free(bktn2);

}

void test_CL_RemoveFirst(void){

    TEST_CHECK(CL_RemoveFirst(NULL));
    CList cl = CL_Create();
    TEST_CHECK(CL_RemoveFirst(cl));
    BKTreeNode *bktn1 = malloc(sizeof(BKTreeNode));
    BKTreeNode *bktn2 = malloc(sizeof(BKTreeNode));
    CL_Insert(cl, bktn1);
    TEST_CHECK(cl->head->candidate == bktn1);
    TEST_CHECK(!CL_RemoveFirst(cl));
    TEST_CHECK(CL_RemoveFirst(cl));
    CL_Insert(cl, bktn1);
    CL_Insert(cl, bktn2);
    TEST_CHECK(cl->head->candidate == bktn1);
    TEST_CHECK(!CL_RemoveFirst(cl));
    TEST_CHECK(cl->head->candidate == bktn2);
    TEST_CHECK(!CL_RemoveFirst(cl));
    TEST_CHECK(CL_RemoveFirst(cl));
    CL_Destroy(cl);
    free(bktn1);
    free(bktn2);
}

void test_CL_GetFirst(void){

    CList cl = CL_Create();
    BKTreeNode *bktn = malloc(sizeof(BKT_CreateNode));
    TEST_CHECK(cl->head == CL_GetFirst(cl));
    CL_Insert(cl, bktn);
    TEST_CHECK(cl->head == CL_GetFirst(cl));
    CL_Insert(cl, bktn);
    TEST_CHECK(cl->head == CL_GetFirst(cl));
    CL_RemoveFirst(cl);
    TEST_CHECK(cl->head == CL_GetFirst(cl));
    CL_Destroy(cl);
    free(bktn);

    TEST_CHECK(!CL_GetFirst(NULL));
}

void test_CL_IsEmpty(void){

    TEST_CHECK(CL_IsEmpty(NULL));
    CList cl = CL_Create();
    TEST_CHECK(!CL_IsEmpty(cl));
    BKTreeNode *bktn = malloc(sizeof(BKTreeNode));
    CL_Insert(cl, bktn);
    TEST_CHECK(CL_IsEmpty(cl));
    CL_Destroy(cl);
    free(bktn);
}

void test_CL_GetSize(void){

    TEST_CHECK(CL_GetSize(NULL) == -1);
    CList cl = CL_Create();
    BKTreeNode *bktn = malloc(sizeof(BKTreeNode));
    TEST_CHECK(!CL_GetSize(cl));
    CL_Insert(cl, bktn);
    TEST_CHECK(CL_GetSize(cl) == 1);
    CL_RemoveFirst(cl);
    TEST_CHECK(!CL_GetSize(cl));
    CL_Insert(cl, bktn);
    TEST_CHECK(CL_GetSize(cl) == 1);
    CL_Insert(cl, bktn);
    TEST_CHECK(CL_GetSize(cl) == 2);
    CL_Insert(cl, bktn);
    TEST_CHECK(CL_GetSize(cl) == 3);
    CL_RemoveFirst(cl);
    TEST_CHECK(CL_GetSize(cl) == 2);
    CL_RemoveFirst(cl);
    TEST_CHECK(CL_GetSize(cl) == 1);
    CL_RemoveFirst(cl);
    TEST_CHECK(!CL_GetSize(cl));
    CL_Destroy(cl);
    free(bktn);
}

void test_CL_Destroy(void){

    TEST_CHECK(CL_Destroy(NULL));
    CList cl = CL_Create();
    TEST_CHECK(!(CL_Destroy(cl)));
}

TEST_LIST = {

    { "CL_Create", test_CL_Create },
	{ "CL_Insert", test_CL_Insert },
    { "CL_RemoveFirst", test_CL_RemoveFirst },
    { "CL_GetFirst", test_CL_GetFirst },
    { "CL_IsEmpty", test_CL_IsEmpty },
    { "CL_GetSize", test_CL_GetSize },
	{ "CL_Destroy", test_CL_Destroy },
	{ NULL, NULL }
};