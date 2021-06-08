#ifndef RECORDS
#define RECORDS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record {
    char* citizenID;
    char* firstName;
    char* lastName;
    char ** country;
    char* age;
} record;

record* createRecord (char* citizenID, char* firstName, char* lastName, char ** country, char* age);

void recordFree(record* r);

#endif