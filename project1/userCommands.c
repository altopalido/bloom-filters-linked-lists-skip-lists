#include "userCommands.h"

void vaccineStatusBloom(char* citizenID, char* virusName, bloomFilterList* bfl)
{
	bloomfilter* bl = searchBloomFilterList(bfl, virusName);
	if (bl == NULL)
	{
		printf("There is no bloomfilter with name %s \n", virusName);
	}
	else
	{

		int exist = bloomFilterSearch(bl , (unsigned char*) citizenID);
		if (exist == 1)
		{
			printf("MAYBE\n");
		}
		else
		{
			printf("NOT VACCINATED\n");
		}
	}
}

void vaccineStatus1(char* citizenID, char* virusName, skipListList* sll)
{
	int id = atoi(citizenID);
	skiplist* sl = searchSkipListList(sll, virusName);
	if (sl == NULL)
	{
		printf("There is no skip list with name %s \n", virusName);
	}
	else
	{
		int exist = search(sl, id);
		if (exist == 1)
		{
			printf("VACCINATED ON %s\n", searchDate(sl, id));
		}
		else
		{
			printf("NOT VACCINATED\n");
		}
	}
}

void vaccineStatus2(char* citizenID, skipListList* vaccinatedList, skipListList* notVaccinatedList)
{
	// first we search the list of skip lists of vaccinated people 
	char* y = "YES";
	char* n = "NO";
	int id = atoi(citizenID);
	skipListNode * current1 = vaccinatedList->head;
	skipListNode * next1 = current1;
	while (current1 != NULL) 
	{	
		if (search(current1->sl, id) == 1) // if we found the citizen in that skip list
	    {
	      char* d = searchDate(current1->sl, id);
	      printf("%s %s %s\n", current1->sl->name, y, d);
	    }
		next1 = current1->next;
		current1 = next1;
	}
  	// then we search the list of skip lists of not vaccinated people
  	skipListNode * current2 = notVaccinatedList->head;
	skipListNode * next2 = current2;
	while (current2 != NULL) 
	{	
		if (search(current2->sl, id) == 1) // if we found the citizen in that skip list
	    {
	      printf("%s %s\n", current2->sl->name, n);
	    }
		next2 = current2->next;
		current2 = next2;
	}
}

void listnonVaccinatedPeople(char* virusName, skipListList* notVaccinatedList)
{
	skiplist* sl = searchSkipListList(notVaccinatedList, virusName);
	if (sl == NULL)
	{
		printf("There is no skip list with name %s \n", virusName);
	}
	else
	{
		int i = display(sl);
		if (i == 0)
		{
			printf("The skip list %s hasn't not vaccinated citizens\n", sl->name);
		} 
	}
}

void populationStatus1(char* country, char* virusName, char* d1, char* d2, skipListList* notVaccinatedList, skipListList* vaccinatedList)
{
    char date1[11];
    char date2[11];
    strcpy(date1, d1);
    strcpy(date2, d2); 
	// convert day month year to separate integers for each date
	char* day1 = getFirst1(date1);
	char* month1 = getNext1();
	char* year1 = getNext1();
	int day1i = atoi(day1);
	int month1i = atoi(month1);
	int year1i = atoi(year1);
	//printf("%d %d %d\n", day1i, month1i, year1i);

	char* day2 = getFirst1(date2);
	char* month2 = getNext1();
	char* year2 = getNext1();
	int day2i = atoi(day2);
	int month2i = atoi(month2);
	int year2i = atoi(year2);
	// end of converting

    int vaccNum;
    int totalNum;
    skiplist* slVacc = searchSkipListList(vaccinatedList, virusName);
    skiplist* slNotVacc = searchSkipListList(notVaccinatedList, virusName);
    if (slVacc == NULL)
    {
        printf("There is no skip list with name %s \n", virusName);
    }
    else
    {
        if((year1i<year2i) || (year1i == year2i && month1i<month2i) || (year1i == year2i && month1i == month2i && day1i<day2i) || (year1i == year2i && month1i == month2i && day1i==day2i))
        {
            vaccNum = citizenRangeDate(slVacc, country, day1i, month1i, year1i, day2i, month2i, year2i);
        }
        if((year1i>year2i) || (year1i == year2i && month1i>month2i) || (year1i == year2i && month1i == month2i && day1i>day2i))
        {
            vaccNum = citizenRangeDate(slVacc, country, day2i, month2i, year2i, day1i, month1i, year1i);
        }
        totalNum = citizenNumber(slVacc, country) + citizenNumber(slNotVacc, country);
        if (totalNum != 0)
        {
            float percent = ((float)vaccNum/(float)totalNum) * 100;
            printf("%s %d %f%% \n", country, vaccNum, percent);
        }
        else if(totalNum == 0)
        {
            float percent = 0.0;
            printf("%s %d %f%% \n", country, vaccNum, percent);
        }
    }
}

