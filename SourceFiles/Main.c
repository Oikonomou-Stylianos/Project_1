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

#include <stdio.h>

#include "BKTree.h"
#include "core.h"

#include "HashTable.h"

int main(int argc, char *argv[]){

	// BKTree myBKT = BKT_Create(MT_EDIT_DIST);

	// BKT_Insert(myBKT, "fall");
	// BKT_Insert(myBKT, "hell");
	// BKT_Insert(myBKT, "felt");
	// BKT_Insert(myBKT, "help");
	// BKT_Insert(myBKT, "melt");
	// BKT_Insert(myBKT, "small");
	// BKT_Insert(myBKT, "fell");

	// WList myWL = BKT_Search(myBKT, "henn", 2);
	// WL_Print(myWL);
	// WL_Destroy(myWL);

	// BKT_Destroy(myBKT);

	WList wl = WL_Create();

	WL_InsertSortUnique(wl, "fall");
	WL_InsertSortUnique(wl, "aall");
	WL_InsertSortUnique(wl, "aall");
	WL_InsertSortUnique(wl, "hell");
	WL_InsertSortUnique(wl, "felt");
	WL_InsertSortUnique(wl, "felt");

	WL_Print(wl);
	WL_Destroy(wl);

	HashTable ht = HT_Create();
	if(HT_InitializeFromFile(ht, "./AppData/test_file.txt") == NULL)
		printf("NULL");

	return 0;
}
