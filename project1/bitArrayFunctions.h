#ifndef BIT_ARRAY_FUNCTIONS
#define BIT_ARRAY_FUNCTIONS

#include <stdio.h>

/// Set the k-th bit of an array to 1 ///
void  setBit( unsigned int A[],  unsigned long k );

/// checking if a bit array's bit is zero or one.   ///
/// The function returns one if the k-th bit is one ///
/// and it returns zero if the k-th bit is zero.    ///
int checkBit( unsigned int A[],  unsigned long k );

#endif
