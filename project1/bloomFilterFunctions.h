#ifndef BLOOM_FILTER_FUNCTIONS
#define BLOOM_FILTER_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashFunctions.h"
#include "bitArrayFunctions.h"

typedef struct bloomfilter {
    char* name;
    int arraySize;
    unsigned int *bloomFilterBitArray;
} bloomfilter;



/// create an empty bloom filter. The arraySize is given in bytes. ///
bloomfilter* createBloomFilter(char* name, int arraySize);



/// bloomFilterSearch function checks if a string is already in bloom filter. ///
/// The function returns 0 if the string doesn't exist already                ///
/// and 1 if exists.                                                          ///
int bloomFilterSearch(bloomfilter* bloomFilter, unsigned char* s);



/// bloomFilterInsert function hashes a string and inputs it in bloom filter. /// 
void bloomFilterInsert(bloomfilter* bloomFilter, unsigned char* s);


void bloomFilterFree(bloomfilter* bloom);

#endif
