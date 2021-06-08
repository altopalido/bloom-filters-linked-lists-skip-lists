#include "countryList.h"

countryNode * createCountryNode(char* country)
{
	countryNode * newCountryNode = malloc(sizeof(countryNode));
	if (!newCountryNode) 
	{
    	return NULL;
  	}
  	newCountryNode->country = malloc(strlen(country) + 1);
    strcpy(newCountryNode->country, country);
  	newCountryNode->next = NULL;
  	return newCountryNode;
}

countryList * createCountryList()
{
	countryList * list = malloc(sizeof(countryList));
	if (!list) 
	{
    	return NULL;
  	}
  	list->head = NULL;
  	printf("A country list has been created!\n");
  	return list;
}

void addCountryToList(char* country, countryList * list)
{
  countryNode * current = NULL;
  if(list->head == NULL)
  {
    list->head = createCountryNode(country);
  }
  else 
  {
    current = list->head; 
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = createCountryNode(country);
  }
}

void displayCountries(countryList * list)
{
  countryNode * current = list->head;
  countryNode * next = current;
  while (current != NULL) 
  { 
    printf("%s\n", current->country);
    next = current->next;
    current = next;
  }
}

char** getNthCountry(countryList* list, int index)
{
  int count = 0;
  countryNode * current = list->head;
  countryNode * next = current;
  while (current != NULL) 
  { 
    if (count == index)
      return &current->country;
    count++;
    next = current->next;
    current = next;
  }
  return NULL;
}

char** searchCountryList(countryList *list, char* country)
{
	countryNode * current = list->head;
	countryNode * next = current;
	while (current != NULL) 
	{	
		if (strcmp(current->country, country) == 0)
			return &current->country;
		next = current->next;
		current = next;
	}
	return NULL;
}

int existCountryAtList(countryList *list, char* country){
  int exist = 0;
  countryNode * current = list->head;
  countryNode * next = current;
  while (current != NULL) 
  { 
    if (strcmp(current->country, country) == 0)
    {
      exist = 1;
      return exist;
    }
    next = current->next;
    current = next;
  }
  return exist;
}

void destroyCountryList(countryList * list)
{
	countryNode * current = list->head;
	countryNode * next = current;
	while(current != NULL){
    next = current->next;
    free(current->country);
    free(current);
    current = next;
  }
  free(list);
  printf("A country list has been destroyed!\n");
}