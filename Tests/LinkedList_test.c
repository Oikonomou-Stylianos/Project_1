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

#include "LinkedList.h"
#include "common_types.h"
#include "constructors.h"

void test_LL_Create(void){

    LList ll;
    TEST_CHECK((ll = LL_Create(IntType, &destroyInt, &compareInt)) != NULL);
    LL_Destroy(ll);
}
void test_LL_InsertHead(void){

    int *num1 = createInt(1), *num2 = createInt(2);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK((lln = LL_InsertHead(NULL, NULL)) == NULL);
    TEST_CHECK((lln = LL_InsertHead(ll, NULL)) == NULL);
    TEST_CHECK((lln = LL_InsertHead(NULL, (Pointer )num1)) == NULL);
    TEST_CHECK((lln = LL_InsertHead(ll, (Pointer )num1)) != NULL);
    TEST_CHECK(ll->head != NULL);
    TEST_CHECK(*(int *)(ll->head->data) == *num1);
    TEST_CHECK(ll->size == 1);
    TEST_CHECK((lln = LL_InsertHead(ll, (Pointer )num2)) != NULL);
    TEST_CHECK(*(int *)(ll->head->data) == *num2);
    TEST_CHECK(ll->size == 2);
    LL_Destroy(ll);
}
void test_LL_InsertTail(void){

    int *num1 = createInt(1), *num2 = createInt(2);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK((lln = LL_InsertTail(NULL, NULL)) == NULL);
    TEST_CHECK((lln = LL_InsertTail(ll, NULL)) == NULL);
    TEST_CHECK((lln = LL_InsertTail(NULL, (Pointer )num1)) == NULL);
    TEST_CHECK((lln = LL_InsertTail(ll, (Pointer )num1)) != NULL);
    TEST_CHECK(ll->tail != NULL);
    TEST_CHECK(*(int *)(ll->tail->data) == *num1);
    TEST_CHECK(ll->size == 1);
    TEST_CHECK((lln = LL_InsertTail(ll, (Pointer )num2)) != NULL);
    TEST_CHECK(ll->tail != NULL);
    TEST_CHECK(*(int *)(ll->tail->data) == *num2);
    TEST_CHECK(ll->size == 2);
    LL_Destroy(ll);
}
void test_LL_InsertSort(void){

    int *num1 = createInt(1), *num11 = createInt(1), *num2 = createInt(2), *num3 = createInt(3), *num4 = createInt(4);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK((lln = LL_InsertSort(NULL, NULL)) == NULL);
    TEST_CHECK((lln = LL_InsertSort(ll, NULL)) == NULL);
    TEST_CHECK((lln = LL_InsertSort(NULL, (Pointer )num2)) == NULL);
    TEST_CHECK((lln = LL_InsertSort(ll, (Pointer )num2)) != NULL);
    TEST_CHECK(*(int *)(ll->head->data) == *num2);
    TEST_CHECK(ll->size == 1);
    TEST_CHECK((lln = LL_InsertSort(ll, (Pointer )num1)) != NULL);
    TEST_CHECK(*(int *)(ll->head->data) == *num1);
    TEST_CHECK(ll->size == 2);
    TEST_CHECK((lln = LL_InsertSort(ll, (Pointer )num11)) != NULL);
    TEST_CHECK(*(int *)(ll->head->next->data) == *num11);
    TEST_CHECK(ll->size == 3);
    TEST_CHECK((lln = LL_InsertSort(ll, (Pointer )num3)) != NULL);
    TEST_CHECK(*(int *)(ll->head->next->next->next->data) == *num3);
    TEST_CHECK(ll->size == 4);
    TEST_CHECK((lln = LL_InsertSort(ll, (Pointer )num4)) != NULL);
    TEST_CHECK(*(int *)(ll->tail->data) == *num4);
    TEST_CHECK(ll->size == 5);
    LL_Destroy(ll);
}
void test_LL_InsertSortUnique(void){

    int *num1 = createInt(1), *num2 = createInt(2), *num3 = createInt(3), *num4 = createInt(4);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK((lln = LL_InsertSortUnique(NULL, NULL)) == NULL);
    TEST_CHECK((lln = LL_InsertSortUnique(ll, NULL)) == NULL);
    TEST_CHECK((lln = LL_InsertSortUnique(NULL, (Pointer )num2)) == NULL);
    TEST_CHECK((lln = LL_InsertSortUnique(ll, (Pointer )num2)) != NULL);
    TEST_CHECK(*(int *)(ll->head->data) == *num2);
    TEST_CHECK(ll->size == 1);
    TEST_CHECK((lln = LL_InsertSortUnique(ll, (Pointer )num1)) != NULL);
    TEST_CHECK(*(int *)(ll->head->data) == *num1);
    TEST_CHECK(ll->size == 2);
    TEST_CHECK((lln = LL_InsertSortUnique(ll, (Pointer )num4)) != NULL);
    TEST_CHECK(*(int *)(ll->tail->data) == *num4);
    TEST_CHECK(ll->size == 3);
    TEST_CHECK((lln = LL_InsertSortUnique(ll, (Pointer )num3)) != NULL);
    TEST_CHECK(*(int *)(ll->head->next->next->data) == *num3);
    TEST_CHECK(ll->size == 4);
    LL_Destroy(ll);
}
void test_LL_InsertAfter(void){
    
    int *num1 = createInt(1), *num2 = createInt(2);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    lln = LL_InsertHead(ll, num1);
    TEST_CHECK(LL_InsertAfter(NULL, NULL, NULL) == NULL);
    TEST_CHECK(LL_InsertAfter(ll, NULL, NULL) == NULL);
    TEST_CHECK(LL_InsertAfter(NULL, lln, NULL) == NULL);
    TEST_CHECK(LL_InsertAfter(NULL, NULL, num2) == NULL);
    TEST_CHECK(LL_InsertAfter(ll, lln, NULL) == NULL);
    TEST_CHECK(LL_InsertAfter(ll, NULL, num2) == NULL);
    TEST_CHECK(LL_InsertAfter(NULL, lln, num2) == NULL);
    TEST_CHECK(LL_InsertAfter(ll, lln, num2) != NULL);
    TEST_CHECK(*(int *)(ll->head->next->data) == *num2);
    LL_Destroy(ll);
}
void test_LL_InsertAt(void){

    int *num1 = createInt(1), *num2 = createInt(2), *num3 = createInt(3);
    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK(LL_InsertAt(NULL, NULL, 0) == NULL);
    TEST_CHECK(LL_InsertAt(ll, NULL, 0) == NULL);
    TEST_CHECK(LL_InsertAt(NULL, num1, 0) == NULL);
    TEST_CHECK(LL_InsertAt(ll, num1, 0) != NULL);
    TEST_CHECK(*(int *)(ll->head->data) == *num1);
    TEST_CHECK(LL_InsertAt(ll, num3, 2) == NULL);   // Index exceeded size of list
    TEST_CHECK(LL_InsertAt(ll, num3, 1) != NULL);
    TEST_CHECK(*(int *)(ll->tail->data) == *num3);
    TEST_CHECK(LL_InsertAt(ll, num2, 1) != NULL);
    TEST_CHECK(*(int *)((ll->head->next)->data) == *num2);
    LL_Destroy(ll);
}
void test_LL_Search(void){

    int *num1 = createInt(1), *num2 = createInt(2);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    LL_InsertHead(ll, num1);
    TEST_CHECK(LL_Search(NULL, NULL) == NULL);
    TEST_CHECK(LL_Search(ll, NULL) == NULL);
    TEST_CHECK(LL_Search(NULL, num1) == NULL);
    TEST_CHECK((lln = LL_Search(ll, num1)) != NULL);
    TEST_CHECK(*(int *)(lln->data) == *num1);
    TEST_CHECK((lln = LL_Search(ll, num2)) == NULL);    // Num does not exist in the list
    destroyInt(num2);
    LL_Destroy(ll);
}
void test_LL_SearchRec(void){

    int *num1 = createInt(1), *num2 = createInt(2);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    LL_InsertHead(ll, num1);
    TEST_CHECK(LL_SearchRec(NULL, NULL, NULL) == NULL);
    TEST_CHECK(LL_SearchRec(ll, NULL, NULL) == NULL);
    TEST_CHECK(LL_SearchRec(NULL, ll->head, NULL) == NULL);
    TEST_CHECK(LL_SearchRec(NULL, NULL, num1) == NULL);
    TEST_CHECK(LL_SearchRec(ll, ll->head, NULL) == NULL);
    TEST_CHECK(LL_SearchRec(ll, NULL, num1) == NULL);
    TEST_CHECK(LL_SearchRec(NULL, ll->head, num1) == NULL);
    TEST_CHECK((lln = LL_SearchRec(ll, ll->head, num1)) != NULL);
    TEST_CHECK(*(int *)(lln->data) == *num1);
    TEST_CHECK((lln = LL_SearchRec(ll, ll->head, num2)) == NULL);    // Num does not exist in the list
    destroyInt(num2);
    LL_Destroy(ll);
}
void test_LL_Exists(void){

    int *num1 = createInt(1), *num2 = createInt(2);
    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    LL_InsertHead(ll, num1);
    TEST_CHECK(LL_Exists(NULL, NULL) == -1);
    TEST_CHECK(LL_Exists(ll, NULL) == -1);
    TEST_CHECK(LL_Exists(NULL, num1) == -1);
    TEST_CHECK(LL_Exists(ll, num1) == 1);
    TEST_CHECK(LL_Exists(ll, num2) == 0);    // Num does not exist in the list
    destroyInt(num2);
    LL_Destroy(ll);
}
void test_LL_DeleteHead(void){

    int *num1 = createInt(1);
    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK(LL_DeleteHead(NULL) == 1);
    TEST_CHECK(LL_DeleteHead(ll) == 1);     // Empty list
    LL_InsertHead(ll, num1);
    TEST_CHECK(LL_DeleteHead(ll) == 0);
    LL_Destroy(ll);
}
void test_LL_DeleteTail(void){

    int *num1 = createInt(1);
    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK(LL_DeleteTail(NULL) == 1);
    TEST_CHECK(LL_DeleteTail(ll) == 1);     // Empty list
    LL_InsertHead(ll, num1);
    TEST_CHECK(LL_DeleteTail(ll) == 0);
    LL_Destroy(ll);
}
void test_LL_DeleteNth(void){

    int *num1 = createInt(1);
    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    LL_InsertHead(ll, num1);
    TEST_CHECK(LL_DeleteNth(NULL, 0) == -1);
    TEST_CHECK(LL_DeleteNth(ll, 1) == 1);    // Empty list
    TEST_CHECK(LL_DeleteNth(ll, 0) == 0);
    TEST_CHECK(LL_GetSize(ll) == 0);
    LL_Destroy(ll);
}
void test_LL_Join(void){

    int *num1 = createInt(1), *num2 = createInt(2);
    LList ll1, ll2, ll3;
    ll1 = LL_Create(IntType, &destroyInt, &compareInt);
    ll2 = LL_Create(IntType, NULL, &compareInt);
    ll3 = LL_Create(UIntType, &destroyUInt, &compareUInt);
    LL_InsertHead(ll1, num1);
    TEST_CHECK(LL_Join(NULL, NULL) == NULL);
    TEST_CHECK(LL_Join(ll1, NULL) == NULL);
    TEST_CHECK(LL_Join(NULL, ll2) == NULL);
    TEST_CHECK(LL_Join(ll1, ll3) == NULL);  // Different dataType
    TEST_CHECK(LL_Join(ll1, ll2) != NULL);
    TEST_CHECK(LL_GetSize(ll1) == 1);   // Empty ll2
    ll2 = LL_Create(IntType, NULL, &compareInt);
    LL_InsertHead(ll2, num1);
    TEST_CHECK(LL_Join(ll1, ll2) != NULL);
    TEST_CHECK(LL_GetSize(ll1) == 1);   // the two lists have the same number so the size does not change
    ll2 = LL_Create(IntType, NULL, &compareInt);
    LL_InsertHead(ll2, num2);
    TEST_CHECK(LL_Join(ll1, ll2) != NULL);
    TEST_CHECK(LL_GetSize(ll1) == 2);
    LL_Destroy(ll1);
    LL_Destroy(ll3);
}
void test_LL_ToArray(void){

    int *num1 = createInt(1), *num2 = createInt(2), *array;
    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK(LL_ToArray(NULL) == NULL);
    TEST_CHECK(LL_ToArray(ll) == NULL);     // Empty list
    LL_InsertTail(ll, num1);
    LL_InsertTail(ll, num2);
    TEST_CHECK((array = LL_ToArray(ll)) != NULL);
    TEST_CHECK(array[0] == *num1);
    TEST_CHECK(array[1] == *num2);
    free(array);
    LL_Destroy(ll);
}
void test_LL_GetValue(void){

    int *num1 = createInt(1);
    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK(LL_GetValue(NULL) == NULL);
    LL_InsertTail(ll, num1);
    TEST_CHECK(*(int *)LL_GetValue(ll->head) == *num1);
    LL_Destroy(ll);
}
void test_LL_GetHead(void){

    int *num1 = createInt(1);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK(LL_GetHead(NULL) == NULL);
    TEST_CHECK((lln = LL_GetHead(ll)) == NULL);
    LL_InsertTail(ll, num1);
    TEST_CHECK((lln = LL_GetHead(ll)) != NULL);
    TEST_CHECK(*(int *)(lln->data) == *num1);
    LL_Destroy(ll);
}
void test_LL_GetTail(void){

    int *num1 = createInt(1);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK(LL_GetTail(NULL) == NULL);
    TEST_CHECK((lln = LL_GetTail(ll)) == NULL);
    LL_InsertTail(ll, num1);
    TEST_CHECK((lln = LL_GetTail(ll)) != NULL);
    TEST_CHECK(*(int *)(lln->data) == *num1);
    LL_Destroy(ll);
}
void test_LL_GetNth(void){

    int *num1 = createInt(1), *num2 = createInt(2);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK(LL_GetNth(NULL, 0) == NULL); 
    TEST_CHECK(LL_GetNth(ll, 0) == NULL);
    LL_InsertTail(ll, num1);
    TEST_CHECK((lln = LL_GetNth(ll, 0)) != NULL); 
    TEST_CHECK(*(int *)(lln->data) == *num1); 
    LL_InsertTail(ll, num2);
    TEST_CHECK((lln = LL_GetNth(ll, 1)) != NULL); 
    TEST_CHECK(*(int *)(lln->data) == *num2); 
    LL_Destroy(ll);
}
void test_LL_Next(void){

    int *num1 = createInt(1), *num2 = createInt(2);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    LL_InsertTail(ll, num1);
    TEST_CHECK(LL_Next(NULL, NULL) == NULL);
    TEST_CHECK(LL_Next(ll, NULL) == NULL);
    TEST_CHECK(LL_Next(NULL, ll->head) == NULL);
    TEST_CHECK(LL_Next(ll, ll->head) == NULL);
    LL_InsertTail(ll, num2);
    TEST_CHECK((lln = LL_Next(ll, ll->head)) != NULL);
    TEST_CHECK(*(int *)(lln->data) == *num2);
    LL_Destroy(ll);
}
void test_LL_Previous(void){

    int *num1 = createInt(1), *num2 = createInt(2);
    LList ll;
    LLNode lln;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    LL_InsertTail(ll, num1);
    LL_InsertTail(ll, num2);
    TEST_CHECK(LL_Previous(NULL, NULL) == NULL);
    TEST_CHECK(LL_Previous(ll, NULL) == NULL);
    TEST_CHECK(LL_Previous(NULL, ll->tail) == NULL);
    TEST_CHECK(LL_Previous(ll, ll->head) == NULL);
    TEST_CHECK((lln = LL_Previous(ll, ll->tail)) != NULL);
    TEST_CHECK(*(int *)(lln->data) == *num1);
    LL_Destroy(ll);
}
void test_LL_Print(void){

    int *num1 = createInt(1), *num2 = createInt(2), *num3 = createInt(3);
    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    LL_InsertTail(ll, num1);
    LL_InsertTail(ll, num2);
    LL_InsertTail(ll, num3);
    TEST_CHECK(LL_Print(NULL) == 1);
    TEST_CHECK(LL_Print(ll) == 0);
    LL_Destroy(ll);
}
void test_LL_IsEmpty(void){

    int *num1 = createInt(1);
    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    LL_InsertTail(ll, num1);
    TEST_CHECK(LL_IsEmpty(NULL) == -1);
    TEST_CHECK(LL_IsEmpty(ll) == 0);
    LL_DeleteHead(ll);
    TEST_CHECK(LL_IsEmpty(ll) == 1);
    LL_Destroy(ll);
}
void test_LL_GetSize(void){

    int *num1 = createInt(1);
    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK(LL_GetSize(NULL) == -1);
    TEST_CHECK(LL_GetSize(ll) == 0);
    LL_InsertTail(ll, num1);
    TEST_CHECK(LL_GetSize(ll) == 1);
    LL_Destroy(ll);
}
void test_LL_Clean(void){

    int *num1 = createInt(1);
    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    LL_InsertTail(ll, num1);
    TEST_CHECK(LL_Clean(NULL) == NULL);
    TEST_CHECK(LL_Clean(ll) != NULL);
    TEST_CHECK(LL_GetHead(ll) == NULL);
    TEST_CHECK(LL_GetTail(ll) == NULL);
    TEST_CHECK(LL_GetSize(ll) == 0);
    LL_Destroy(ll);
}
void test_LL_Destroy(void){

    LList ll;
    ll = LL_Create(IntType, &destroyInt, &compareInt);
    TEST_CHECK(LL_Destroy(NULL) == 1);
    TEST_CHECK(LL_Destroy(ll) == 0);
}

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