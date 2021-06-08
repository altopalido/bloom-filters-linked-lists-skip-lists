#include "dateVaccinatedList.h"

dateVaccinatedNode * createDateVaccinatedNode(char* dateVaccinated)
{
	dateVaccinatedNode * newDateVaccinatedNode = (dateVaccinatedNode *) malloc(sizeof(dateVaccinatedNode));
	if (!newDateVaccinatedNode) 
	{
    	return NULL;
  	}
  	newDateVaccinatedNode->dateVaccinated = malloc(strlen(dateVaccinated) + 1);
    strcpy(newDateVaccinatedNode->dateVaccinated, dateVaccinated);
  	newDateVaccinatedNode->next = NULL;
  	return newDateVaccinatedNode;
}

dateVaccinatedList * createDateVaccinatedList()
{
	dateVaccinatedList * list = (dateVaccinatedList*) malloc(sizeof(dateVaccinatedList));
	if (!list) 
	{
    	return NULL;
  	}
  	list->head = NULL;
  	printf("A dateVaccinated list has been created!\n");
  	return list;
}

void addDateVaccinatedToList(char* dateVaccinated, dateVaccinatedList * list)
{
  dateVaccinatedNode * current = NULL;
  if(list->head == NULL)
  {
    list->head = createDateVaccinatedNode(dateVaccinated);
  }
  else 
  {
    current = list->head; 
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = createDateVaccinatedNode(dateVaccinated);
  }
}

char** searchDateVaccinatedList(dateVaccinatedList *list, char* dateVaccinated)
{
	dateVaccinatedNode * current = list->head;
	dateVaccinatedNode * next = current;
	while (current != NULL) 
	{	
		if (strcmp(current->dateVaccinated, dateVaccinated) == 0)
			return &current->dateVaccinated;
		next = current->next;
		current = next;
	}
	return NULL;
}

int existDateVaccinatedAtList(dateVaccinatedList *list, char* dateVaccinated){
  int exist = 0;
  dateVaccinatedNode * current = list->head;
  dateVaccinatedNode * next = current;
  while (current != NULL) 
  { 
    if (strcmp(current->dateVaccinated, dateVaccinated) == 0)
    {
      exist = 1;
      return exist;
    }
    next = current->next;
    current = next;
  }
  return exist;
}

void destroyDateVaccinatedList(dateVaccinatedList * list)
{
	dateVaccinatedNode * current = list->head;
	dateVaccinatedNode * next = current;
	while(current != NULL)
	{
	    next = current->next;
	    free(current->dateVaccinated);
	    free(current);
	    current = next;
  	}
  	free(list);
  	printf("A dateVaccinated list has been destroyed!\n");
}
