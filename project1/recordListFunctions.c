#include "recordListFunctions.h"
#include "records.h"

recordNode * createRecordNode(record* rec){
  recordNode * newRecordNode =(recordNode *) malloc(sizeof(recordNode));
  if (!newRecordNode) {
    return NULL;
  }
  newRecordNode->rec = rec;
  newRecordNode->next = NULL;
  return newRecordNode;
}

recordList * createRecordList(){
  recordList * list =(recordList *) malloc(sizeof(recordList));
  if (!list) {
    return NULL;
  }
  list->head = NULL;
  printf("A record list has been created!\n");
  return list;
}

/// Add record at the end of the list ///
void addRecordToList(record* rec, recordList * list){
  recordNode * current = NULL;
  if(list->head == NULL)
  {
    list->head = createRecordNode(rec);
  }
  else 
  {
    current = list->head; 
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = createRecordNode(rec);
  }
}

/// Search record list by the id of the record and  ///
/// return a pointer to the record with this id.    ///
record* searchRecordList(recordList *list, char* id){
	recordNode * current = list->head;
	recordNode * next = current;
	while (current != NULL) 
	{	
		if (strcmp(current->rec->citizenID, id) == 0)
			return current->rec;
		next = current->next;
		current = next;
	}
	return NULL;
}

int existRecordAtList(recordList *list, char* id){
  int exist = 0;
  recordNode * current = list->head;
  recordNode * next = current;
  while (current != NULL) 
  { 
    if (strcmp(current->rec->citizenID, id) == 0)
    {
      exist = 1;
      return exist;
    }
    next = current->next;
    current = next;
  }
  return exist;
}

/// Destroy record list ///
void destroyRecordList(recordList * list){
  recordNode * current = list->head;
  recordNode * next = current;
  while(current != NULL){
    next = current->next;
    recordFree(current->rec);
    free(current);
    current = next;
  }
  free(list);
  printf("A record list has been destroyed!\n");
}