void populationStatus2(char* virusName, char* date1, char* date2, skipListList* notVaccinatedList, skipListList* vaccinatedList, countryList* listOfCountries)
{
    int i = 0;
    char** country = getNthCountry(listOfCountries, i);
    while(country != NULL)
    {
        populationStatus1(*country, virusName, date1, date2, notVaccinatedList, vaccinatedList);
        i++;
        country = getNthCountry(listOfCountries, i);
    }
}

void popStatusByAge1(char* country, char* virusName, char* d1, char* d2, skipListList* notVaccinatedList, skipListList* vaccinatedList)
{
    char date1[11];
    char date2[11];
    strcpy(date1, d1);
    strcpy(date2, d2); 
    // convert day month year to separate integers for each date
    char* day1 = getFirst1(date1);
    char* month1 = getNext1();
    char* year1 = getNext1();
    int day1i = atoi(day1);
    int month1i = atoi(month1);
    int year1i = atoi(year1);
    //printf("%d %d %d\n", day1i, month1i, year1i);

    char* day2 = getFirst1(date2);
    char* month2 = getNext1();
    char* year2 = getNext1();
    int day2i = atoi(day2);
    int month2i = atoi(month2);
    int year2i = atoi(year2);
    // end of converting

    int vaccNum0_20;
    int vaccNum20_40;
    int vaccNum40_60;
    int vaccNum60;
    int totalNum;
    skiplist* slVacc = searchSkipListList(vaccinatedList, virusName);
    skiplist* slNotVacc = searchSkipListList(notVaccinatedList, virusName);
    if (slVacc == NULL)
    {
        printf("There is no skip list with name %s \n", virusName);
    }
    else
    {
        if((year1i<year2i) || (year1i == year2i && month1i<month2i) || (year1i == year2i && month1i == month2i && day1i<day2i) || (year1i == year2i && month1i == month2i && day1i==day2i))
        {
            vaccNum0_20 = citizenRangeDate0_20(slVacc, country, day1i, month1i, year1i, day2i, month2i, year2i);
            vaccNum20_40 = citizenRangeDate20_40(slVacc, country, day1i, month1i, year1i, day2i, month2i, year2i);
            vaccNum40_60 = citizenRangeDate40_60(slVacc, country, day1i, month1i, year1i, day2i, month2i, year2i);
            vaccNum60 = citizenRangeDate60(slVacc, country, day1i, month1i, year1i, day2i, month2i, year2i);
        }
        if((year1i>year2i) || (year1i == year2i && month1i>month2i) || (year1i == year2i && month1i == month2i && day1i>day2i))
        {
            vaccNum0_20 = citizenRangeDate0_20(slVacc, country, day2i, month2i, year2i, day1i, month1i, year1i);
            vaccNum20_40 = citizenRangeDate20_40(slVacc, country, day2i, month2i, year2i, day1i, month1i, year1i);
            vaccNum40_60 = citizenRangeDate40_60(slVacc, country, day2i, month2i, year2i, day1i, month1i, year1i);
            vaccNum60 = citizenRangeDate60(slVacc, country, day2i, month2i, year2i, day1i, month1i, year1i);
        }
        totalNum = citizenNumber(slVacc, country) + citizenNumber(slNotVacc, country);
        if (totalNum != 0)
        {
            float percent0_20 = ((float)vaccNum0_20/(float)totalNum) * 100;
            printf("%s %d %f%% \n", "0-20", vaccNum0_20, percent0_20);
            float percent20_40 = ((float)vaccNum20_40/(float)totalNum) * 100;
            printf("%s %d %f%% \n", "20-40", vaccNum20_40, percent20_40);
            float percent40_60 = ((float)vaccNum40_60/(float)totalNum) * 100;
            printf("%s %d %f%% \n", "40-60", vaccNum40_60, percent40_60);
            float percent60 = ((float)vaccNum60/(float)totalNum) * 100;
            printf("%s %d %f%% \n", "60+", vaccNum60, percent60);
        }
        else if(totalNum == 0)
        {
            float percent0_20 = 0.0;
            printf("%s %d %f%% \n", "0-20", vaccNum0_20, percent0_20);
            float percent20_40 = 0.0;
            printf("%s %d %f%% \n", "20-40", vaccNum20_40, percent20_40);
            float percent40_60 = 0.0;
            printf("%s %d %f%% \n", "40-60", vaccNum40_60, percent40_60);
            float percent60 = 0.0;
            printf("%s %d %f%% \n", "60+", vaccNum60, percent60);
        }
    }
}

