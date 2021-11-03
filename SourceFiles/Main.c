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

#include "../HeaderFiles/BKTree.h"

int main(int argc, char *argv[]){

	BKTree myBKT = BKT_Create();

	BKT_Insert(myBKT, "fall");
	BKT_Insert(myBKT, "hell");
	BKT_Insert(myBKT, "help");
	BKT_Insert(myBKT, "felt");
	BKT_Insert(myBKT, "small");
	BKT_Insert(myBKT, "fell");
	BKT_Insert(myBKT, "melt");

	WList myWL = BKT_Search(myBKT, "henn", 2);
	WL_Print(myWL);
	WL_Destroy(myWL);

	BKT_Destroy(myBKT);

	return 0;
}