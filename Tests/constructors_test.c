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
// File : distance_test.c
///////////////////////////////////

#include "acutest.h"

#include "constructors.h"
#include "core.h"

void test_createString(void){

    char *str;
    TEST_CHECK((str = createString(NULL)) == NULL);
    TEST_CHECK((str = createString("test")) != NULL);
    TEST_CHECK(compareString(str, "test") == 0);
    destroyString(str);
}
void test_destroyString(void){

    // Nothing to check
}
void test_compareString(void){

    char *str1 = createString("a"), *str2 = createString("b");
    TEST_CHECK(compareString(NULL, NULL) == -2); 
    TEST_CHECK(compareString(NULL, str2) == -2); 
    TEST_CHECK(compareString(str1, NULL) == -2); 
    TEST_CHECK(compareString(str1, str1) == 0); 
    TEST_CHECK(compareString(str1, str2) == -1); 
    TEST_CHECK(compareString(str2, str1) == 1); 
    destroyString(str1);
    destroyString(str2);
}
void test_createInt(void){

    int *a;
    a = createInt(1);
    TEST_CHECK(*a == 1);
    destroyInt(a);
}
void test_destroyInt(void){

    // Nothing to check
}
void test_compareInt(void){

    int *num1 = createInt(1), *num2 = createInt(2);
    TEST_CHECK(compareInt(NULL, NULL) == -2); 
    TEST_CHECK(compareInt(NULL, num2) == -2); 
    TEST_CHECK(compareInt(num1, NULL) == -2); 
    TEST_CHECK(compareInt(num1, num1) == 0); 
    TEST_CHECK(compareInt(num1, num2) == -1); 
    TEST_CHECK(compareInt(num2, num1) == 1); 
    destroyInt(num1);
    destroyInt(num2);
}
void test_createUInt(void){

    unsigned int *a;
    a = createUInt(1);
    TEST_CHECK(*a == 1);
    destroyUInt(a);
}
void test_destroyUInt(void){

    // Nothing to check
}
void test_compareUInt(void){

    unsigned int *num1 = createUInt(1), *num2 = createUInt(2);
    TEST_CHECK(compareUInt(NULL, NULL) == -2); 
    TEST_CHECK(compareUInt(NULL, num2) == -2); 
    TEST_CHECK(compareUInt(num1, NULL) == -2); 
    TEST_CHECK(compareUInt(num1, num1) == 0); 
    TEST_CHECK(compareUInt(num1, num2) == -1); 
    TEST_CHECK(compareUInt(num2, num1) == 1); 
    destroyUInt(num1);
    destroyUInt(num2);
}
void test_createEntry(void){

    Entry e;
    TEST_CHECK((e = createEntry(NULL)) == NULL);
    TEST_CHECK((e = createEntry("test")) != NULL);
    TEST_CHECK(compareString(e->word, "test") == 0);
    destroyEntry(e);
}
void test_destroyEntry(void){

    // Nothing to check
}
void test_compareEntry(void){

    Entry e1 = createEntry("a"), e2 = createEntry("b");
    TEST_CHECK(compareEntry(NULL, NULL) == -2);
    TEST_CHECK(compareEntry(e1, NULL) == -2);
    TEST_CHECK(compareEntry(NULL, e2) == -2);
    TEST_CHECK(compareEntry(e1, e1) == 0);
    TEST_CHECK(compareEntry(e1, e2) == -1);
    TEST_CHECK(compareEntry(e2, e1) == 1);
    destroyEntry(e1);
    destroyEntry(e2);
}
void test_createQuery(void){

    Query q;
    q = createQuery(1, 0, 1);
    TEST_CHECK(q->query_id == 1);
    TEST_CHECK(q->match_type == 0);
    TEST_CHECK(q->match_dist == 1);
    TEST_CHECK(q->active == 1);
    destroyQuery(q);
}
void test_destroyQuery(void){

    // Nothing to check
}
void test_compareQuery(void){

    Query q1 = createQuery(1, 0, 1), q2 = createQuery(2, 0, 1);
    TEST_CHECK(compareQuery(NULL, NULL) == -2);
    TEST_CHECK(compareQuery(q1, NULL) == -2);
    TEST_CHECK(compareQuery(NULL, q2) == -2);
    TEST_CHECK(compareQuery(q1, q1) == 0);
    TEST_CHECK(compareQuery(q1, q2) == -1);
    TEST_CHECK(compareQuery(q2, q1) == 1);
    destroyQuery(q1);
    destroyQuery(q2);
}
void test_toggle_query_active(void){

    Query q = createQuery(1, 0, 1);
    TEST_CHECK(toggle_query_active(NULL) == -1);
    TEST_CHECK(toggle_query_active(q) == 0);
    TEST_CHECK(toggle_query_active(q) == 1);
    destroyQuery(q);
}
void test_query_active_false(void){

    Query q = createQuery(1, 0, 1);
    query_active_false(q);
    TEST_CHECK(q->active == 0);
    destroyQuery(q);
}
void test_query_active_true(void){

    Query q = createQuery(1, 0, 1);
    query_active_false(q);
    TEST_CHECK(q->active == 0);
    query_active_true(q);
    TEST_CHECK(q->active == 1);
    destroyQuery(q);
}
void test_compareBKTNPtrString(void){

    char *str1 = createString("a"), *str2 = createString("b"); 
    BKTreeNode bktn1 = (BKTreeNode )malloc(sizeof(bk_tree_node)), bktn2 = (BKTreeNode )malloc(sizeof(bk_tree_node));
    bktn1->data = (Pointer )str1;
    bktn2->data = (Pointer )str2;
    TEST_CHECK(compareBKTNPtrString(NULL, NULL) == -2);
    TEST_CHECK(compareBKTNPtrString(NULL, &bktn2) == -2);
    TEST_CHECK(compareBKTNPtrString(&bktn1, NULL) == -2);
    TEST_CHECK(compareBKTNPtrString(&bktn1, &bktn1) == 0);
    TEST_CHECK(compareBKTNPtrString(&bktn1, &bktn2) == -1);
    TEST_CHECK(compareBKTNPtrString(&bktn2, &bktn1) == 1);
    destroyString(str1); destroyString(str2);
    free(bktn1); free(bktn2);
}
void test_compareBKTNPtrEntry(void){

    Entry e1 = createEntry("a"), e2 = createEntry("b");
    BKTreeNode bktn1 = (BKTreeNode )malloc(sizeof(bk_tree_node)), bktn2 = (BKTreeNode )malloc(sizeof(bk_tree_node));
    bktn1->data = (Pointer )&e1;
    bktn2->data = (Pointer )&e2;
    TEST_CHECK(compareBKTNPtrEntry(NULL, NULL) == -2);
    TEST_CHECK(compareBKTNPtrEntry(NULL, &bktn2) == -2);
    TEST_CHECK(compareBKTNPtrEntry(&bktn1, NULL) == -2);
    TEST_CHECK(compareBKTNPtrEntry(&bktn1, &bktn1) == 0);
    TEST_CHECK(compareBKTNPtrEntry(&bktn1, &bktn2) == -1);
    TEST_CHECK(compareBKTNPtrEntry(&bktn2, &bktn1) == 1);
    destroyEntry(e1); destroyEntry(e2);
    free(bktn1); free(bktn2);
}
void test_createQueryResult(void){

    QueryResult qr;
    unsigned int *ids = (unsigned int *)malloc(sizeof(int ));
    ids[0] = 1;
    qr = createQueryResult(1, 1, ids);
    TEST_CHECK(qr->doc_id == 1);
    TEST_CHECK(qr->num_res == 1);
    TEST_CHECK(qr->query_ids[0] == 1);
    free(ids);
    destroyQueryResult(qr);
}
void test_destroyQueryResult(void){

    // Nothing to check
}
void test_compareQueryResult(void){

    QueryResult qr1 = createQueryResult(1, 1, NULL), qr2 = createQueryResult(2, 1, NULL);
    TEST_CHECK(compareQueryResult(NULL, NULL) == -2);
    TEST_CHECK(compareQueryResult(NULL, qr2) == -2);
    TEST_CHECK(compareQueryResult(qr1, NULL) == -2);
    TEST_CHECK(compareQueryResult(qr1, qr1) == 0);
    TEST_CHECK(compareQueryResult(qr1, qr2) == -1);
    TEST_CHECK(compareQueryResult(qr2, qr1) == 1);
    destroyQueryResult(qr1);
    destroyQueryResult(qr2);
}


TEST_LIST = {

	{ "createString", test_createString },
	{ "destroyString", test_destroyString },
	{ "compareString", test_compareString },
	{ "createInt", test_createInt },
	{ "destroyInt", test_destroyInt },
	{ "compareInt", test_compareInt },
	{ "createUInt", test_createUInt },
	{ "destroyUInt", test_destroyUInt },
	{ "compareUInt", test_compareUInt },
	{ "createEntry", test_createEntry },
	{ "destroyEntry", test_destroyEntry },
	{ "compareEntry", test_compareEntry },
	{ "createQuery", test_createQuery },
	{ "destroyQuery", test_destroyQuery },
	{ "compareQuery", test_compareQuery },
	{ "toggle_query_active", test_toggle_query_active },
	{ "query_active_false", test_query_active_false },
	{ "query_active_true", test_query_active_true },
	{ "compareBKTNPtrString", test_compareBKTNPtrString },
	{ "compareBKTNPtrEntry", test_compareBKTNPtrEntry },
	{ "createQueryResult", test_createQueryResult },
	{ "destroyQueryResult", test_destroyQueryResult },
	{ "compareQueryResult", test_compareQueryResult },
	{ NULL, NULL }
};