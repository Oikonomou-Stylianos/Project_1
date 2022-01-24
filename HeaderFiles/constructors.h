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
// File : constructors.h
///////////////////////////////////

#pragma once

#include "common_types.h"
#include "core.h"

char *createString(char *);
void destroyString(Pointer );
int compareString(Pointer , Pointer );

int *createInt(int );
void destroyInt(Pointer );
int compareInt(Pointer , Pointer);

unsigned int *createUInt(unsigned int );
void destroyUInt(Pointer );
int compareUInt(Pointer , Pointer );

Entry createEntry(char *);
void destroyEntry(Pointer );
int compareEntry(Pointer , Pointer );

Query createQuery(unsigned int, MatchType , unsigned int );
void destroyQuery(Pointer );
int compareQuery(Pointer , Pointer );
char toggle_query_active(Query );
void query_active_false(Query );
void query_active_true(Query );

int compareBKTNString(Pointer , Pointer );
int compareBKTNEntry(Pointer , Pointer );

QueryResult createQueryResult(unsigned int , unsigned int , unsigned int *);
void destroyQueryResult(Pointer );
int compareQueryResult(Pointer , Pointer );

Job createJob(void *(*)(void *), void **);
void destroyJob(Pointer );