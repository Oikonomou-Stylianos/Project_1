#include <stdlib.h>
#include "ItemDestructs.h"
#include "DataStructs.h"

List *create_list(void){

    List *list = (List *)malloc(sizeof(List));
    if(!list) return NULL;
    list->head = list->tail = NULL; 
    list->size = 0;
    return list;
}

ErrorCode destroy_node(listnode *ln, DataType type){

    if (!ln) return EC_FAIL;
    // ErrorCode ret;
    switch(type){   //Can be expanded
        case entry: destroy_entry((Entry *)(ln->data)); break;
        case query: destroy_query((Query *)(ln->data)); break;
        default: break; //Do nothing
    }
    //if (ret) return EC_FAIL;  //Mixes things up in the supposedly-never-gonna-occur-case where an entry list contains a NULL entry
    free(ln);
    return EC_SUCCESS;
}

ErrorCode destroy_list(List *l, DataType type){

    if (!l) return EC_FAIL;

    listnode *temp = l->head, *tbdestr;
    while (temp){
        tbdestr = temp;
        temp = temp->next;
        destroy_node(tbdestr, type);
    }
    free(l);
    return EC_SUCCESS;
}

List *insert_list(List *l, void *data){

    if (!l) return NULL;

    listnode* node = (listnode *)malloc(sizeof(listnode));
    if (!node) return NULL;
    node->next = NULL; 
    node->data = (void *)data;   //Data initialization
    (l->size)++;
    
    if (!(l->head)) {l->head = node; l->tail = node;}        //If list is empty, make new data head and tail
    else {
        l->tail->next = node;   //Data concatination
        l->tail = node;         //Update tail pointer
    }
    return l;
}

unsigned int get_list_size(const List *el){
    return (el) ? el->size: 0;
}