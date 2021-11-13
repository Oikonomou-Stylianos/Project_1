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

#pragma once

#include "core.h"

typedef struct {
    char *word;
    void *payload;
} Entry;

typedef struct lnode {
    void *data;
    struct lnode *next;
} listnode;

typedef struct {
    listnode *head;
    listnode *tail;
    unsigned int size;
} List;

typedef enum { 
    entry,          //Can be expanded
    other,
} ListType;

typedef BKTree *Index;

List *create_list(void);
ErrorCode destroy_node(listnode *, ListType);
ErrorCode destroy_list(List *, ListType);
List *insert_list(List *, void *);

ErrorCode create_entry_list(List **);
Entry *create_entry(const char *, void *);
ErrorCode destroy_entry(Entry *);
unsigned int get_number_entries(const List *);
ErrorCode add_entry(List *, const Entry *); //Prefer to use create_entry as second argument
Entry *get_first(const List *);
Entry *get_next(const listnode *);
ErrorCode destroy_entry_list(List *);
Entry *copy_entry(Entry *);
void print_entry_list(List *);
ErrorCode build_entry_index(const List *, MatchType, Index);
ErrorCode lookup_entry_index(const char *, Index, int, List **);