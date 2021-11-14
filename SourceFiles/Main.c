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
// File : Main.c
///////////////////////////////////

#include <stdio.h>

#include "EntryList.h"
#include "BKTree.h"
#include "core.h"

#include "HashTable.h"

int main(int argc, char *argv[]){

	// ~~! Project example !~~
    List *el = NULL;
    if(create_entry_list(&el) != EC_SUCCESS) return 1;
    if(add_entry(el, create_entry("hell", NULL)) != EC_SUCCESS) return 1;
    if(add_entry(el, create_entry("help", NULL)) != EC_SUCCESS) return 1;
    if(add_entry(el, create_entry("fall", NULL)) != EC_SUCCESS) return 1;
    if(add_entry(el, create_entry("felt", NULL)) != EC_SUCCESS) return 1;
    if(add_entry(el, create_entry("fell", NULL)) != EC_SUCCESS) return 1;
    if(add_entry(el, create_entry("small", NULL)) != EC_SUCCESS) return 1;
    if(add_entry(el, create_entry("melt", NULL)) != EC_SUCCESS) return 1;

    BKTree myBKT;
	if(build_entry_index(el, MT_EDIT_DIST, &myBKT) != EC_SUCCESS) return 1; 

	List *myL;
	if(lookup_entry_index("henn", &myBKT, 2, &myL) != EC_SUCCESS) return 1;
	print_entry_list(myL);
	if(destroy_entry_index(&myBKT) != EC_SUCCESS) return 1;
	if(destroy_entry_list(myL) != EC_SUCCESS) return 1;
	if(destroy_entry_list(el) != EC_SUCCESS) return 1;

	// ~~! Deduplicate example !~~
	// WList wl;
	// if((wl = deduplicate("./AppData/small_test.txt")) == NULL) return 1;
	// if(WL_Print(wl) == 1) return 1;
	// printf("Deduplicated Words Count = %d\n",WL_GetSize(wl));
	// if(WL_Destroy(wl) == 1) return 1;

	return 0;
}
