#ifndef COUNTRY_LIST
#define COUNTRY_LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct countryNode {
  char* country;
  struct countryNode * next;
} countryNode;

typedef struct countryList {
	countryNode * head;
} countryList;

countryNode * createCountryNode(char* country);

countryList * createCountryList();

/// Add country at list ///
void addCountryToList(char* country, countryList * list);

void displayCountries(countryList * list);

/// return the N-th element ///
char** getNthCountry(countryList* list, int index);

char** searchCountryList(countryList *list, char* country);

/// search the list for a specific country and return 1 if the country exists in list, else return 0. ///
int existCountryAtList(countryList *list, char* country);

void destroyCountryList(countryList * list);

#endif
