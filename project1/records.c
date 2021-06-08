#include "records.h"

record* createRecord (char* citizenID, char* firstName, char* lastName, char ** country, char* age)
{	
	record* r = (record*) malloc(sizeof(record));
    if (NULL == r) // checking
    {
        return NULL;
    }
	r -> citizenID = malloc(strlen(citizenID) + 1);
    strcpy(r -> citizenID, citizenID);
	r -> firstName = malloc(strlen(firstName) + 1);
    strcpy(r -> firstName, firstName);
    r -> lastName = malloc(strlen(lastName) + 1);
    strcpy(r -> lastName, lastName);
    r -> age = malloc(strlen(age) + 1);
    strcpy(r -> age, age);
    r -> country = country;
    printf("A record has been created\n");
    return r;
}

void recordFree(record* r)
{
	if (NULL == r) 
    {
        return;
    }
    free(r -> citizenID);
    free(r -> firstName);
    free(r -> lastName);
    free(r -> age);
    free(r);
    r = NULL;
}