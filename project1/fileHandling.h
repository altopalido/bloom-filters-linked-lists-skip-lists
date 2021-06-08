#ifndef FILE_HANDLING
#define FILE_HANDLING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "sentenceContent.h"

/// open a data file and check if opened successfully ///
FILE * openFile(char * f);

/// close a file ///
void closeFile(FILE * f);

/// read a file line by line dynamically and return number of lines ///
int readFile(FILE * f);

/// give an input sentence and store each word in an array. Return the number of words. ///
int readWords(char* Sentence, char wordArray[8][30]);

#endif