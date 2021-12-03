#pragma once

#include "DataStructs.h"
#include "List.h"

#include "core.h"

ErrorCode create_query_list(List **);
ErrorCode destroy_query_list(List *);
Query *create_query(const QueryID q_id, const MatchType q_match_type, const unsigned int q_match_distance, const unsigned int q_word_count);
Query *copy_query(const Query *);
ErrorCode add_query(List *, const Query *);
char query_active(Query *);
char toggle_query_active(Query *);