void popStatusByAge2(char* virusName, char* date1, char* date2, skipListList* notVaccinatedList, skipListList* vaccinatedList, countryList* listOfCountries)
{
    int i = 0;
    char** country = getNthCountry(listOfCountries, i);
    while(country != NULL)
    {   
        printf("%s\n", *country);
        popStatusByAge1(*country, virusName, date1, date2, notVaccinatedList, vaccinatedList);
        printf("\n");
        i++;
        country = getNthCountry(listOfCountries, i);
    }
}

void insertCitizenRecord1(char* citizenID, char* firstName, char* lastName, char* country, char* age, char* virusName, char* yes_no, skipListList* notVaccinatedList, skipListList* vaccinatedList, bloomFilterList* bfl, recordList* recList, countryList* cl, int bloomSize)
{
	int integerID = atoi(citizenID);
	if (existCountryAtList(cl, country) == 0) // if we see this country for the first time add it to list
    {
        addCountryToList(country, cl);
    }

	skiplist* sl = searchSkipListList(notVaccinatedList, virusName);
	if (sl == NULL) // if we see this virus for the first time
	{
		bloomfilter* bf = createBloomFilter(virusName, bloomSize); // create a new bloom filter for this virus
        addBloomFilterToList(bf, bfl); // add bloom filter to list
        skiplist* slNotVacc = createSkipList(virusName); // create a new skip list for not vaccinated people
        addSkipListToList(slNotVacc, notVaccinatedList); // add skip list for not vaccinated people to list
        skiplist* slVacc = createSkipList(virusName); // create a new skip list for vaccinated people
        addSkipListToList(slVacc, vaccinatedList); // add skip list for vaccinated people to list

        if (existRecordAtList(recList, citizenID) == 0) // if we see this citizen for the first time
        {
            char** c = searchCountryList(cl, country); // pointer at list to this country
            record* rec = createRecord (citizenID, firstName, lastName, c, age); // create a new record for the citizen
            addRecordToList(rec, recList); // add the new record to list
            record* r = searchRecordList(recList, citizenID);
            skiplistInsert(slNotVacc, integerID, NULL, r); // add citizen at skip list
            printf("CITIZEN %s ADDED\n", citizenID);
        }
        if (existRecordAtList(recList, citizenID) == 1) // if we have seen this citizen again
        {
        	record* r = searchRecordList(recList, citizenID);
        	skiplistInsert(slNotVacc, integerID, NULL, r);
        	printf("CITIZEN %s ADDED\n", citizenID);
        }
        
	}
	else // if we have seen this virus again
	{
		skiplist* slNotVacc = searchSkipListList(notVaccinatedList, virusName);
		skiplist* slVacc = searchSkipListList(vaccinatedList, virusName);
		if (existRecordAtList(recList, citizenID) == 0) // if we see this citizen for the first time
        {
            char** c = searchCountryList(cl, country); // pointer at list to this country
            record* rec = createRecord (citizenID, firstName, lastName, c, age); // create a new record for the citizen
            addRecordToList(rec, recList); // add the new record to list
            record* r = searchRecordList(recList, citizenID);
            skiplistInsert(slNotVacc, integerID, NULL, r); // add citizen at skip list
            printf("CITIZEN %s ADDED\n", citizenID);
        }
        if (existRecordAtList(recList, citizenID) == 1) // if we have seen this citizen again
        {
        	record* r = searchRecordList(recList, citizenID);
        	if ((search(slNotVacc, integerID) == 0) && (search(slVacc, integerID) == 0)) // if citizen is not already at not vaccinated skip list and is not already at vaccinated skip list, add citizen at not vaccinated skip list
            {
                skiplistInsert(slNotVacc, integerID, NULL, r);
                printf("CITIZEN %s ADDED\n", citizenID);
            }
            else if ((search(slVacc, integerID) == 1)) // if citizen is already at vaccinated skip list
            {
                printf("ERROR: CITIZEN %s ALREADY VACCINATED ON %s\n", citizenID, searchDate(slVacc, integerID));
            }
            else if ((search(slNotVacc, integerID) == 1)) // if citizen is already at not vaccinated skip list
            {
                printf("ERROR IN RECORD %s\n", citizenID);
            }
        }
	}
}

