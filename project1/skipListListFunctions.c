#include "skipListListFunctions.h"

skipListNode * createSkipListNode(skiplist* sl){
  skipListNode * newSkipListNode = malloc(sizeof(skipListNode));
  if (!newSkipListNode) {
    return NULL;
  }
  newSkipListNode->sl = sl;
  newSkipListNode->next = NULL;
  return newSkipListNode;
}

skipListList * createSkipListList(){
  skipListList * list = malloc(sizeof(skipListList));
  if (!list) {
    return NULL;
  }
  list->head = NULL;
  printf("A skip list, list has been created!\n");
  return list;
}

/// Add skip list at the end of the list ///
void addSkipListToList(skiplist* sl, skipListList * list){
  skipListNode * current = NULL;
  if(list->head == NULL){
    list->head = createSkipListNode(sl);
  }
  else {
    current = list->head; 
    while (current->next!=NULL){
      current = current->next;
    }
    current->next = createSkipListNode(sl);
  }
}

/// Search skip list list by the name of the skip list and  ///
/// return a pointer to the skip list with this name.    ///
skiplist* searchSkipListList(skipListList *list, char* name){
	skipListNode * current = list->head;
	skipListNode * next = current;
	while (current != NULL) 
	{	
		if (strcmp(current->sl->name, name) == 0) 
    {
      //printf("uparxei\n");
      return current->sl;
    }
		next = current->next;
		current = next;
	}
  //printf("den uparxei %s\n", name);
	return NULL;
}

/// Search skiplist list by the name of the skiplist and  ///
/// return 1 if the skiplist exists in the list else return 0    ///
int existSkipListAtList(skipListList *list, char* name){
  int exist = 0;
  skipListNode * current = list->head;
  skipListNode * next = current;
  while (current != NULL) 
  { 
    if (strcmp(current->sl->name, name) == 0)
    {
      exist = 1;
      return exist;
    }
    next = current->next;
    current = next;
  }
  return exist;
}

/// Destroy skip list list ///
void destroySkipListList(skipListList * list){
  skipListNode * current = list->head;
  skipListNode * next = current;
  while(current != NULL){
    next = current->next;
    skiplistFree(current->sl);
    free(current);
    current = next;
  }
  free(list);
  printf("A skip list, list has been destroyed!\n");
}