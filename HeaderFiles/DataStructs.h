#include "core.h"

typedef struct {
    char *word;
    void *payload;
} Entry;

typedef struct lnode {
    void *data;
    struct lnode *next;
} listnode;

typedef struct {
    listnode *head;
    listnode *tail;
    unsigned int size;
} List;

typedef enum { 
    entry,          //Can be expanded
    other,
} ListType;

typedef struct bk_tree_node_tag{

	Entry *entry;
	struct bk_tree_node_tag** children;

}bk_tree_node;
typedef bk_tree_node* BKTreeNode;

typedef struct{

	BKTreeNode root;
	MatchType matchType;
}bktree;
typedef bktree* BKTree;

typedef BKTree *Index;