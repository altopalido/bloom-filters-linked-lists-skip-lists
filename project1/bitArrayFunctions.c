#include "bitArrayFunctions.h"

/// Set the k-th bit of an array to 1 ///
void  setBit( unsigned int A[],  unsigned long k )
{
    int i = k/32;        //gives the corresponding index in the array A
    int pos = k%32;      //gives the corresponding bit position in A[i]
    unsigned int flag = 1;   // flag = 0000.....00001
    flag = flag << pos;      // flag = 0000...010...000   (shifted k positions)
    A[i] = A[i] | flag;      // Set the bit at the k-th position in A[i]
}

/// checking if a bit array's bit is zero or one.   ///
/// The function returns one if the k-th bit is one ///
/// and it returns zero if the k-th bit is zero.    ///
int checkBit( unsigned int A[],  unsigned long k )
{
    return ( (A[k/32] & (1 << (k%32) )) != 0 ) ;     
}