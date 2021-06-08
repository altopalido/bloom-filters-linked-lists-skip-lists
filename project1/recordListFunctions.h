#ifndef RECORD_LIST_FUNCTIONS
#define RECORD_LIST_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "records.h"

typedef struct recordNode {
  record* rec;
  struct recordNode * next;
} recordNode;

typedef struct recordList {
	recordNode * head;
} recordList;

recordNode * createRecordNode(record* rec);

recordList * createRecordList();

/// Add record at the end of the list ///
void addRecordToList(record* rec, recordList * list);

/// Search record list by the id of the record and  ///
/// return a pointer to the record with this id.    ///
record* searchRecordList(recordList *list, char* id);

int existRecordAtList(recordList *list, char* id);

/// Destroy record list ///
void destroyRecordList(recordList * list);

#endif
