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

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#include "acutest.h"

#include "EntryList.h"
#include "core.h"

void test_create_list(void){
    List *temp;
    TEST_CHECK((temp = create_list()) != NULL);
    TEST_CHECK(!(temp->head) && !(temp->tail));
    destroy_list(temp, other);
}

void test_destroy_node(void){
    listnode *temp = malloc(sizeof(listnode));
    if (!temp) return;
    TEST_CHECK(destroy_node(NULL, other) == EC_FAIL);
    TEST_CHECK(destroy_node(NULL, entry) == EC_FAIL);
    TEST_CHECK(destroy_node(temp, entry) == EC_SUCCESS);
    temp = malloc(sizeof(listnode));
    TEST_CHECK(destroy_node(temp, other) == EC_SUCCESS);

    temp = malloc(sizeof(listnode));
    if (!temp) return;
    create_entry("test", NULL, temp->data);
    TEST_CHECK(destroy_node(temp, entry) == EC_SUCCESS);
}

void test_destroy_list(void){
    TEST_CHECK(destroy_list(NULL, entry) == EC_FAIL);
    TEST_CHECK(destroy_list(NULL, other) == EC_FAIL);

    List *list = create_list();
    if (!list) return;
    TEST_CHECK(destroy_list(list, entry) == EC_SUCCESS);
    list = create_list();
    if (!list) return;
    TEST_CHECK(destroy_list(list, other) == EC_SUCCESS);

    list = create_list();
    if (!list) return;
    int *x = (int *)malloc(sizeof(int )); *x = 5;
    printf("OK\n");
    insert_list(list, (void *)x);
    printf("OK\n");
    TEST_CHECK(destroy_list(list, other) == EC_SUCCESS);

    list = create_list();
    if (!list) return;
    *x = 5;
    insert_list(list, x);
    *x = 6;
    insert_list(list, x);
    *x = 7;
    insert_list(list, x);
    TEST_CHECK(destroy_list(list, other) == EC_SUCCESS);
    free(x);
}

void test_insert_list(void){
    List *list;
    int *x = (int *)malloc(sizeof(int )); *x = 5;
    TEST_CHECK(!insert_list(NULL, NULL));
    TEST_CHECK(!insert_list(NULL, x));
    list = create_list();
    TEST_CHECK(insert_list(list, x) == list);
    printf("OK\n");
    TEST_CHECK(insert_list(list, NULL) == list);
    TEST_CHECK(insert_list(list, x) == list);
    TEST_CHECK(list->head->data == x);
    TEST_CHECK(!(list->head->next->data));
    TEST_CHECK(list->head->next->next->data == x);
    TEST_CHECK(!(list->head->next->next->next));
    destroy_list(list, other);
    free(x);
}

void test_create_entry_list(void){
    List *list = NULL;
    TEST_CHECK(create_entry_list(list) == EC_SUCCESS);
    TEST_CHECK(!list);
    destroy_entry_list(list);
}

void test_create_entry(void){
    Entry *entry = (Entry *)1;
    char *word;
    TEST_CHECK(create_entry(NULL, NULL, entry) == EC_FAIL);
    TEST_CHECK(!entry);
    TEST_CHECK(create_entry("test", NULL, entry) == EC_SUCCESS);
    TEST_CHECK(!strcmp("test", entry->word) && !(entry->payload));
    destroy_entry(entry);
    if (!(word = malloc(10*sizeof(char)))) return;
    strcpy(word, "testing");
    TEST_CHECK(create_entry(word, NULL, entry) == EC_SUCCESS);
    TEST_CHECK(!strcmp(word, entry->word) && !(entry->payload));
    free(word);
    destroy_entry(entry);
}

void test_destroy_entry(void){
    Entry *entry = NULL;
    TEST_CHECK(destroy_entry(NULL) == EC_FAIL);
    if (create_entry("test", NULL, entry) != EC_SUCCESS) return;
    TEST_CHECK(destroy_entry(entry) == EC_SUCCESS);
}

