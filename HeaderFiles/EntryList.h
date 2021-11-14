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

#include "BKTree.h"
#include "core.h"

#include "common_types.h"

//Generic List functions, called by entry list functions
List *create_list(void);
ErrorCode destroy_node(listnode *, ListType);
ErrorCode destroy_list(List *, ListType);
List *insert_list(List *, void *);

//Entry List and index functions
ErrorCode create_entry_list(List **);
Entry *create_entry(const char *, void *);
ErrorCode destroy_entry(Entry *);
unsigned int get_number_entries(const List *);
ErrorCode add_entry(List *, const Entry *); //Prefer to use create_entry/copy_entry as second argument
Entry *get_first(const List *);
Entry *get_next(const listnode *);
ErrorCode destroy_entry_list(List *);
Entry *copy_entry(const Entry *);
void print_entry_list(const List *);
ErrorCode build_entry_index(const List *, MatchType, Index);
ErrorCode lookup_entry_index(const char *, Index, int, List **);
ErrorCode destroy_entry_index(Index);