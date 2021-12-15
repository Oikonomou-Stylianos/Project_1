///////////////////////////////////
// University: UoA DIT
// Course : [K23a] Software Development for Computer Systems
// Semester : Fall 2021-2022
// Professor : Yannis Ioannidis 
// Assistant : Sarantis Paskalis
// --------------------------------
// Students: Stylianos Oikonomou , Anastasios Triantafyllou
// ID : 1115201500243 , 1115201600173 
// --------------------------------
// File : distance.h
///////////////////////////////////

#pragma once

#include "core.h"

int min_int(const int , const int );

int edit_distance(const char *, const char *);
int hamming_distance(const char *, const char *);
int exact_match(const char *, const char *);
int distance(const char *, const char *, MatchType );