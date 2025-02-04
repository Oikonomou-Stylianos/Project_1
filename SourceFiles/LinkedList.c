///////////////////////////////////
// University: UoA DIT
// Course : [K23a] Software Development for Computer Systems
// Semester : Fall 2021-2022
// Professor : Yannis Ioannidis 
// Assistant : Sarantis Paskalis
// --------------------------------
// Students: Stylianos Oikonomou , Anastasios Triantafyllou
// ID : 1115201500243 , 1115201600173 
// --------------------------------
// File : LinkedList.c
///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>

#include "LinkedList.h"
#include "constructors.h"
#include "common_types.h"
#include "core.h"

#include "HashTable.h"  // For main
#include "BKTree.h"  // For main

LList LL_Create(DataType dt, DestroyFunction df, CompareFunction cf){

	LList ll = (LList )malloc(sizeof(llist ));
	if(ll == NULL) return NULL;

    ll->head = NULL;
	ll->tail = NULL;
    ll->size = 0;

	ll->dataType = dt;
	ll->destroyFunction = df;
	ll->compareFunction = cf;

	return ll;
}
LLNode LL_InsertHead(const LList ll, Pointer data){

	if(ll == NULL || data == NULL) return NULL;

	LLNode lln = (LLNode )malloc(sizeof(llnode ));
    if(lln == NULL) return NULL;

	lln->data = data;
	lln->next = NULL;

	if(ll->head == NULL){

		ll->head = lln;
		ll->tail = lln;
	}
	else{

        lln->next = ll->head;
		ll->head = lln;
	}
    ll->size++;

	return lln;
}
LLNode LL_InsertTail(const LList ll, Pointer data){

	if(ll == NULL || data == NULL) return NULL;

	LLNode lln = (LLNode )malloc(sizeof(llnode ));
    if(lln == NULL) return NULL;

	lln->data = data;
	lln->next = NULL;

	if(ll->head == NULL){

		ll->head = lln;
		ll->tail = lln;
	}
	else{

		ll->tail->next = lln;
		ll->tail = lln;
	}
    ll->size++;

	return lln;
}
LLNode LL_InsertSort(const LList ll , Pointer data){

    if(ll == NULL || data == NULL) return NULL;

	LLNode lln = (LLNode )malloc(sizeof(llnode ));
    if(lln == NULL) return NULL;

	lln->data = data;
	lln->next = NULL;

    if(ll->head == NULL){

        ll->head = lln;
        ll->tail = lln;
    }
    else if(ll->compareFunction(data, ll->head->data) <= 0){

        lln->next = ll->head;
        ll->head = lln;
    }
    else{

        LLNode temp = ll->head;
        while(temp->next != NULL && ll->compareFunction(data, temp->next->data) > 0)
            temp = temp->next;

        if(temp->next == NULL){

            temp->next = lln;
            ll->tail = lln;
        }
        else{

            lln->next = temp->next;
            temp->next = lln;
        }
    }
    ll->size++;

    return lln;
}
LLNode LL_InsertSortUnique(const LList ll , Pointer data){

    if(ll == NULL || data == NULL) return NULL;

	LLNode lln = (LLNode )malloc(sizeof(llnode ));
    if(lln == NULL) return NULL;

	lln->data = data;
	lln->next = NULL;

    if(ll->head == NULL){

        ll->head = lln;
        ll->tail = lln;
    }
    else if(ll->compareFunction(data, ll->head->data) < 0){

        lln->next = ll->head;
        ll->head = lln;
    }
    else if(ll->compareFunction(data, ll->head->data) == 0){

        if(ll->destroyFunction != NULL) ll->destroyFunction(data);
        free(lln);
        return NULL;
    }
    else{

        LLNode temp = ll->head;
        while(temp->next != NULL && ll->compareFunction(data, temp->next->data) > 0)
            temp = temp->next;

        if(temp->next == NULL){

            temp->next = lln;
            ll->tail = lln;
        }
        else if(ll->compareFunction(data, temp->next->data) < 0){

            lln->next = temp->next;
            temp->next = lln;
        }
        else{

            if(ll->destroyFunction != NULL) ll->destroyFunction(data);
            free(lln);
            return NULL;
        }
    }
    ll->size++;

    return lln;
}
LLNode LL_InsertAfter(const LList ll, const LLNode previous, Pointer data){

    if(ll == NULL || previous == NULL || data == NULL) return NULL;

	LLNode lln = (LLNode )malloc(sizeof(llnode ));
    if(lln == NULL) return NULL;

    lln->data = data;
    lln->next = previous->next;
    previous->next = lln;
    ll->size++;

    return lln;
}
LLNode LL_InsertAt(const LList ll, Pointer data, const unsigned int index){

    if(ll == NULL || data == NULL || index > LL_GetSize(ll)) return NULL;

    LLNode lln;

    if(index == 0)
        lln = LL_InsertHead(ll, data);
    else if(index == LL_GetSize(ll))
        lln = LL_InsertTail(ll, data);
    else{

        LLNode previous = ll->head;
        int i;
        for(i = 1; i < index; i++)
            previous = previous->next;
        
        lln = LL_InsertAfter(ll, previous, data);
    } 

    return lln;
}
LLNode LL_Search(const LList ll, Pointer value){

    if(ll == NULL || value == NULL) return NULL;

    LLNode temp = ll->head;
    while(temp != NULL){

        switch(ll->dataType){
            case StringType:
                if(strcmp((char *)value, (char *)(temp->data)) == 0)
                    return temp;
                break;
            case EntryType:
                if(strcmp((char *)value, ((Entry )(temp->data))->word) == 0)
                    return temp;
                break;
            case IntType:
                if(*(int *)value == *(int *)(temp->data))
                    return temp;
                break;
            case UIntType:
                if(*(unsigned int *)value == *(unsigned int *)(temp->data))
                    return temp;
                break;
            case QueryType:
                if(*(unsigned int *)value == ((Query )(temp->data))->query_id)
                    return temp;
                break;
            case QueryResultType:
                if(*(unsigned int *)value == ((QueryResult )(temp->data))->doc_id)
                    return temp;
                break;
            default:
                printf("Error: [LL_Search] : Unsupported data type\n");
        }
        temp = temp->next;
    }

    return NULL;
}
LLNode LL_SearchRec(const LList ll, const LLNode lln, Pointer value){

    if(ll == NULL || value == NULL) return NULL; 
    
    if(lln == NULL) return NULL;

    switch(ll->dataType){
        case StringType:
            if(strcmp((char *)value, (char *)(lln->data)) == 0)
                return lln;
            break;
        case EntryType:
            if(strcmp((char *)value, ((Entry )(lln->data))->word) == 0)
                return lln;
            break;
        case IntType:
            if(*(int *)value == *(int *)(lln->data))
                return lln;
            break;
        case UIntType:
            if(*(unsigned int *)value == *(unsigned int *)(lln->data))
                return lln;
            break;
        case QueryType:
            if(*(unsigned int *)value == ((Query )(lln->data))->query_id)
                return lln;
            break;
        case QueryResultType:
            if(*(unsigned int *)value == ((QueryResult )(lln->data))->doc_id)
                return lln;
            break;
        default:
            printf("Error: [LL_Search] : Unsupported data type\n");
    }

    return LL_SearchRec(ll, lln->next, value);
}
int LL_Exists(const LList ll, Pointer value){

    if(ll == NULL || value == NULL) return -1;

    return LL_Search(ll, value) != NULL ? 1 : 0;
}
int LL_DeleteHead(const LList ll){

	if(ll == NULL) return 1;
	
    if(ll->head == NULL) 
        return 1;
	else{

		if(ll->head == ll->tail){

			if(ll->destroyFunction != NULL) ll->destroyFunction(ll->head->data);
			free(ll->head);

			ll->head = NULL;
			ll->tail = NULL;
		}
		else{

			LLNode temp = ll->head;
			ll->head = ll->head->next;
			if(ll->destroyFunction != NULL) ll->destroyFunction(temp->data);
			free(temp);
		}
	}
    ll->size--;

	return 0;
}
int LL_DeleteTail(const LList ll){

	if(ll == NULL) return 1;
	
    if(ll->head == NULL) 
        return 1;
	else{

		if(ll->head == ll->tail){

			if(ll->destroyFunction != NULL) ll->destroyFunction(ll->tail->data);
			free(ll->tail);

			ll->head = NULL;
			ll->tail = NULL;
		}
		else{

            LLNode temp, temp_tail;
            temp_tail = LL_GetTail(ll);
            temp = LL_GetHead(ll);
            
			while(temp->next != temp_tail)
                temp = temp->next;
            
            if(ll->destroyFunction != NULL) ll->destroyFunction(ll->tail->data);
            free(ll->tail);
            temp->next = NULL;
            ll->tail = temp;
		}
	}
    ll->size--;

	return 0;
}
int LL_DeleteNth(const LList ll, const unsigned int index){

    if(ll == NULL) return -1;
    if(index > LL_GetSize(ll) - 1) return 1;

    if(index == 0)
        return LL_DeleteHead(ll);
    else if(index == LL_GetSize(ll) - 1)
        return LL_DeleteTail(ll);
    else{

        LLNode previous = ll->head, current;
        int i;
        for(i = 0; i < index; i++)
            previous = previous->next; 
        
        current = previous->next;
        previous->next = current->next;

        if(ll->destroyFunction != NULL) ll->destroyFunction(current->data);
        free(current);
        ll->size--;
    }

    return 0;
}
LList LL_Join(const LList ll1, LList ll2){

    if(ll1 == NULL || ll2 == NULL || ll1->dataType != ll2->dataType) return NULL;

    int exists;
    LLNode temp = LL_GetHead(ll2);
    while(temp != NULL){

        switch(ll1->dataType){
            case EntryType:
                exists = LL_Exists(ll1, (Pointer )((Entry )(temp->data))->word);
                break;
            default:
                exists = LL_Exists(ll1, (Pointer )(temp->data));
        }

        if(exists == 0){

            if(ll2->destroyFunction == NULL)
                LL_InsertTail(ll1, (Pointer )temp->data);
            else{

                switch(ll1->dataType){
                    case StringType:
                        LL_InsertTail(ll1, (Pointer )createString((char *)(temp->data)));
                        break;
                    case IntType:
                        LL_InsertTail(ll1, (Pointer )createInt(*(int *)(temp->data)));
                        break;
                    case UIntType:
                        LL_InsertTail(ll1, (Pointer )createUInt(*(unsigned int *)(temp->data)));
                        break;
                    case EntryType:
                        LL_InsertTail(ll1, (Pointer )createEntry(((Entry )(temp->data))->word));
                        break;
                    default:
                        printf("Error : [LL_Join] : Unsupported data type\n");
                        return NULL;
                }
            }
        }

        temp = LL_Next(ll2, temp);
    }
    LL_Destroy(ll2);
    
    return ll1;
}
Pointer LL_ToArray(const LList ll){

    if(ll == NULL || LL_IsEmpty(ll) == 1) return NULL;

    int index;
    LLNode temp;
    Pointer array;

    switch(ll->dataType){
        // case StringType:
        //     if((array = (char **)malloc(sizeof(char *) * LL_GetSize(ll))) == NULL) return NULL;
        //     break;
        case IntType:
            array = (int *)malloc(sizeof(int ) * LL_GetSize(ll));
            break;
        case UIntType:
            array = (unsigned int *)malloc(sizeof(unsigned int ) * LL_GetSize(ll));
            break;
        default:
            printf("Error : [LL_ToArray] : Unsupported data type\n");
            return NULL;
    }

    temp = LL_GetHead(ll);
    index = 0;
    while(temp != NULL){

        switch(ll->dataType){
            // case StringType:
            //     ((char **)array)[index] = (char *)malloc(sizeof(char ) * MAX_WORD_LENGTH);
            //     strcmp(((char **)array)[index], (char *)(temp->data));
            //     break;
            case IntType:
                ((int *)array)[index] = *(int *)(temp->data);
                break;
            case UIntType:
                ((unsigned int *)array)[index] = *(unsigned int *)(temp->data);
                break;
            default:
                printf("Error : [LL_ToArray] : Unsupported data type\n");
                return NULL;
            
        }
        temp = LL_Next(ll, temp);
        index++;
    }

    return array;
}
Pointer LL_GetValue(const LLNode lln){

    if(lln == NULL) return NULL;

    return lln->data;
}
LLNode LL_GetHead(const LList ll){

	if(ll == NULL) return NULL;
	
    return ll->head;
}
LLNode LL_GetTail(const LList ll){

	if(ll == NULL) return NULL;
	
    return ll->tail;
}
LLNode LL_GetNth(const LList ll, const unsigned int index){

    if(ll == NULL || index > LL_GetSize(ll) - 1) return NULL;

    LLNode temp = ll->head;
    int i;
    for(i = 0; i < index; i++)
        temp = temp->next; 

    return temp;
}
LLNode LL_Next(const LList ll, const LLNode lln){

    if(ll == NULL || lln == NULL) return NULL;
    
    return lln->next;
}
LLNode LL_Previous(const LList ll, const LLNode lln){

    if(ll == NULL || lln == NULL) return NULL;

    // If the given node is in the head of the List return NULL
    if(lln == ll->head) return NULL;

    LLNode temp = ll->head;
    while(temp->next != NULL && temp->next != lln)
        temp = temp->next;
    
    if(temp->next == NULL) 
        return NULL;
    else
        return temp;
}
int LL_Print(const LList ll){

	if(ll == NULL) return 1;

	LLNode temp = ll->head;
	printf("[ ");
	while(temp != NULL){

        switch(ll->dataType){
            case StringType:
		        printf("%s ", (char *)(temp->data));
                break;
            case EntryType:
		        printf("%s ", ((Entry )(temp->data))->word);
                break;
            case IntType:
                printf("%d ", *(int *)(temp->data));
                break;
            case UIntType:
                printf("%u ", *(unsigned int *)(temp->data));
                break;
            case QueryType:
                printf("\n {\n query_id = %u\n query_words = ", ((Query )(temp->data))->query_id);
                LL_Print(((Query )(temp->data))->query_words);
                printf(" match_type = %d\n match_dist = %u\n active = %d\n }", ((Query )(temp->data))->match_type, ((Query )(temp->data))->match_dist, ((Query )(temp->data))->active);
                break;
            case QueryResultType:
                printf("\n {\n doc_id = %u\n num_res = %u\n query_ids = [ ", ((QueryResult )(temp->data))->doc_id, ((QueryResult )(temp->data))->num_res);
                int i;
                for(i = 0; i < ((QueryResult )(temp->data))->num_res; i++)
                    printf("%u ", ((QueryResult )(temp->data))->query_ids[i]);
                printf("]\n }");
                break;
            default:
                printf("Error: [LL_Print] : Unsupported data type\n");
                return -1;
        }
		temp = temp->next;
	}
	printf("]\n");

	return 0;
}
int LL_IsEmpty(const LList ll){

	if(ll == NULL) return -1;
	
	return ll->head == NULL ? 1 : 0;
}
unsigned int LL_GetSize(const LList ll){

	if(ll == NULL) return -1;

    return ll->size;
}
LList LL_Clean(const LList ll){

	if(ll == NULL) return NULL;

    LLNode current, next;
    current = ll->head;
	while(current){
        
        next = current->next;
        if(ll->destroyFunction != NULL) ll->destroyFunction(current->data);
        free(current);
        current = next;
    }

    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;

	return ll;
}
int LL_Destroy(LList ll){

	if(ll == NULL) return 1;

    LLNode current, next;
    current = ll->head;
	while(current){
        
        next = current->next;
        if(ll->destroyFunction != NULL) ll->destroyFunction(current->data);
        free(current);
        current = next;
    }
	free(ll);

	return 0;
}
