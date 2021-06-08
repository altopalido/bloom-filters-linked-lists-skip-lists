#ifndef SKIP_LIST
#define SKIP_LIST

#include "records.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SKIPLIST_MAXLEVEL 32 // Max level is the upper bound on number of levels in the skip list.
#define SKIPLIST_P 0.25 // p=1/4 and it is the base of logN to find the list level (N is the number of pointers in the list)

/// we create a struct for node. Each node carries a key which is the id  ///
/// and a forward array carrying pointers to nodes of a different level   ///
/// and a pointer to the date that the citizen has been vaccinated.       ///
typedef struct skiplistNode {
	record* rec;
	char** date;
    int key;
    struct skiplistNode* forwards[];
} skiplistNode;


typedef struct skiplist {
    struct skiplistNode* header;
    int level;
    char* name;
} skiplist;

/// create a node dynamically with random level and a key ///
skiplistNode* createNode(int level, int key, char** date, record* rec);

/// create an empty skip list dinamically ///
skiplist* createSkipList(char* listName);

/// Each element in the list is represented by a node                    ///
/// the level of the node is chosen randomly while insertion in the list ///
/// The level for node is decided by the following algorithm             ///
int randomLevel();

/// search for element in skip list                  ///
/// it returns 1 if we found the key, else returns 0 ///
/// start from highest level of skip list            ///
/// move the current pointer forward while key       /// 
/// is greater than key of node next to current      ///
/// Otherwise inserted current in update and         ///
/// move one level down and continue search          ///
int search(skiplist* l, int key);

/// return the date that the citizen with the id has been vaccinated ///
char* searchDate(skiplist* l, int key);

/// return the record with information for the citizen with this id ///
record* searchRecord(skiplist* l, int key);

/// start from highest level in the list and compare key of next node with the key to be inserted          ///
/// if key of next node is less than key to be inserted then we keep on moving forward on the same level   ///
/// else store the pointer to current node i at update[i] and move one level down and continue our search. ///
void skiplistInsert(skiplist* l, int key, char** date, record* rec);

///  start from highest level and search for key          ///
///  after deleting we re-arrange pointers in every level ///
///  remove levels with no elements if any                ///
void skiplistDelete(skiplist* l, int key);

/// display function prints all the records of the skip list.  ///
/// If the skip list is empty it returns 0.                    ///
int display(skiplist* l);

/// The function returns total number of citizens from the country "country" in the skip list ///
int citizenNumber(skiplist* l, char* country);

/// The function returns number of citizens vaccinated in a range date ///
int citizenRangeDate(skiplist* l, char* country, int day1i, int month1i, int year1i, int day2i, int month2i, int year2i);

/// The function returns number of citizens vaccinated in a range date and the age is 0-20 ///
int citizenRangeDate0_20(skiplist* l, char* country, int day1i, int month1i, int year1i, int day2i, int month2i, int year2i);

/// The function returns number of citizens vaccinated in a range date and the age is 20-40 ///
int citizenRangeDate20_40(skiplist* l, char* country, int day1i, int month1i, int year1i, int day2i, int month2i, int year2i);

/// The function returns number of citizens vaccinated in a range date and the age is 40-60 ///
int citizenRangeDate40_60(skiplist* l, char* country, int day1i, int month1i, int year1i, int day2i, int month2i, int year2i);

/// The function returns number of citizens vaccinated in a range date and the age is 60+ ///
int citizenRangeDate60(skiplist* l, char* country, int day1i, int month1i, int year1i, int day2i, int month2i, int year2i);

/// free memory ///
void skiplistFreeNode(skiplistNode* node);

/// free memory ///
void skiplistFree(skiplist* l);

#endif