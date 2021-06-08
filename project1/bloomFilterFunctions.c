#include "bloomFilterFunctions.h"

/// create an empty bloom filter. The arraySize is given in bytes. ///
bloomfilter* createBloomFilter(char* bloomFilterName, int arraySize)
{   
    bloomfilter* b = (bloomfilter*) malloc(sizeof(bloomfilter));
    if (NULL == b) // checking
    {
        return NULL;
    }
    b->name = malloc(strlen(bloomFilterName) + 1);
    strcpy(b->name, bloomFilterName);
    b->arraySize = arraySize/4;
    b->bloomFilterBitArray = malloc(b->arraySize * sizeof(unsigned int));
    int j;
    for(j=0; j<b->arraySize; j++) //initialize bitArray to zeros
    {
    	b->bloomFilterBitArray[j] = 0;
    }
    printf("The bloom filter %s has been created\n", bloomFilterName);
    return b;
}



/// bloomFilterSearch function checks if a string is already in bloom filter. ///
/// The function returns 0 if the string doesn't exist already                ///
/// and 1 if exists.                                                          ///
int bloomFilterSearch(bloomfilter* bloomFilter, unsigned char* s)
{   
    int arraySize = (bloomFilter->arraySize) *32; //convert the array size from bytes to bits
	int i; 
    int K = 16;
    for (i = 0 ; i < K ; i++) // hash and check if exists
    {	
    	unsigned long h;
        h = hash_i(s,i) % arraySize;
        if( checkBit(bloomFilter -> bloomFilterBitArray, h) == 0)
        {
        	printf("%s doesn't exist! Go ahaid and insert if you like.\n", s);
        	return 0;
        } // if we find even one zero than string doesn't exist already in bloom filter
	}  
    printf("Maybe %s already exists!\n", s);
    return 1;
}



/// bloomFilterInsert function hashes a string and inputs it in bloom filter. /// 
void bloomFilterInsert(bloomfilter* bloomFilter, unsigned char* s)
{
    int arraySize = (bloomFilter->arraySize) *32; //convert the array size from bytes to bits
    // check if the element is already present or not
    if (bloomFilterSearch(bloomFilter, s))
    {
        //printf("%s is probably already exist\n", s);
        return;
    }
    // if it doesn't present, insert
    else
    {
    	int i; 
    	int K=16;
        for (i = 0 ; i < K ; i++) 
        {	
        	unsigned long h;
        	h = hash_i(s,i) % arraySize;
			//printf("hash_%d (%s) : %lu \n", i, s, h);
			setBit(bloomFilter -> bloomFilterBitArray, h);
		} // end of hashing and inserting 
        printf("%s inserted in bloom filter\n", s);
    }
}

/// free memory ///
void bloomFilterFree(bloomfilter* bloom) 
{
    if (NULL == bloom) 
    {
        return;
    }
    printf("The bloom filter %s has been destroyed\n", bloom->name);
    free(bloom->bloomFilterBitArray);
    free(bloom->name);
    free(bloom);
    bloom = NULL;
}
