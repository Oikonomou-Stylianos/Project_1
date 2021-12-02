#pragma once

#include "core.h"
#include "DataStructs.h"

//Generic List functions, called by entry list functions and other potential list implementations
List *create_list(void);
ErrorCode destroy_node(listnode *, ListType);
ErrorCode destroy_list(List *, ListType);
List *insert_list(List *, void *);