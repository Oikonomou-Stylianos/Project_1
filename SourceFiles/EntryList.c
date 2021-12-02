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
// File : EntryList.c
///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EntryList.h"
#include "List.h"
#include "DataStructs.h"
#include "BKTree.h"
#include "core.h"

Entry *create_entry(const char *word, void *payload){

    if (!word) return NULL;
    int wlen = strlen(word) + 1;    // +1 for the terminating \0;
    if (wlen > MAX_WORD_LENGTH + 1 || wlen < MIN_WORD_LENGTH + 1) return NULL;

    
    Entry *ent = (Entry *)malloc(sizeof(Entry));
    if (!ent) return NULL;
    ent->payload = payload;
    ent->word = (char *)malloc(wlen*sizeof(char));
    if (!(ent->word)) { free(ent); return NULL; }
    strcpy(ent->word, word);
    return ent;
}

ErrorCode create_entry_list(List **l){
    
    *l = create_list();
    return (*l) ? EC_SUCCESS : EC_FAIL;
}

unsigned int get_number_entries(const List *el){  //Might replace with a variable in the List struct
    
    return get_list_size(el);
}

ErrorCode add_entry(List *l, const Entry *entry){   //Might change up so it creates the entry itself aswell by calling create_entry()

    if (!l || !entry) return EC_FAIL;
    return (insert_list(l, (Entry *)entry)) ? EC_SUCCESS : EC_FAIL;
}

Entry *get_first(const List* el){

    return (el) ? (el->head) ? (Entry *)(el->head->data) : NULL : NULL;
}

Entry *get_next(const listnode* ln){    //Placeholder implementation, might change up the whole approach
    
    return (ln) ? (ln->next) ? (Entry *)(ln->next->data) : NULL : NULL;
}

ErrorCode destroy_entry_list(List *l){

    if (!l) return EC_FAIL;
    
    destroy_list(l, entry);
    return EC_SUCCESS;
}

Entry *copy_entry(const Entry *e){
    
    return (!e) ? NULL : create_entry(e->word, e->payload);
}

Entry *entry_exists(const List *l, const char *word){
    if (!l || !word) return NULL;
    listnode ln = l->head;
    Entry *temp = get_first(l); // = l->head->data
    while (temp){
        if (!strcmp(temp->word, word)) break;
        temp = get_next(ln);
    }
    return temp;
}

void print_entry_list(const List *l){
    if (!l) return;
    listnode *ln = l->head;
    printf("[ ");
    while (ln) {
        printf("%s ", ((Entry *)(ln->data))->word);
        ln = ln->next;
    }
    printf("]\n");
}

ErrorCode build_entry_index(const List *el, MatchType type, Index ix){

	if (!el) return EC_FAIL;

    *ix = BKT_Create(type);
	listnode *ln = el->head;
	while (ln){
		BKT_Insert(*ix, (Entry *)(ln->data));
		ln = ln->next;
	}

	return EC_SUCCESS;
}
ErrorCode lookup_entry_index(const char *w, Index ix, int threshold, List **result){

    *result = NULL;
    List *list;
	if (!(list = BKT_Search(*ix, w, threshold))) return EC_FAIL;
    *result = list;
    return EC_SUCCESS;
}

ErrorCode destroy_entry_index(Index ix){
    return (BKT_Destroy(*ix)) ? EC_FAIL : EC_SUCCESS;
}