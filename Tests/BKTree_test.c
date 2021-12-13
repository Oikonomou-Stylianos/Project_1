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
// File : HashTable_test.c
///////////////////////////////////

#include "acutest.h"

#include "BKTree.h"
#include "common_types.h"
#include "constructors.h"

void BKT_Create

TEST_LIST = {

    { "LL_Create", test_LL_Create },
    { "LL_InsertHead", test_LL_InsertHead },
    { "LL_InsertTail", test_LL_InsertTail },
    { "LL_InsertSort", test_LL_InsertSort },
    { "LL_InsertSortUnique", test_LL_InsertSortUnique },
    { "LL_InsertAfter", test_LL_InsertAfter },
    { "LL_InsertAt", test_LL_InsertAt },
    { "LL_Search", test_LL_Search },
    { "LL_SearchRec", test_LL_SearchRec },
    { "LL_Exists", test_LL_Exists },
    { "LL_DeleteHead", test_LL_DeleteHead },
    { "LL_DeleteTail", test_LL_DeleteTail },
    { "LL_DeleteNth", test_LL_DeleteNth },
    { "LL_Join", test_LL_Join },
    { "LL_ToArray", test_LL_ToArray },
    { "LL_GetValue", test_LL_GetValue },
    { "LL_GetHead", test_LL_GetHead },
    { "LL_GetTail", test_LL_GetTail },
    { "LL_GetNth", test_LL_GetNth },
    { "LL_Next", test_LL_Next },
    { "LL_Next", test_LL_Previous },
    { "LL_Print", test_LL_Print },
    { "LL_IsEmpty", test_LL_IsEmpty },
    { "LL_GetSize", test_LL_GetSize },
    { "LL_Clean", test_LL_Clean },
    { "LL_Destroy", test_LL_Destroy },
    { NULL, NULL }
};