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

#include "WordList.h"

void test_create(void){

    WList wl;
    TEST_CHECK((wl = WL_Create()) != NULL);
    WL_Destroy(wl);
}

void test_destroy(void){

    WList wl = WL_Create();
    TEST_CHECK(!(WL_Destroy(wl)));
}

void test_insert(void){

    WList wl = WL_Create();
    WLNode first, second, node;
    char *str = NULL;
    TEST_CHECK(!WL_Insert(wl, str));
    str = malloc((MAX_WORD_LENGTH+1)*sizeof(char));
    strcpy(str, "headtesting");
    TEST_CHECK((first = WL_Insert(wl, str)) != NULL);
    strcpy(str, "nexttesting");
    TEST_CHECK((second = WL_Insert(wl, str)) != NULL);
    node = WL_GetFirst(wl);
    TEST_CHECK(first == node);
    WL_RemoveFirst(wl);
    node = WL_GetFirst(wl);
    TEST_CHECK(second == node);
    WL_Destroy(wl);
    free(str);

    TEST_CHECK(!WL_Insert(NULL, "adsad"));
}

void test_getfirst(void){

    WList wl = WL_Create();
    TEST_CHECK(wl->head == WL_GetFirst(wl));
    WL_Insert(wl, "testing");
    TEST_CHECK(wl->head == WL_GetFirst(wl));
    WL_Insert(wl, "testingagain");
    TEST_CHECK(wl->head == WL_GetFirst(wl));
    WL_RemoveFirst(wl);
    TEST_CHECK(wl->head == WL_GetFirst(wl));
    WL_Destroy(wl);

    TEST_CHECK(!WL_GetFirst(NULL));
}

void test_removefirst(void){

    TEST_CHECK(WL_RemoveFirst(NULL));
    WList wl = WL_Create();
    TEST_CHECK(WL_RemoveFirst(wl));
    WL_Insert(wl, "testing");
    TEST_CHECK(!strcmp(wl->head->word, "testing"));
    TEST_CHECK(!WL_RemoveFirst(wl));
    TEST_CHECK(WL_RemoveFirst(wl));
    WL_Insert(wl, "testingagain");
    WL_Insert(wl, "testingagainagain");
    TEST_CHECK(!strcmp(wl->head->word, "testingagain"));
    TEST_CHECK(!WL_RemoveFirst(wl));
    TEST_CHECK(!strcmp(wl->head->word, "testingagainagain"));
    TEST_CHECK(!WL_RemoveFirst(wl));
    TEST_CHECK(WL_RemoveFirst(wl));
    WL_Destroy(wl);
}

void test_print(void){

    TEST_CHECK(WL_Print(NULL));
    WList wl = WL_Create();
    TEST_CHECK(!WL_Print(wl));
    WL_Destroy(wl);
}

void test_getsize(void){

    TEST_CHECK(WL_GetSize(NULL) == -1);
    WList wl = WL_Create();
    TEST_CHECK(!WL_GetSize(wl));
    WL_Insert(wl, "first");
    TEST_CHECK(WL_GetSize(wl) == 1);
    WL_RemoveFirst(wl);
    TEST_CHECK(!WL_GetSize(wl));
    WL_Insert(wl, "first");
    TEST_CHECK(WL_GetSize(wl) == 1);
    WL_Insert(wl, "second");
    TEST_CHECK(WL_GetSize(wl) == 2);
    WL_Insert(wl, "third");
    TEST_CHECK(WL_GetSize(wl) == 3);
    WL_RemoveFirst(wl);
    TEST_CHECK(WL_GetSize(wl) == 2);
    WL_RemoveFirst(wl);
    TEST_CHECK(WL_GetSize(wl) == 1);
    WL_RemoveFirst(wl);
    TEST_CHECK(!WL_GetSize(wl));
    WL_Destroy(wl);
}

TEST_LIST = {

    { "test_create", test_create },
	{ "test_destroy", test_destroy },
	{ "test_insert", test_insert },
    { "test_getfirst", test_getfirst },
    { "test_removefirst", test_removefirst },
    { "test_print", test_print },
    { "test_getsize", test_getsize },
	{ NULL, NULL }
};