#include "bloomFilterListFunctions.h"

bloomFilterNode * createBloomFilterNode(bloomfilter* bf){
  bloomFilterNode * newBloomFilterNode = malloc(sizeof(bloomFilterNode));
  if (!newBloomFilterNode) {
    return NULL;
  }
  newBloomFilterNode->bf = bf;
  newBloomFilterNode->next = NULL;
  return newBloomFilterNode;
}

bloomFilterList * createBloomFilterList(){
  bloomFilterList * list = malloc(sizeof(bloomFilterList));
  if (!list) {
    return NULL;
  }
  list->head = NULL;
  printf("A bloom filter list has been created!\n");
  return list;
}

/// Add bloomfilter at the end of the list ///
void addBloomFilterToList(bloomfilter* bf, bloomFilterList * list){
  bloomFilterNode * current = NULL;
  if(list->head == NULL)
  {
    list->head = createBloomFilterNode(bf);
  }
  else 
  {
    current = list->head; 
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = createBloomFilterNode(bf);
  }
  printf("The bloom Filter %s added at list\n", bf->name);
}

/// Search bloomfilter list by the name of the bloomfilter and  ///
/// return a pointer to the bloomfilter with this name.    ///
bloomfilter* searchBloomFilterList(bloomFilterList *list, char* name){
	bloomFilterNode * current = list->head;
	bloomFilterNode * next = current;
	while (current != NULL) 
	{	
		if (strcmp(current->bf->name, name) == 0)
    {
      //printf("egwww %s\n", current->bf->name);
      //printf("uparxei\n");
      return current->bf;
    }
		next = current->next;
		current = next;
	}
  //printf("esyyy %s\n", name);
  //printf("den uparxei\n");
	return NULL;
}

/// Search bloomfilter list by the name of the bloomfilter and  ///
/// return 1 if the bloom filter exists in the list else return 0    ///
int existBloomFilterAtList(bloomFilterList *list, char* name){
  int exist = 0;
  bloomFilterNode * current = list->head;
  bloomFilterNode * next = current;
  while (current != NULL) 
  { 
    if (strcmp(current->bf->name, name) == 0) 
    {
      exist = 1;
      return exist;
    }
    next = current->next;
    current = next;
  }
  return exist;
}

/// Destroy bloom filter list ///
void destroyBloomFilterList(bloomFilterList * list){
  bloomFilterNode * current = list->head;
  bloomFilterNode * next = current;
  while(current != NULL){
    next = current->next;
    bloomFilterFree(current->bf);
    free(current);
    current = next;
  }
  free(list);
  printf("A bloom filter list has been destroyed!\n");
}



