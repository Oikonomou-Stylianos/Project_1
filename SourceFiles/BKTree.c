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

#include "BKTree.h"
#include "HashTable.h"
#include "LinkedList.h"

#include "distance.h"
#include "constructors.h"
#include "common_types.h"
#include "core.h"

// Create a BK-Tree  
BKTree BKT_Create(MatchType mt, DataType dt, DestroyFunction df){

	if(mt != MT_HAMMING_DIST && mt != MT_EDIT_DIST) return NULL;

	BKTree bkt = (BKTree )malloc(sizeof(bktree ));
	bkt->root = NULL;
	bkt->matchType = mt;

	bkt->dataType = dt;
	bkt->destroyFunction = df;

	return bkt;
}
// Create a BK-Tree node
BKTreeNode BKT_CreateNode(Pointer data){

	if(data == NULL) return NULL;

	BKTreeNode bktn = (BKTreeNode )malloc(sizeof(bk_tree_node));
	bktn->data = data;
	bktn->children = (bk_tree_node **)malloc(sizeof(bk_tree_node *) * MAX_WORD_LENGTH);
	int i;
	for(i = 0; i < MAX_WORD_LENGTH; i++)
		bktn->children[i] = NULL;

	return bktn;
}
// Insert a word into the BK-Tree
BKTreeNode BKT_Insert(const BKTree bkt, Pointer data){

	if(bkt == NULL || data == NULL) return NULL;

	int word_length, root_length = 0;
    switch(bkt->dataType){
        case StringType:
            word_length = strlen((char *)data);
            if(bkt->root != NULL) root_length = strlen((char *)(bkt->root->data));
            break;
        case EntryType:
            word_length = strlen((char *)(((Entry )data)->word));
            if(bkt->root != NULL) root_length = strlen((char *)(((Entry )(bkt->root->data))->word));
            break;
        default:
            printf("Error : [BKT_Insert] : Unsupported data type\n");
            return NULL;
    }

	if(word_length < MIN_WORD_LENGTH || word_length > MAX_WORD_LENGTH){
        // printf("%s, %d\n", (char *)(((Entry )data)->word), word_length);
        printf("Error : [BKT_Insert] : Word exceeded length limits\n");
        return NULL;
    }

	if(bkt->root == NULL){

		bkt->root = BKT_CreateNode(data);
		return bkt->root;
	}
	else{

		if(bkt->matchType == MT_HAMMING_DIST && root_length != word_length){
			printf("Warning : [BKT_Insert] : Attempted to insert word of different length in a BKTree with MatchType set to HammingDistance\n");
			return NULL;
		}
		return BKT_InsertNode(bkt, bkt->root, data);
	}
}
// Insert recursively a word into the BK-Tree
BKTreeNode BKT_InsertNode(const BKTree bkt, const BKTreeNode parent, Pointer data){

	if(bkt == NULL || parent == NULL || data == NULL) return NULL;

	int dist;
    switch(bkt->dataType){
        case StringType:
            dist = distance((char *)(parent->data), (char *)data, bkt->matchType);
            break;
        case EntryType:
            dist = distance((char *)(((Entry )(parent->data))->word), ((Entry )data)->word, bkt->matchType);
            break;
        default:
            printf("Error : [BKT_InsertNode] : Unsupported data type\n");
            return NULL;
    }

	if(dist == 0)
		return parent;
    else{
        if(parent->children[dist-1] == NULL){

            parent->children[dist-1] = BKT_CreateNode(data);
            return parent->children[dist-1];
        }
        else
            return BKT_InsertNode(bkt, parent->children[dist-1], data);
    }
}
// Search in the BK-Tree for words with distance from a given word defined by given threshold
LList BKT_Search(const BKTree bkt, const char *word, const unsigned int threshold){

	if(bkt == NULL || bkt->root == NULL || word == NULL || threshold < 1) return NULL;

	LList candidateList, wordList; 
    switch(bkt->dataType){
        case StringType:
            if(bkt->matchType == MT_HAMMING_DIST && strlen(word) != strlen((char *)(bkt->root->data))) return NULL;
            candidateList = LL_Create(BKTNodeType, NULL, &compareBKTNPtrString);
            wordList = LL_Create(StringType, &destroyString, &compareString);
            break;
        case EntryType:
            if(bkt->matchType == MT_HAMMING_DIST && strlen(word) != strlen((char *)(((Entry )(bkt->root->data))->word))) return NULL;
            candidateList = LL_Create(BKTNodeType, NULL, &compareBKTNPtrEntry);
            wordList = LL_Create(EntryType, NULL, &compareEntry);
            break;
        default:
            printf("Error : [BKT_Search] : Unsupported data type\n");
            return NULL;
    }
    // Insert the root in the Candidate List
    LL_InsertTail(candidateList, &(bkt->root));

	int i, leftBound, rightBound, dist;
	LLNode lln_temp;
	BKTreeNode *bktn_temp;
	while(!LL_IsEmpty(candidateList)){

		lln_temp = LL_GetHead(candidateList);
		bktn_temp = (BKTreeNode *)lln_temp->data;
		
        switch(bkt->dataType){
            case StringType:
                dist = distance(word, (char *)((*bktn_temp)->data), bkt->matchType);
                break;
            case EntryType:
                dist = distance(word, (char *)(((Entry )((*bktn_temp)->data))->word), bkt->matchType);
                break;
            default:
                printf("Error : [BKT_Search] : Unsupported data type\n");
                return NULL;
        }

		if(dist <= threshold){

            switch(bkt->dataType){
                case StringType:
                    LL_InsertTail(wordList, createString((char *)((*bktn_temp)->data)));
                    break;
                case EntryType:
                    LL_InsertTail(wordList, (*bktn_temp)->data);
                    break;
                default:
                    printf("Error : [BKT_Search] : Unsupported data type\n");
                    return NULL;
            }
		}

		leftBound = dist - threshold;
		rightBound = dist + threshold;

		for(i = 0; i < MAX_WORD_LENGTH; i++){

			if(i >= leftBound - 1 && i <= rightBound - 1 && (*bktn_temp)->children[i] != NULL)
                LL_InsertTail(candidateList, &((*bktn_temp)->children[i]));
		}
        LL_DeleteHead(candidateList);
	}
	LL_Destroy(candidateList);

	return wordList;
}
// Destroy a BK-Tree
int BKT_Destroy(BKTree bkt){

	if(bkt == NULL) return 1;

	BKT_DestroyNode(bkt, bkt->root);
	free(bkt);
	return 0;
}
// Destroy the BK-Tree nodes rec
int BKT_DestroyNode(BKTree bkt, BKTreeNode bktn){

	if(bkt == NULL || bktn == NULL) return 1;

	int i;
	for(i = 0; i < MAX_WORD_LENGTH; i++)
		BKT_DestroyNode(bkt, bktn->children[i]);
	
	if(bkt->destroyFunction != NULL) bkt->destroyFunction(bktn->data);
    free(bktn->children);
    free(bktn);

	return 0;
}