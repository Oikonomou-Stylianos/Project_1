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
// File : WordList.c
///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

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

		ll->tail->next = lln;
		ll->tail = lln;
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
    else if(ll->compareFunction(data, ll->head->data) <= 0){

        lln->next = ll->head;
        ll->head = lln;
    }
    else if(ll->compareFunction(data, ll->head->data) == 0){

        if(ll->destroyFunction != NULL) ll->destroyFunction(data);
        free(lln);
        lln = NULL;
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
            lln = NULL;
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
        for(i = 0; i < index; i++)
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
                if(strcmp((char *)value, ((Entry )temp->data)->word) == 0)
                    return temp;
                break;
            case EntryPtrType:
                if(strcmp((char *)value, (*(Entry *)temp->data)->word) == 0)
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
            if(strcmp((char *)value, ((Entry )lln->data)->word) == 0)
                return lln;
            break;
        case EntryPtrType:
            if(strcmp((char *)value, (*(Entry *)lln->data)->word) == 0)
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
        default:
            printf("Error: [LL_Search] : Unsupported data type\n");
    }

    return LL_SearchRec(ll, lln->next, value);
}
int LL_Exists(const LList ll, Pointer value){

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

    LLNode previous = ll->head, current;
    int i;
    for(i = 0; i < index; i++)
        previous = previous->next; 
    
    current = previous->next;
    previous->next = current->next;

    if(ll->destroyFunction != NULL) ll->destroyFunction(current->data);
    free(current);

    return 0;
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
		        printf("%s ", ((Entry )temp->data)->word);
                break;
            case EntryPtrType:
		        printf("%s ", (*(Entry *)temp->data)->word);
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
                printf(" match_type = %d\n match_dist = %u\n active = %c\n }", ((Query )(temp->data))->match_type, ((Query )(temp->data))->match_dist, ((Query )(temp->data))->active);
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
	
	return ll->head == NULL ? 0 : 1;
}
unsigned int LL_GetSize(const LList ll){

	if(ll == NULL) return -1;

    return ll->size;
}
int LL_Clean(const LList ll){

	if(ll == NULL) return 1;

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

	return 0;
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

////////////////////////////////////////////////////////////////////////////////////////////

int main(void){

    // String Example
    // LList myLL = LL_Create(StringType, &destroyString, &compareString);
    // LL_InsertTail(myLL, (Pointer )createString("Panagiwths"));
    // LL_InsertTail(myLL, (Pointer )createString("Anastasis"));
    // LL_InsertTail(myLL, (Pointer )createString("Stelios"));
    // LL_Print(myLL);
    // printf("Size: %d\n", LL_GetSize(myLL));
    // char *value = "Stelios";
    // printf("Search: %s\n", (char *)LL_Search(myLL, (Pointer )value)->data);
    // LL_DeleteTail(myLL);
    // LL_Print(myLL);
    // LL_DeleteHead(myLL);
    // LL_Print(myLL);
    // printf("Count: %d\n", LL_GetSize(myLL)); 
    // printf("Search: %s\n", (*(Entry *)(LL_SearchRec(myLL, myLL->head, "Stelios")->data))->word);
    // LL_Destroy(myLL);

    // Entry Example
    // LList myEntryLL = LL_Create(EntryType, &destroyEntry, &compareEntry);
    // LL_InsertTail(myEntryLL, (Pointer )createEntry("Anastasis"));
    // LL_InsertTail(myEntryLL, (Pointer )createEntry("Panagiwths"));
    // LL_InsertTail(myEntryLL, (Pointer )createEntry("Stelios"));

    // // LL_Print(myEntryLL);

    // LList myEntryPtrLL = LL_Create(EntryPtrType, NULL, &compareEntryPtr);
    // HashTable myHT = HT_Create(EntryPtrType, &djb2, NULL, &compareEntryPtr);

    // LLNode temp = LL_GetHead(myEntryLL), temp1;
    // while(temp != NULL){

    //     LL_InsertTail(myEntryPtrLL, (Pointer )(&(temp->data)));
    //     HT_Insert(myHT, (Pointer )(&(temp->data)));
    //     // printf("%s\n", ((Entry )(temp->data))->word);
    //     temp = LL_Next(myEntryLL, temp);
    // }
    
    // // LL_Print(myEntryPtrLL);
    // HT_Print(myHT);

    // LL_Destroy(myEntryPtrLL);
    // LL_Destroy(myEntryLL);

    // Int Example
    // time_t t;
    // srand(time(NULL));
    // LList myIntLL = LL_Create(IntType, &destroyInt, &compareInt);
    // int i;
    // for(i = 0; i < 10; i++)
    //     LL_InsertTail(myIntLL, createInt(rand()%100));
    // LL_Print(myIntLL);
    // LL_Destroy(myIntLL);

    // UInt Example
    // time_t t;
    // srand(time(NULL));
    // LList myUIntLL = LL_Create(UIntType, &destroyUInt, &compareUInt);
    // int i;
    // for(i = 0; i < 10; i++)
    //     // LL_InsertTail(myUIntLL, createUInt(rand()%100));
    //     LL_InsertTail(myUIntLL, createUInt(i));
    // LL_Print(myUIntLL);
    // LL_Destroy(myUIntLL);

    // Query Example
    // time_t t;
    // srand(time(NULL));
    // LList myQueryList = LL_Create(QueryType, &destroyQuery, &compareQuery);
    // int i;
    // unsigned int *qid;
    // for(i = 0; i < 10; i++){
    //     qid = createUInt(i);
    //     LL_InsertTail(myQueryList, (Pointer )createQuery(*qid, "one two three", i%3, rand()%5));
    // }
    // LL_Print(myQueryList);

    // BKTree - EntryList test
    LList myEntryLL = LL_Create(EntryType, &destroyEntry, &compareEntry);
    LL_InsertTail(myEntryLL, (Pointer )createEntry("hell"));
    LL_InsertTail(myEntryLL, (Pointer )createEntry("help"));
    LL_InsertTail(myEntryLL, (Pointer )createEntry("fall"));
    LL_InsertTail(myEntryLL, (Pointer )createEntry("felt"));
    LL_InsertTail(myEntryLL, (Pointer )createEntry("fell"));
    LL_InsertTail(myEntryLL, (Pointer )createEntry("small"));
    LL_InsertTail(myEntryLL, (Pointer )createEntry("melt"));
    LL_Print(myEntryLL);

    BKTree myBKT = BKT_Create(MT_EDIT_DIST, EntryPtrType, NULL);

    LLNode temp = LL_GetHead(myEntryLL);
    while(temp != NULL){

        BKT_Insert(myBKT, (Pointer )(&(temp->data)));
        temp = LL_Next(myEntryLL, temp);
    }

    LList result = BKT_Search(myBKT, "henn", 2);
    LL_Print(result);

    LL_Destroy(myEntryLL);
    LL_Destroy(result);
    BKT_Destroy(myBKT);

    return 0;
}