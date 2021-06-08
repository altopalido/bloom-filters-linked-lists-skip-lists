#ifndef BLOOM_FILTER_LIST_FUNCTIONS
#define BLOOM_FILTER_LIST_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bloomFilterFunctions.h"

typedef struct bloomFilterNode {
  bloomfilter* bf;
  struct bloomFilterNode * next;
} bloomFilterNode;

typedef struct bloomFilterList {
	bloomFilterNode * head;
} bloomFilterList;

bloomFilterNode * createBloomFilterNode(bloomfilter* bf);

bloomFilterList * createBloomFilterList();

/// Add bloomfilter at the end of the list ///
void addBloomFilterToList(bloomfilter* bf, bloomFilterList * list);

/// Search bloomfilter list by the name of the bloomfilter and  ///
/// return a pointer to the bloomfilter with this name.    ///
bloomfilter* searchBloomFilterList(bloomFilterList *list, char* name);

/// Search bloomfilter list by the name of the bloomfilter and  ///
/// return 1 if the bloom filter exists in the list else return 0    ///
int existBloomFilterAtList(bloomFilterList *list, char* name);

/// Destroy bloomfilter list ///
void destroyBloomFilterList(bloomFilterList * list);



#endif