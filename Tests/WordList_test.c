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
// File : WordList_test.c
///////////////////////////////////

#include "acutest.h"
#include "core.h"

#include "WordList.h"

void test_WL_Create(void){

    WList wl;
    TEST_CHECK((wl = WL_Create()) != NULL);
    WL_Destroy(wl);
}
void test_WL_Insert(void){

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
void test_WL_InsertSortUnique(void){

    WList wl = WL_Create();
    WLNode wln;
    TEST_CHECK(WL_InsertSortUnique(NULL, NULL) == NULL);
    TEST_CHECK(WL_InsertSortUnique(NULL, "abcd") == NULL);
    TEST_CHECK(WL_InsertSortUnique(wl, NULL) == NULL);
    TEST_CHECK((wln = WL_InsertSortUnique(wl, "abcd")) != NULL); // Insert in empty WList
    TEST_CHECK(strcmp(wln->word, "abcd") == 0);
    TEST_CHECK(wln == wl->head);
    TEST_CHECK(wln == wl->tail);
    TEST_CHECK((wln = WL_InsertSortUnique(wl, "abc")) != NULL); // Insert at the head of a non empty WList
    TEST_CHECK(strcmp(wln->word, "abc") == 0);
    TEST_CHECK(wln == wl->head);
    TEST_CHECK((wln = WL_InsertSortUnique(wl, "abc")) == NULL); // Insert a word that already exists in the head of a WList
    TEST_CHECK((wln = WL_InsertSortUnique(wl, "abcdef")) != NULL); // Insert at the tail of a non empty WList
    TEST_CHECK(strcmp(wln->word, "abcdef") == 0);
    TEST_CHECK(wln == wl->tail);
    TEST_CHECK((wln = WL_InsertSortUnique(wl, "abcde")) != NULL); // Insert behind a WLNode of a non empty WList
    TEST_CHECK(strcmp(wln->word, "abcde") == 0);
    TEST_CHECK((wln = WL_InsertSortUnique(wl, "abcde")) == NULL); // Insert a word that already exists in a WList
    WL_Destroy(wl);
}
void test_WL_RemoveFirst(void){

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
void test_WL_GetFirst(void){

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
void test_WL_Print(void){

    TEST_CHECK(WL_Print(NULL) == 1);
    WList wl = WL_Create();
    TEST_CHECK(WL_Print(wl) == 0);
    WL_Destroy(wl);
}
void test_WL_IsEmpty(void){

    TEST_CHECK(WL_IsEmpty(NULL) == -1);
    WList wl = WL_Create();
    TEST_CHECK(WL_IsEmpty(wl) == 0);
    WL_Insert(wl, "abcd");
    TEST_CHECK(WL_IsEmpty(wl) == 1);
    WL_Destroy(wl);
}
void test_WL_GetSize(void){

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
void test_WL_Destroy(void){

    TEST_CHECK(WL_Destroy(NULL) == 1);
    WList wl = WL_Create();
    TEST_CHECK(WL_Destroy(wl) == 0);
}

TEST_LIST = {

    { "WL_Create", test_WL_Create },
	{ "WL_Insert", test_WL_Insert },
	{ "WL_InsertSortUnique", test_WL_InsertSortUnique },
    { "WL_RemoveFirst", test_WL_RemoveFirst },
    { "WL_GetFirst", test_WL_GetFirst },
    { "WL_Print", test_WL_Print },
    { "WL_IsEmpty", test_WL_IsEmpty },
    { "WL_GetSize", test_WL_GetSize },
	{ "WL_Destroy", test_WL_Destroy },
	{ NULL, NULL }
};