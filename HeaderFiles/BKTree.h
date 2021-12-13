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
// File : BKTree.h
///////////////////////////////////

#pragma once

#include "LinkedList.h"

#include "common_types.h"
#include "core.h"

BKTree BKT_Create(MatchType , DataType , DestroyFunction );
BKTreeNode BKT_CreateNode(Pointer );
BKTreeNode BKT_Insert(const BKTree , Pointer );
BKTreeNode BKT_InsertNode(const BKTree , const BKTreeNode , Pointer );
LList BKT_Search(const BKTree , const char *, const unsigned int );
int BKT_Destroy(BKTree );
int BKT_DestroyNode(BKTree , BKTreeNode );