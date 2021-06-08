#ifndef DATE_VACCINATED_LIST
#define DATE_VACCINATED_LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dateVaccinatedNode {
  char* dateVaccinated;
  struct dateVaccinatedNode * next;
} dateVaccinatedNode;

typedef struct dateVaccinatedList {
	dateVaccinatedNode * head;
} dateVaccinatedList;

dateVaccinatedNode * createDateVaccinatedNode(char* dateVaccinated);

dateVaccinatedList * createDateVaccinatedList();

void addDateVaccinatedToList(char* dateVaccinated, dateVaccinatedList * list);

char** searchDateVaccinatedList(dateVaccinatedList *list, char* dateVaccinated);

int existDateVaccinatedAtList(dateVaccinatedList *list, char* dateVaccinated);

void destroyDateVaccinatedList(dateVaccinatedList * list);

#endif