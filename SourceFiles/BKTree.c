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
// File : BKTree.c
///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_types.h"

#include "EntryList.h"
#include "BKTree.h"
#include "DataStructs.h"
#include "CandidateList.h"
#include "distance.h"
#include "core.h"

// Create a BK-Tree  
BKTree BKT_Create(MatchType mt){

	if(mt != MT_HAMMING_DIST && mt != MT_EDIT_DIST) return NULL;

	BKTree bkt = (BKTree )malloc(sizeof(bktree));
	bkt->root = NULL;
	bkt->matchType = mt;

	return bkt;
}
// Create a BK-Tree node
BKTreeNode BKT_CreateNode(Entry *e){

	if(e == NULL) return NULL;

	BKTreeNode bktn = (BKTreeNode )malloc(sizeof(bk_tree_node));
	bktn->entry = copy_entry(e);	
	bktn->children = (bk_tree_node **)malloc(sizeof(bk_tree_node *) * MAX_WORD_LENGTH);
	int i;
	for(i = 0; i < MAX_WORD_LENGTH; i++)
		bktn->children[i] = NULL;


	return bktn;
}
// Insert a word into the BK-Tree
BKTreeNode BKT_Insert(const BKTree bkt, Entry *e){

	if(bkt == NULL || e == NULL) return NULL;


	int word_length = strlen(e->word);
	if(word_length < MIN_WORD_LENGTH || word_length > MAX_WORD_LENGTH)
		return NULL;

	if(bkt->root == NULL){

		bkt->root = BKT_CreateNode(e);

		return bkt->root;
	}
	else{

		if(bkt->matchType == MT_HAMMING_DIST && strlen(bkt->root->entry->word) != strlen(e->word)){
			printf("Warning: [word = \"%s\"] : Attempted to insert word of different length in a BKTree with MatchType set to HammingDistance\n", e->word);
			return NULL;
		}

		return BKT_InsertNode(bkt, bkt->root, e);
	}
}
// Insert recursively a word into the BK-Tree
BKTreeNode BKT_InsertNode(const BKTree bkt, const BKTreeNode parent, Entry *e){

	if(bkt == NULL || parent == NULL || e == NULL) return NULL;

	int dist = distance(parent->entry->word, e->word, bkt->matchType);

	if(dist == 0)
		return parent;

	if(parent->children[dist-1] == NULL){

		parent->children[dist-1] = BKT_CreateNode(e);
		return parent->children[dist-1];
	}
	else
		return BKT_InsertNode(bkt, parent->children[dist-1], e);
}
// Search in the BK-Tree for words with distance from a given word defined by given threshold
List *BKT_Search(const BKTree bkt, const char *word, const int threshold){

	if(bkt == NULL || bkt->root == NULL || word == NULL || threshold < 1)
		return NULL;

	CList candidateList = CL_Create();
	List *wordList;
	create_entry_list(&wordList);

	CL_Insert(candidateList, &(bkt->root));

	int i, leftBound, rightBound, dist;
	CLNode cln_temp;
	BKTreeNode *bktn_temp;
	while(CL_IsEmpty(candidateList)){

		cln_temp = CL_GetFirst(candidateList);
		bktn_temp = cln_temp->candidate;
		
		dist = distance(word, (*bktn_temp)->entry->word, bkt->matchType);
		if(dist <= threshold){

			add_entry(wordList, copy_entry((*bktn_temp)->entry));
		}

		leftBound = dist - threshold;
		rightBound = dist + threshold;

		for(i = 0; i < MAX_WORD_LENGTH; i++){

			if(i >= leftBound - 1 && i <= rightBound - 1 && (*bktn_temp)->children[i] != NULL)
				CL_Insert(candidateList, &((*bktn_temp)->children[i]));
		}
		CL_RemoveFirst(candidateList);
	}
	CL_Destroy(candidateList);
	return wordList;
}
// Destroy a BK-Tree
int BKT_Destroy(BKTree bkt){

	if(bkt == NULL)
		return 1;

	BKT_DestroyNode(bkt->root);
	free(bkt);
	return 0;
}
// Destroy the BK-Tree nodes rec
int BKT_DestroyNode(BKTreeNode bktn){

	if(bktn == NULL)
		return 1;

	int i;
	for(i = 0; i < MAX_WORD_LENGTH; i++)
		BKT_DestroyNode(bktn->children[i]);
	free(bktn->children);
	destroy_entry(bktn->entry);
	free(bktn);
	return 0;
}