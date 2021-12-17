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

#include "distance.h"
#include "core.h"

void test_min_int(void){

    TEST_CHECK(min_int(0, 0) == 0);
    TEST_CHECK(min_int(-1, 1) == -1);
    TEST_CHECK(min_int(1, -1) == -1);
    TEST_CHECK(min_int(-1, -1) == -1);
    TEST_CHECK(min_int(1, 1) == 1);
    TEST_CHECK(min_int(1, 2) == 1);
    TEST_CHECK(min_int(-1, -2) == -2);
}
void test_edit_distance(void){

    char *a, *b;
    a = NULL; b = NULL;
    TEST_CHECK(edit_distance(a, b) == -1);
    b = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    a = NULL; strcpy(b, "abcd");
    TEST_CHECK(edit_distance(a, b) == -1);
    a = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    strcpy(a, "abcd"); free(b); b = NULL; 
    TEST_CHECK(edit_distance(a, b) == -1);
    b = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    strcpy(a, ""); strcpy(b, ""); 
    TEST_CHECK(edit_distance(a, b) == -1);
    strcpy(a, "abcd"); strcpy(b, ""); 
    TEST_CHECK(edit_distance(a, b) == -1);
    strcpy(a, ""); strcpy(b, "abcd"); 
    TEST_CHECK(edit_distance(a, b) == -1);
    strcpy(a, "a"); strcpy(b, "abcd");
    TEST_CHECK(edit_distance(a, b) == -1);
    strcpy(a, "abcd"); strcpy(b, "b");
    TEST_CHECK(edit_distance(a, b) == -1);
    strcpy(a, "abcd"); strcpy(b, "abcd");
    TEST_CHECK(edit_distance(a, b) == 0);
    strcpy(a, "abcd"); strcpy(b, "abcde");
    TEST_CHECK(edit_distance(a, b) == 1);
    strcpy(a, "abcde"); strcpy(b, "abcd");
    TEST_CHECK(edit_distance(a, b) == 1);
    strcpy(a, "aaaa"); strcpy(b, "bbbbbbbb");
    TEST_CHECK(edit_distance(a, b) == 8);
    strcpy(a, "aaaaaaaa"); strcpy(b, "bbbb");
    TEST_CHECK(edit_distance(a, b) == 8);
    free(a); free(b);
}
void test_hamming_distance(void){

    char *a, *b;
    a = NULL; b = NULL;
    TEST_CHECK(hamming_distance(a, b) == -1);
    b = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    a = NULL; strcpy(b, "abcd");
    TEST_CHECK(hamming_distance(a, b) == -1);
    a = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    strcpy(a, "abcd"); free(b); b = NULL; 
    TEST_CHECK(hamming_distance(a, b) == -1);
    b = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    strcpy(a, ""); strcpy(b, ""); 
    TEST_CHECK(hamming_distance(a, b) == -1);
    strcpy(a, "abcd"); strcpy(b, ""); 
    TEST_CHECK(hamming_distance(a, b) == -1);
    strcpy(a, ""); strcpy(b, "abcd"); 
    TEST_CHECK(hamming_distance(a, b) == -1);
    strcpy(a, "a"); strcpy(b, "abcd");
    TEST_CHECK(hamming_distance(a, b) == -1);
    strcpy(a, "abcd"); strcpy(b, "b");
    TEST_CHECK(hamming_distance(a, b) == -1);
    strcpy(a, "abcd"); strcpy(b, "abcd");
    TEST_CHECK(hamming_distance(a, b) == 0);
    strcpy(a, "abcd"); strcpy(b, "abcde");
    TEST_CHECK(hamming_distance(a, b) == -1);
    strcpy(a, "abcde"); strcpy(b, "abcd");
    TEST_CHECK(hamming_distance(a, b) == -1);
    free(a); free(b);
}
void test_exact_match(void){

    char *a, *b;
    a = NULL, b = NULL;
    TEST_CHECK(exact_match(a, b) == -1);
    b = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    a = NULL; strcpy(b, "abcd");
    TEST_CHECK(exact_match(a, b) == -1);
    a = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    strcpy(a, "abcd"); free(b); b = NULL; 
    TEST_CHECK(exact_match(a, b) == -1);
    b = (char *)malloc(sizeof(char )*MAX_WORD_LENGTH);
    strcpy(a, ""); strcpy(b, ""); 
    TEST_CHECK(exact_match(a, b) == -1);
    strcpy(a, "abcd"); strcpy(b, ""); 
    TEST_CHECK(exact_match(a, b) == -1);
    strcpy(a, ""); strcpy(b, "abcd"); 
    TEST_CHECK(exact_match(a, b) == -1);
    strcpy(a, "a"); strcpy(b, "abcd"); 
    TEST_CHECK(exact_match(a, b) == -1);
    strcpy(a, "abcd"); strcpy(b, "b"); 
    TEST_CHECK(exact_match(a, b) == -1);
    strcpy(a, "abcd"); strcpy(b, "abcd"); 
    TEST_CHECK(exact_match(a, b) == 0);
    strcpy(a, "abcde"); strcpy(b, "abcd"); 
    TEST_CHECK(exact_match(a, b) == 1);
    strcpy(a, "abcd"); strcpy(b, "abcde"); 
    TEST_CHECK(exact_match(a, b) == 1);
    free(a); free(b);
}

TEST_LIST = {

	{ "min_int", test_min_int },
	{ "edit_distance", test_edit_distance },
	{ "hamming_distance", test_hamming_distance },
	{ "exact_match", test_exact_match },
	{ NULL, NULL }
};