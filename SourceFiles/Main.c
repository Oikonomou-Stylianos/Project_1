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

	// ~~! BKTree example !--

    BKTree myBKT = BKT_Create(MT_EDIT_DIST);
    List *el = NULL;
    create_entry_list(&el);
    add_entry(el, create_entry("hell", NULL));
    add_entry(el, create_entry("help", NULL));
    add_entry(el, create_entry("fall", NULL));
    add_entry(el, create_entry("felt", NULL));
    add_entry(el, create_entry("fell", NULL));
    add_entry(el, create_entry("small", NULL));
    add_entry(el, create_entry("melt", NULL));

    BKT_InsertFromEntryList(myBKT, el);

	Entry *entry;
	entry = create_entry("henn", NULL);
	List *myWL = BKT_Search(myBKT, entry, 2);
	WL_Print(myWL);
	WL_Destroy(myWL);
	BKT_Destroy(myBKT);

	// ~~! Word List InsertSortUnique example !~~
	// WList wl = WL_Create();
	// WL_InsertSortUnique(wl, "fall");
	// WL_InsertSortUnique(wl, "aall");
	// WL_InsertSortUnique(wl, "aall");
	// WL_InsertSortUnique(wl, "hell");
	// WL_InsertSortUnique(wl, "felt");
	// WL_InsertSortUnique(wl, "felt");
	// WL_Print(wl);
	// WL_Destroy(wl);

	// ~~! Deduplicate example !~~
	// WList wl = deduplicate("./AppData/small_test.txt");
	// WL_Print(wl);
	// printf("Deduplicated Words Count = %d\n",WL_GetSize(wl));
	// WL_Destroy(wl);

	return 0;
}
