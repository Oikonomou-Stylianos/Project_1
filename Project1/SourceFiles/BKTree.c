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

#include "../HeaderFiles/BKTree.h"
#include "../HeaderFiles/CandidateList.h"
#include "../HeaderFiles/WordList.h"
#include "../HeaderFiles/common_types.h"

// Create a BK-Tree  
BKTree BKT_Create(){

	BKTree bkt = (BKTree )malloc(sizeof(bktree));
	bkt->root = NULL;

	return bkt != NULL ? bkt : NULL;
}
// Create a BK-Tree node
BKTreeNode BKT_CreateNode(char *word){

	if(word == NULL)
		return NULL;

	BKTreeNode bktn = (BKTreeNode )malloc(sizeof(bk_tree_node));
	strcpy(bktn->word, word);
	bktn->children = (bk_tree_node **)malloc(sizeof(bk_tree_node *) * MAX_WORD_LENGTH);
	int i;
	for(i = 0; i < MAX_WORD_LENGTH; i++)
		bktn->children[i] = NULL;

	return bktn;
}
// Insert a word into the BK-Tree
BKTreeNode BKT_Insert(BKTree bkt, char *word){

	if(bkt == NULL || word == NULL)
		return NULL;

	if(bkt->root == NULL){

		bkt->root = BKT_CreateNode(word);
		return bkt->root;
	}
	else
		return BKT_InsertNode(bkt->root, word);
}
// Insert recursively a word into the BK-Tree
BKTreeNode BKT_InsertNode(BKTreeNode parent, char *word){

	if(parent == NULL || word == NULL)
		return NULL;

	int dist = distance(parent->word, word);

	if(dist == 0)
		return parent;

	if(parent->children[dist-1] == NULL){

		parent->children[dist-1] = BKT_CreateNode(word);
		return parent->children[dist-1];
	}
	else
		return BKT_InsertNode(parent->children[dist-1], word);
}
// Search the BK-Tree for words with edit distance from a given word defined by given contraints
WList BKT_Search(BKTree bkt, char *word, int constraint){

	if(bkt == NULL || bkt->root == NULL || word == NULL || constraint < 1)
		return NULL;

	CList candidateList = CL_Create();
	WList wordList = WL_Create();

	CL_Insert(candidateList, &(bkt->root));

	int i, leftBound, rightBound, dist;
	CLNode cln_temp;
	BKTreeNode *bktn_temp;
	while(CL_IsEmpty(candidateList)){

		cln_temp = CL_GetFirst(candidateList);
		bktn_temp = cln_temp->candidate;
		
		dist = distance(word, (*bktn_temp)->word);
		if(dist <= constraint){

			WL_Insert(wordList, (*bktn_temp)->word);
		}

		leftBound = dist - constraint;
		rightBound = dist + constraint;

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

	BKT_DestroyNodes(bkt->root);
	free(bkt);
	return 0;
}
// Destroy the BK-Tree nodes rec
int BKT_DestroyNodes(BKTreeNode bktn){

	if(bktn == NULL)
		return 0;

	int i;
	for(i = 0; i < MAX_WORD_LENGTH; i++)
		BKT_DestroyNodes(bktn->children[i]);
	free(bktn->children);
	free(bktn);
	return 0;
}