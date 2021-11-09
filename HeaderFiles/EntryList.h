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

typedef struct {
    char *word;
    void *payload;
} Entry;

typedef struct lnode {
    void *item;
    struct lnode *next;
} listnode;

typedef struct {
    listnode *head;
    listnode *tail;
} List;

typedef enum { 
    entry,          //Can be expanded
    other,
} ListType;

List *create_list(void);
void destroy_node(listnode *, ListType);
void destroy_list(List *, ListType);
List *insert_list(List *, void *);
ErrorCode create_entry_list(List *);
ErrorCode create_entry(const char *, void *, Entry *);
ErrorCode destroy_entry(Entry *);
unsigned int get_number_entries(const List *);
ErrorCode add_entry(List *, const Entry *); //Prefer to use create_entry as second argument
Entry *get_first(const List *);
Entry *get_next(const listnode *);
ErrorCode destroy_entry_list(List *);