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

#include "acutest.h"

#include "distance.h"

void test_min_int(void){

    TEST_CHECK(min_int(0, 0) == 0);
}

TEST_LIST = {
	{ "min_int", test_min_int },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};