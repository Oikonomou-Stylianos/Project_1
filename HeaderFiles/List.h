#pragma once

#include "core.h"
#include "DataStructs.h"

//Generic List functions, called by entry list functions and other potential list implementations
List *create_list(void);
ErrorCode destroy_node(listnode *, DataType);
ErrorCode destroy_list(List *, DataType);
List *insert_list(List *, void *);
unsigned int get_list_size(const List *);