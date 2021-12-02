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
// File : EntryList.h
///////////////////////////////////

#pragma once

#include "BKTree.h"
#include "core.h"
#include "DataStructs.h"
#include "List.h"

//Entry List and index functions
ErrorCode create_entry_list(List **);
Entry *create_entry(const char *, void *);
unsigned int get_number_entries(const List *);
ErrorCode add_entry(List *, const Entry *); //Prefer to use create_entry/copy_entry as second argument
Entry *get_first(const List *);
Entry *get_next(const listnode *);
ErrorCode destroy_entry_list(List *);
Entry *copy_entry(const Entry *);
Entry *entry_exists(const List *, const char *);
ErrorCode update_payload(Entry *, void *);
void print_entry_list(const List *);
ErrorCode build_entry_index(const List *, MatchType, Index);
ErrorCode lookup_entry_index(const char *, Index, int, List **);
ErrorCode destroy_entry_index(Index);