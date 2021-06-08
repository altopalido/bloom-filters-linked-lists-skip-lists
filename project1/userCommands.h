#ifndef USER_COMMANDS
#define USER_COMMANDS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bloomFilterListFunctions.h"
#include "skipListListFunctions.h"
#include "recordListFunctions.h"
#include "countryList.h"
#include "dateVaccinatedList.h"
#include <time.h>
#include "mytok.h"

void vaccineStatusBloom(char* citizenID, char* virusName, bloomFilterList* bl);

void vaccineStatus1(char* citizenID, char* virusName, skipListList* sll);

void vaccineStatus2(char* citizenID, skipListList* vaccinatedList, skipListList* notVaccinatedList);

void listnonVaccinatedPeople(char* virusName, skipListList* notVaccinatedList);

void populationStatus1(char* country, char* virusName, char* d1, char* d2, skipListList* notVaccinatedList, skipListList* vaccinatedList);

void populationStatus2(char* virusName, char* date1, char* date2, skipListList* notVaccinatedList, skipListList* vaccinatedList, countryList* listOfCountries);

void popStatusByAge1(char* country, char* virusName, char* d1, char* d2, skipListList* notVaccinatedList, skipListList* vaccinatedList);

void popStatusByAge2(char* virusName, char* date1, char* date2, skipListList* notVaccinatedList, skipListList* vaccinatedList, countryList* listOfCountries);

void insertCitizenRecord1(char* citizenID, char* firstName, char* lastName, char* country, char* age, char* virusName, char* yes_no, skipListList* notVaccinatedList, skipListList* vaccinatedList, bloomFilterList* bfl, recordList* recList, countryList* cl, int bloomSize);

void insertCitizenRecord2(char* citizenID, char* firstName, char* lastName, char* coutry, char* age, char* virusName, char* yes_no, char* date, skipListList* vaccinatedList, skipListList* notVaccinatedList, bloomFilterList* bfl, recordList* recList, countryList* cl, dateVaccinatedList* dateList, int bloomSize);

void vaccinateNow(char* citizenID, char* firstName, char* lastName, char* country, char* age, char* virusName, skipListList* vaccinatedList, skipListList* notVaccinatedList, bloomFilterList* bfl, recordList* recList, countryList* cl, dateVaccinatedList* dateList, int bloomSize);

#endif
