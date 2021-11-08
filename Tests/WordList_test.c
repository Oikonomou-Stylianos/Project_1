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
    WList temp;
    TEST_CHECK((temp = WL_Create()) != NULL);
    WL_Destroy(temp);
}

void test_destroy(void){
    WList temp = WL_Create();
    TEST_CHECK(!(temp = WL_Destroy(temp)));
}

void test_insert(void){
    WList temp = WL_Create();
    WLNode first, second, node;
    char *str = NULL;
    TEST_CHECK(!WL_Insert(temp, str));
    str = malloc((MAX_WORD_LENGTH+1)*sizeof(char));
    strcpy(str, "headtesting");
    TEST_CHECK((first = WL_Insert(temp, str)));
    strcpy(str, "nexttesting");
    TEST_CHECK((second = WL_Insert(temp, str)));
    node = WL_GetFirst(temp);
    TEST_CHECK(first == node);
    WL_RemoveFirst(temp);
    node = WL_GetFirst(temp);
    TEST_CHECK(second == node);
    WL_Destroy(temp);
    free(str);

    TEST_CHECK(!WL_Insert(NULL, "adsad"));
}

void test_getfirst(void){
    WList temp = WL_Create();
    TEST_CHECK(temp->head == WL_GetFirst(temp));
    WL_Insert(temp, "testing");
    TEST_CHECK(temp->head == WL_GetFirst(temp));
    WL_Insert(temp, "testingagain");
    TEST_CHECK(temp->head == WL_GetFirst(temp));
    WL_RemoveFirst(temp);
    TEST_CHECK(temp->head == WL_GetFirst(temp));
    WL_Destroy(temp);

    TEST_CHECK(!WL_GetFirst(NULL));
}

void test_removefirst(void){
    TEST_CHECK(WL_RemoveFirst(NULL));
    WList temp = WL_Create();
    TEST_CHECK(WL_RemoveFirst(temp));
    WL_Insert(temp, "testing");
    TEST_CHECK(!strcmp(temp->head->word, "testing"));
    TEST_CHECK(!WL_RemoveFirst(temp));
    TEST_CHECK(WL_RemoveFirst(temp));
    WL_Insert(temp, "testingagain");
    WL_Insert(temp, "testingagainagain");
    TEST_CHECK(!strcmp(temp->head->word, "testingagain"));
    TEST_CHECK(!WL_RemoveFirst(temp));
    TEST_CHECK(!strcmp(temp->head->word, "testingagainagain"));
    TEST_CHECK(!WL_RemoveFirst(temp));
    TEST_CHECK(WL_RemoveFirst(temp));
    WL_Destroy(temp);
}

void test_print(void){
    TEST_CHECK(WL_Print(NULL));
    WList temp = WL_Create();
    TEST_CHECK(!WL_Print(temp));
    WL_Destroy(temp);
}

void test_getsize(void){
    TEST_CHECK(WL_getSize(NULL) == -1);
    WList temp = WL_Create();
    TEST_CHECK(!WL_getSize(temp));
    WL_Insert(temp, "first");
    TEST_CHECK(WL_getSize(temp) == 1);
    WL_RemoveFirst(temp);
    TEST_CHECK(!WL_getSize(temp));
    WL_Insert(temp, "first");
    TEST_CHECK(WL_getSize(temp) == 1);
    WL_Insert(temp, "second");
    TEST_CHECK(WL_getSize(temp) == 2);
    WL_Insert(temp, "third");
    TEST_CHECK(WL_getSize(temp) == 3);
    WL_RemoveFirst(temp);
    TEST_CHECK(WL_getSize(temp) == 2);
    WL_RemoveFirst(temp);
    TEST_CHECK(WL_getSize(temp) == 1);
    WL_RemoveFirst(temp);
    TEST_CHECK(!WL_getSize(temp));
    WL_Destroy(temp);
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