void insertCitizenRecord2(char* citizenID, char* firstName, char* lastName, char* country, char* age, char* virusName, char* yes_no, char* date, skipListList* vaccinatedList, skipListList* notVaccinatedList, bloomFilterList* bfl, recordList* recList, countryList* cl, dateVaccinatedList* dateList, int bloomSize)
{
	int integerID = atoi(citizenID);
	if (existCountryAtList(cl, country) == 0) // if we see this country for the first time add it to list
    {
        addCountryToList(country, cl);
    }

    if (existDateVaccinatedAtList(dateList, date) == 0) // if we see this date for the first time add it to list
    {
        addDateVaccinatedToList(date, dateList);
    }

	skiplist* sl = searchSkipListList(vaccinatedList, virusName);
	if (sl == NULL) // if we see this virus for the first time
	{
		bloomfilter* bf = createBloomFilter(virusName, bloomSize); // create a new bloom filter for this virus
        addBloomFilterToList(bf, bfl); // add bloom filter to list
        skiplist* slNotVacc = createSkipList(virusName); // create a new skip list for not vaccinated people
        addSkipListToList(slNotVacc, notVaccinatedList); // add skip list for not vaccinated people to list
        skiplist* slVacc = createSkipList(virusName); // create a new skip list for vaccinated people
        addSkipListToList(slVacc, vaccinatedList); // add skip list for vaccinated people to list

        if (existRecordAtList(recList, citizenID) == 0) // if we see this citizen for the first time
        {
            char** c = searchCountryList(cl, country); // pointer at list to this country
            record* rec = createRecord (citizenID, firstName, lastName, c, age); // create a new record for the citizen
            addRecordToList(rec, recList); // add the new record to list
            record* r = searchRecordList(recList, citizenID);
            char** d = searchDateVaccinatedList(dateList, date);
            skiplistInsert(slVacc, integerID, d, r); // add citizen at skip list
            bloomFilterInsert(bf, (unsigned char*)citizenID); //add citizen at bloom filter
            printf("CITIZEN %s ADDED\n", citizenID);
        }
        if (existRecordAtList(recList, citizenID) == 1) // if we have seen this citizen again
        {
        	record* r = searchRecordList(recList, citizenID);
        	char** d = searchDateVaccinatedList(dateList, date);
        	skiplistInsert(slVacc, integerID, d, r);
        	bloomFilterInsert(bf, (unsigned char*)citizenID); //add citizen at bloom filter
        	printf("CITIZEN %s ADDED\n", citizenID);
        }
        
	}
	else // if we have seen this virus again
	{
		bloomfilter* bf = searchBloomFilterList(bfl, virusName);
		skiplist* slNotVacc = searchSkipListList(notVaccinatedList, virusName);
		skiplist* slVacc = searchSkipListList(vaccinatedList, virusName);
		if (existRecordAtList(recList, citizenID) == 0) // if we see this citizen for the first time
        {
            char** c = searchCountryList(cl, country); // pointer at list to this country
            record* rec = createRecord (citizenID, firstName, lastName, c, age); // create a new record for the citizen
            addRecordToList(rec, recList); // add the new record to list
            record* r = searchRecordList(recList, citizenID);
            char** d = searchDateVaccinatedList(dateList, date);
            skiplistInsert(slVacc, integerID, d, r); // add citizen at skip list
            bloomFilterInsert(bf, (unsigned char*)citizenID); //add citizen at bloom filter
            printf("CITIZEN %s ADDED\n", citizenID);
        }
        if (existRecordAtList(recList, citizenID) == 1) // if we have seen this citizen again
        {
        	record* r = searchRecordList(recList, citizenID);
        	if ((search(slNotVacc, integerID) == 0) && (search(slVacc, integerID) == 0)) // if citizen is not already at not vaccinated skip list and is not already at vaccinated skip list, add citizen at vaccinated skip list
            {
            	char** d = searchDateVaccinatedList(dateList, date);
            	bloomFilterInsert(bf, (unsigned char*)citizenID); //add citizen at bloom filter
                skiplistInsert(slVacc, integerID, d, r);
                printf("CITIZEN %s ADDED\n", citizenID);
            }
            else if ((search(slVacc, integerID) == 1)) // if citizen is already at vaccinated skip list
            {
                printf("ERROR: CITIZEN %s ALREADY VACCINATED ON %s\n", citizenID, searchDate(slVacc, integerID));
            }
            else if ((search(slNotVacc, integerID) == 1)) // if citizen is already at not vaccinated skip list
            {
            	skiplistDelete(slNotVacc, integerID); // delete citizen from not vaccinated skip list
            	char** d = searchDateVaccinatedList(dateList, date);
            	skiplistInsert(slVacc, integerID, d, r); // add citizen at skip list
            	bloomFilterInsert(bf, (unsigned char*)citizenID); //add citizen at bloom filter
                printf("CITIZEN %s ADDED\n", citizenID);
            }
        }
	}
}

