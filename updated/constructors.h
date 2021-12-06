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
// File : WordList.h
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

void destroyEntryPtr(Pointer );
int compareEntryPtr(Pointer , Pointer );

Query createQuery(unsigned int , char *, MatchType , unsigned int );
void destroyQuery(Pointer );
int compareQuery(Pointer , Pointer );
int compareQueryPtr(Pointer , Pointer );

int compareBKTNPtrString(Pointer , Pointer );
int compareBKTNPtrEntry(Pointer , Pointer );