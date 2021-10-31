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
#include <stdlib.h>
#include <string.h>

#include "../HeaderFiles/WordList.h"
#include "../HeaderFiles/common_types.h"

// Create a Word List
WList WL_Create(){

	WList wl = (WList )malloc(sizeof(wlist ));
	wl->head = NULL;

	return wl != NULL ? wl : NULL;
}
// Insert a node at the tail of a Word List
WLNode WL_Insert(WList wl, char *word){

	if(wl == NULL || word == NULL)
		return NULL;

	WLNode wln = (WLNode )malloc(sizeof(word_list_node ));
	strcpy(wln->word, word);
	wln->next = NULL;

	if(wl->head == NULL){
		wl->head = wln;
		wl->tail = wln;
	}
	else{

		wl->tail->next = wln;
		wl->tail = wln;
	}
	return wln;
}
// Remove the first node of a Word List
int WL_RemoveFirst(WList wl){

	if(wl == NULL)
		return 1;

	if(wl->head == NULL)
		return 1;
	else{

		if(wl->tail == wl->head){

			WLNode temp = wl->head;
			wl->head = NULL;
			wl->tail = NULL;
			free(temp);
		}
		else{

			WLNode temp = wl->head;
			wl->head = wl->head->next;
			free(temp);
		}
	}
	return 0;
}
WLNode WL_GetFirst(WList wl){

	return wl->head;
}
// Print a Word List 
int WL_Print(WList wl){

	if(wl == NULL)
		return 1;

	WLNode temp = wl->head;
	printf("[");
	while(temp != NULL){

		printf("'%s'", temp->word);
		temp = temp->next;
		if(temp != NULL)
			printf(",");
	}
	printf("]\n");
	return 0;
}
// Destroy a Word List
int WL_Destroy(WList wl){

	if(wl == NULL)
		return 1;

	while(wl->head != NULL)
		WL_RemoveFirst(wl);
	free(wl);
	return 0;
}