void vaccinateNow(char* citizenID, char* firstName, char* lastName, char* country, char* age, char* virusName, skipListList* vaccinatedList, skipListList* notVaccinatedList, bloomFilterList* bfl, recordList* recList, countryList* cl, dateVaccinatedList* dateList, int bloomSize)
{
	int integerID = atoi(citizenID);
	if (existCountryAtList(cl, country) == 0) // if we see this country for the first time add it to list
    {
        addCountryToList(country, cl);
    }

	skiplist* sl = searchSkipListList(vaccinatedList, virusName);
	if (sl == NULL) // if we see this virus for the first time
	{
		bloomfilter* bf = createBloomFilter(virusName, bloomSize); // create a new bloom filter for this virus
        addBloomFilterToList(bf, bfl); // add bloom filter to list
        skiplist* slNotVacc = createSkipList(virusName); // create a new skip list for not vaccinated people
        addSkipListToList(slNotVacc, notVaccinatedList); // add skip list for not vaccinated people to list
        skiplist* slVacc = createSkipList(virusName); // create a new skip list for vaccinated people
        addSkipListToList(slVacc, vaccinatedList); // add skip list for vaccinated people to list

        if (existRecordAtList(recList, citizenID) == 0) // if we see this citizen for the first time
        {
            char** c = searchCountryList(cl, country); // pointer at list to this country
            record* rec = createRecord (citizenID, firstName, lastName, c, age); // create a new record for the citizen
            addRecordToList(rec, recList); // add the new record to list
            record* r = searchRecordList(recList, citizenID);
            time_t timer = time(NULL);
            char date[20];
            struct tm* tm_info;
            tm_info = localtime(&timer);
            strftime(date, 20, "%d-%m-%Y", tm_info);
            printf("Today's date is: %s\n", date);
        	addDateVaccinatedToList(date, dateList);
            char** d = searchDateVaccinatedList(dateList, date);
            skiplistInsert(slVacc, integerID, d, r); // add citizen at skip list
            bloomFilterInsert(bf, (unsigned char*)citizenID); //add citizen at bloom filter
            printf("CITIZEN %s ADDED\n", citizenID);
        }
        if (existRecordAtList(recList, citizenID) == 1) // if we have seen this citizen again
        {
        	record* r = searchRecordList(recList, citizenID);
        	time_t timer = time(NULL);
            char date[20];
            struct tm* tm_info;
            tm_info = localtime(&timer);
            strftime(date, 20, "%d-%m-%Y", tm_info);
        	addDateVaccinatedToList(date, dateList);
        	char** d = searchDateVaccinatedList(dateList, date);
        	skiplistInsert(slVacc, integerID, d, r);
        	bloomFilterInsert(bf, (unsigned char*)citizenID);
        	printf("CITIZEN %s ADDED\n", citizenID);
        }
        
	}
	else // if we have seen this virus again
	{
		bloomfilter* bf = searchBloomFilterList(bfl, virusName);
		skiplist* slNotVacc = searchSkipListList(notVaccinatedList, virusName);
		skiplist* slVacc = searchSkipListList(vaccinatedList, virusName);
		if (existRecordAtList(recList, citizenID) == 0) // if we see this citizen for the first time
        {
            char** c = searchCountryList(cl, country); // pointer at list to this country
            record* rec = createRecord (citizenID, firstName, lastName, c, age); // create a new record for the citizen
            addRecordToList(rec, recList); // add the new record to list
            record* r = searchRecordList(recList, citizenID);
            time_t timer = time(NULL);
            char date[20];
            struct tm* tm_info;
            tm_info = localtime(&timer);
            strftime(date, 20, "%d-%m-%Y", tm_info);
        	addDateVaccinatedToList(date, dateList);
            char** d = searchDateVaccinatedList(dateList, date);
            skiplistInsert(slVacc, integerID, d, r); // add citizen at skip list
            bloomFilterInsert(bf, (unsigned char*)citizenID);
            printf("CITIZEN %s ADDED\n", citizenID);
        }
        if (existRecordAtList(recList, citizenID) == 1) // if we have seen this citizen again
        {
        	record* r = searchRecordList(recList, citizenID);
        	if ((search(slNotVacc, integerID) == 0) && (search(slVacc, integerID) == 0)) // if citizen is not already at not vaccinated skip list and is not already at vaccinated skip list, add citizen at vaccinated skip list
            {
            	time_t timer = time(NULL);
	            char date[20];
	            struct tm* tm_info;
	            tm_info = localtime(&timer);
	            strftime(date, 20, "%d-%m-%Y", tm_info);
        		addDateVaccinatedToList(date, dateList);
            	char** d = searchDateVaccinatedList(dateList, date);
            	bloomFilterInsert(bf, (unsigned char*)citizenID);
                skiplistInsert(slVacc, integerID, d, r);
                printf("CITIZEN %s ADDED\n", citizenID);
            }
            else if ((search(slVacc, integerID) == 1)) // if citizen is already at vaccinated skip list
            {
                printf("ERROR: CITIZEN %s ALREADY VACCINATED ON %s\n", citizenID, searchDate(slVacc, integerID));
            }
            else if ((search(slNotVacc, integerID) == 1)) // if citizen is already at not vaccinated skip list
            {
            	skiplistDelete(slNotVacc, integerID); // delete citizen from not vaccinated skip list
            	time_t timer = time(NULL);
	            char date[20];
	            struct tm* tm_info;
	            tm_info = localtime(&timer);
	            strftime(date, 20, "%d-%m-%Y", tm_info);
        		addDateVaccinatedToList(date, dateList);
            	char** d = searchDateVaccinatedList(dateList, date);
            	skiplistInsert(slVacc, integerID, d, r); // add citizen at skip list
            	bloomFilterInsert(bf, (unsigned char*)citizenID);
                printf("CITIZEN %s ADDED\n", citizenID);
            }
        }
	}
}