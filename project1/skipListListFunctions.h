#ifndef SKIP_LIST_LIST_FUNCTIONS
#define SKIP_LIST_LIST_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skipList.h"

typedef struct skipListNode {
  skiplist* sl;
  struct skipListNode * next;
} skipListNode;

typedef struct skipListList {
	skipListNode * head;
} skipListList;

skipListNode * createSkipListNode(skiplist* sl);

skipListList * createSkipListList();

/// Add skip list at the end of the list ///
void addSkipListToList(skiplist* sl, skipListList * list);

/// Search skip list list by the name of the skip list and  ///
/// return a pointer to the skip list with this name.    ///
skiplist* searchSkipListList(skipListList *list, char* name);

/// Search skiplist list by the name of the skiplist and  ///
/// return 1 if the skiplist exists in the list else return 0    ///
int existSkipListAtList(skipListList *list, char* name);

/// Destroy skip list list ///
void destroySkipListList(skipListList * list);

#endif