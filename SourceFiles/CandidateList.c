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

#include "CandidateList.h"
#include "BKTree.h"

// Create a Candidate List
CList CL_Create(){

	CList cl = (CList )malloc(sizeof(clist ));
	cl->head = NULL;
	cl->tail = NULL;

	return cl != NULL ? cl : NULL;
}
// Insert a node at the tail of a Candidate List
CLNode CL_Insert(const CList cl, BKTreeNode *bktn){

	if(cl == NULL || bktn == NULL)
		return NULL;

	CLNode cln = (CLNode )malloc(sizeof(candidate_list_node ));
	cln->candidate = bktn;
	cln->next = NULL;

	if(cl->head == NULL){
		cl->head = cln;
		cl->tail = cln;
	}
	else{

		cl->tail->next = cln;
		cl->tail = cln;
	}
	return cln;
}
// Remove the first node of a Candidate List
int CL_RemoveFirst(const CList cl){

	if(cl == NULL)
		return 1;

	if(cl->head == NULL)
		return 1;
	else{

		if(cl->tail == cl->head){

			CLNode temp = cl->head; 
			cl->head = NULL;
			cl->tail = NULL;
			free(temp);
		}
		else{

			CLNode temp = cl->head;
			cl->head = cl->head->next;
			free(temp);
		}
	}
	return 0;
}
// Get the first node of a Candidate List
CLNode CL_GetFirst(const CList cl){
	
	if(cl == NULL)
		return NULL;
	return cl->head;
}
// Return 0 if the Word List is empty, 1 if not
int CL_IsEmpty(const CList cl){

	if(cl == NULL)
		return -1;
	
	return cl->head == NULL ? 0 : 1;
}
// Return the size of the Candidate List
int CL_GetSize(const CList cl){

	if(cl == NULL)
		return -1;

	int size = 0;
	CLNode temp = cl->head;
	while(temp != NULL){

		size++;
		temp = temp->next;
	}
	return size;
}
// Destroy a Candidate List
int CL_Destroy(CList cl){

	if(cl == NULL)
		return 1;

	while(cl->head != NULL)
		CL_RemoveFirst(cl);
	free(cl);
	return 0;
}