void test_get_number_entries(void){
    List *l = NULL;
    if (create_entry_list(l) != EC_SUCCESS) return;
    TEST_CHECK(!get_number_entries(NULL));
    TEST_CHECK(!get_number_entries(l));
    Entry *entry = NULL;
    create_entry("test", NULL, entry);
    add_entry(l, entry);
    TEST_CHECK(get_number_entries(l) == 1);
    create_entry("testi", NULL, entry);
    add_entry(l, entry);
    TEST_CHECK(get_number_entries(l) == 2);
    create_entry("testin", NULL, entry);
    add_entry(l, entry);
    TEST_CHECK(get_number_entries(l) == 3);
    destroy_entry_list(l);
}

void test_add_entry(void){
    List *list = NULL; Entry *entry = NULL;
    create_entry("test", NULL, entry);
    TEST_CHECK(add_entry(NULL, NULL) == EC_FAIL);
    TEST_CHECK(add_entry(NULL, entry) == EC_FAIL);
    create_entry_list(list);
    TEST_CHECK(add_entry(list, entry) == EC_SUCCESS);
    TEST_CHECK(add_entry(list, NULL) == EC_SUCCESS);
    destroy_entry_list(list);
}

void test_get_first(void){
    List *list = NULL; Entry *entry = NULL, *entry2 = NULL;
    TEST_CHECK(!get_first(NULL));
    create_entry_list(list);
    TEST_CHECK(!get_first(list));
    create_entry("test", NULL, entry);
    add_entry(list, entry);
    TEST_CHECK(get_first(list) == entry);
    create_entry("testing", NULL, entry2);
    add_entry(list, entry2);
    TEST_CHECK(get_first(list) == entry);
    destroy_entry_list(list);
}

void test_get_next(void){
    List *list = NULL;
    TEST_CHECK(!get_next(NULL));
    create_entry_list(list);
    TEST_CHECK(!get_next(list->head));
    TEST_CHECK(!get_next(list->tail));
    Entry *entry = NULL;

    create_entry("test", NULL, entry);
    add_entry(list, entry);
    TEST_CHECK(!strcmp(get_next(list->head)->word, "test"));
    TEST_CHECK(!strcmp(get_next(list->tail)->word, "test"));

    create_entry("testi", NULL, entry);
    add_entry(list, entry);
    TEST_CHECK(!strcmp(get_next(list->head)->word, "test"));
    TEST_CHECK(!strcmp(get_next(list->tail)->word, "testi"));

    create_entry("testin", NULL, entry);
    add_entry(list, entry);
    TEST_CHECK(!strcmp(get_next(list->head)->word, "test"));
    TEST_CHECK(!strcmp(get_next(list->tail)->word, "testin"));
    destroy_entry_list(list);
}

void test_destroy_entry_list(void){
    List *list = NULL;
    create_entry_list(list);
    TEST_CHECK(destroy_entry_list(NULL) == EC_FAIL);
    TEST_CHECK(destroy_entry_list(list) == EC_SUCCESS);

    create_entry_list(list);
    Entry *entry = NULL;
    create_entry("test", NULL, entry);
    add_entry(list, entry);
    create_entry("testi", NULL, entry);
    add_entry(list, entry);
    TEST_CHECK(destroy_entry_list(list) == EC_SUCCESS);
}

TEST_LIST = {

    { "test_create_list", test_create_list },
    { "test_destroy_node", test_destroy_node },
    { "test_insert_list", test_insert_list },
    { "test_destroy_list", test_destroy_list },
    { "test_create_entry_list", test_create_entry_list },
    { "test_create_entry", test_create_entry },
    { "test_destroy_entry", test_destroy_entry },
    { "test_get_number_entries", test_get_number_entries },
    { "test_add_entry", test_add_entry },
    { "test_get_first", test_get_first },
    { "test_get_next", test_get_next },
    { "test_destroy_entry_list", test_destroy_entry_list },
    { NULL, NULL }
};