#include "fileHandling.h"
#include "userCommands.h"
#include "recordListFunctions.h"
#include "bloomFilterListFunctions.h"
#include "skipListListFunctions.h"
#include "dateVaccinatedList.h"
#include "countryList.h"

int main( int argc, char *argv[] )  
{
	/// checking if the number of arguments is correct ///
	if( argc == 5 ) 
	{
		/// convent the second argument into an integer ///
		int size = atoi(argv[4]);
		/// end of converting ///
		if (strcmp(argv[1], "-c") != 0 || strcmp(argv[3], "-b") != 0)
		{
			printf("Second parameter must be -c and fourth parameter must be -b.\n");
			exit(1);
		}
		if (size <= 0)
		{
			printf("You must give a positive number at fifth parameter and big enough like 100000.\n");
			exit(1);
		}
		printf("The arguments supplied are %s, %s, %s and %s\n", argv[1], argv[2], argv[3], argv[4]);
	}
	else if( argc > 5 ) 
	{
		printf("Too many arguments supplied.\n");
		exit(1);
	}
	else 
	{
		printf("Four arguments expected.\n");
		exit(1);
	}
	/// end of checking the number of arguments ///

	/// convent the second argument into an integer ///
	int bloomSize = atoi(argv[4]);
	/// end of converting ///

	/// create lists ///
	skipListList * listOfVaccinatedSkipLists = createSkipListList();
	skipListList * listOfNotVaccinatedSkipLists = createSkipListList();
	bloomFilterList * listOfBloomFilters = createBloomFilterList();
	recordList * listOfRecords = createRecordList();
	dateVaccinatedList * listOfDates = createDateVaccinatedList();
    countryList * listOfCountries = createCountryList();
	/// end of creating lists ///

    int i;
	FILE *fp;
    fp = openFile(argv[2]);

    if (fp == NULL) 
    {
        perror("Error!");
        exit(1);
    } 
    else 
    {
        char line[5000];

        while (!feof(fp)) 
        {
        	for (i = 0; i < 5000; i++)
        		line[i] = '\0';
            fgets(line, 5000, fp);
            if (strlen(line) < 2)
            	continue;
            char * ptr1 = strchr(line, '\r');
            char * ptr2 = strchr(line, '\n');

            if (ptr1 != NULL) 
            {
                *ptr1 = '\0';
            }
            if (ptr2 != NULL) 
            {
                *ptr2 = '\0';
            }
            /// store words ///
            char * id = getFirst(line);
            int integerID = atoi(id);
            char * name = getNext();
            // if (name == NULL)
            // 	continue;
            char * surname = getNext();
            char * country = getNext();
            if (existCountryAtList(listOfCountries, country) == 0) // if we see this country for the first time add it to list
            {
                addCountryToList(country, listOfCountries);
            }
            char * age = getNext();
            char * virus = getNext();
            char * yes_no = getNext();
            int i = 7; // we have 7 words
            /// end of storing words ///

            if (existBloomFilterAtList(listOfBloomFilters, virus) == 0) //if we see this virus for the first time
            {
            	bloomfilter* bf = createBloomFilter(virus, bloomSize); // create a new bloom filter for this virus
            	addBloomFilterToList(bf, listOfBloomFilters); // add bloom filter to list
            	skiplist* slNotVacc = createSkipList(virus); // create a new skip list for not vaccinated people
            	addSkipListToList(slNotVacc, listOfNotVaccinatedSkipLists); // add skip list for not vaccinated people to list
            	skiplist* slVacc = createSkipList(virus); // create a new skip list for vaccinated people
            	addSkipListToList(slVacc, listOfVaccinatedSkipLists); // add skip list for vaccinated people to list

            	if (existRecordAtList(listOfRecords, id) == 0) // if we see this citizen for the first time
            	{
                    char** c = searchCountryList(listOfCountries, country); // pointer at list to this country
            		record* rec = createRecord (id, name, surname, c, age); // create a new record for the citizen
            		addRecordToList(rec, listOfRecords); // add the new record to list
            		record* r = searchRecordList(listOfRecords, id);
            		//printf("laaaaaaa%s\n", *r->country);
            		if (strcmp(yes_no,"YES") == 0) // if yes add citizen at vaccinated skip list and at bloom filter
            		{
                        char * date = getNext();
                        if (existDateVaccinatedAtList(listOfDates, date) == 0) // if we see this date for the first time add it to list
                        {
                            addDateVaccinatedToList(date, listOfDates);
                        }
                        char** d = searchDateVaccinatedList(listOfDates, date); // this date
                        i = 8; // we have 8 words
                        //printf("%s\n", "YES");                        
            			skiplistInsert(slVacc, integerID, d, r);
            			//printf("laaaaaaa %s\n", *(searchRecord(slVacc, integerID)->country));
                        bloomFilterInsert(bf, (unsigned char*)id);
            		}
            		else if (strcmp(yes_no,"NO") == 0) // if no add citizen at not vaccinated skip list 
            		{
                        //printf("%s\n", "NO");
            			skiplistInsert(slNotVacc, integerID, NULL, r);
            		}

            	}
            	else if (existRecordAtList(listOfRecords, id) == 1) // if we have seen this citizen again
            	{
                    record* r = searchRecordList(listOfRecords, id);
                    if (strcmp(yes_no,"YES") == 0) // if yes add citizen at vaccinated skip list and at bloom filter
                    {
                        char * date = getNext();
                        if (existDateVaccinatedAtList(listOfDates, date) == 0) // if we see this date for the first time add it to list
                        {
                            addDateVaccinatedToList(date, listOfDates);
                        }
                        char** d = searchDateVaccinatedList(listOfDates, date); // this date
                        i = 8; // we have 8 words
                        //printf("%s\n", "YES");                        
                        skiplistInsert(slVacc, integerID, d, r);
                        //printf("laaaaaaa %s\n", *(searchRecord(slVacc, integerID)->country));
                        bloomFilterInsert(bf, (unsigned char*)id);
                    }
                    else if (strcmp(yes_no,"NO") == 0) // if no add citizen at not vaccinated skip list
                    {
                        //printf("%s\n", "NO");
                        skiplistInsert(slNotVacc, integerID, NULL, r);
                    }
            	}
            }

            else if (existBloomFilterAtList(listOfBloomFilters, virus) == 1) //if we have seen this virus again
            {
                bloomfilter* bf = searchBloomFilterList(listOfBloomFilters, virus);
                skiplist* slNotVacc = searchSkipListList(listOfNotVaccinatedSkipLists, virus);
                skiplist* slVacc = searchSkipListList(listOfVaccinatedSkipLists, virus);
                if (existRecordAtList(listOfRecords, id) == 0) // if we see this citizen for the first time
                {
                    char** c = searchCountryList(listOfCountries, country); // pointer at list to this country
                    record* rec = createRecord (id, name, surname, c, age); // create a new record for the citizen
                    addRecordToList(rec, listOfRecords); // add the new record to list
                    record* r = searchRecordList(listOfRecords, id);
                    if (strcmp(yes_no,"YES") == 0) // if yes add citizen at vaccinated skip list and at bloom filter
                    {
                        char * date = getNext();
                        if (existDateVaccinatedAtList(listOfDates, date) == 0) // if we see this date for the first time add it to list
                        {
                            addDateVaccinatedToList(date, listOfDates);
                        }
                        char** d = searchDateVaccinatedList(listOfDates, date); // this date
                        i = 8; // we have 8 words
                        //printf("%s\n", "YES");                        
                        skiplistInsert(slVacc, integerID, d, r);
                        //printf("laaaaaaa %s\n", *(searchRecord(slVacc, integerID)->country));
                        bloomFilterInsert(bf, (unsigned char*)id);
                    }
                    else if (strcmp(yes_no,"NO") == 0) // if no add citizen at not vaccinated skip list
                    {
                        //printf("%s\n", "NO");
                        skiplistInsert(slNotVacc, integerID, NULL, r);
                    }

                }
                else if (existRecordAtList(listOfRecords, id) == 1) // if we have seen this citizen again
                {
                    record* r = searchRecordList(listOfRecords, id);
                    if ((strcmp(yes_no,"YES") == 0) && (search(slVacc, integerID) == 0) && (search(slNotVacc,integerID) == 0)) // if yes and citizen is not already at vaccinated skip list and is not already at not vaccineted skip list, add citizen at vaccinated skip list and at bloom filter
                    {
                        char * date = getNext();
                        if (existDateVaccinatedAtList(listOfDates, date) == 0) // if we see this date for the first time add it to list
                        {
                            addDateVaccinatedToList(date, listOfDates);
                        }
                        char** d = searchDateVaccinatedList(listOfDates, date); // this date
                        i = 8; // we have 8 words
                        //printf("%s\n", "YES");                        
                        skiplistInsert(slVacc, integerID, d, r);
                        bloomFilterInsert(bf, (unsigned char*)id);
                    }
                    else if (strcmp(yes_no,"NO") == 0 && (search(slNotVacc, integerID) == 0) && (search(slVacc, integerID) == 0)) // if no and citizen is not already at not vaccinated skip list and is not already at vaccineted skip list, add citizen at not vaccinated skip list
                    {
                        //printf("%s\n", "NO");
                        skiplistInsert(slNotVacc, integerID, NULL, r);
                    }
                    else if ((strcmp(yes_no,"YES") == 0) && (search(slVacc, integerID) == 1)) // if yes and citizen is already at vaccinated skip list
                    {
                        printf("ERROR IN RECORD %s\n", r->citizenID);
                    }
                    else if (strcmp(yes_no,"NO") == 0 && (search(slNotVacc, integerID) == 1)) // if no and citizen is already at not vaccinated skip list
                    {
                        printf("ERROR IN RECORD %s\n", r->citizenID);
                    }
                }
            }
        }
    }
    closeFile(fp);

    char line[3000];

    do {
    	printf("What would you like to do? ");
        fgets(line, sizeof (line), stdin);

        if (strlen(line) < 2) {
            continue;
        }
        char * ptr1 = strchr(line, '\r');
        char * ptr2 = strchr(line, '\n');

        if (ptr1 != NULL) {
            *ptr1 = '\0';
        }
        if (ptr2 != NULL) {
            *ptr2 = '\0';
        }

        char * word = getFirst(line);
        //printf("%s\n", word);

        if (strcmp(word, "/vaccineStatusBloom") == 0) 
        {
            char *w1 = getNext();
            char *w2 = getNext();

            if (w1 != NULL && w2 != NULL) 
            {
            	printf("vaccineStatusBloom\n");
                // call the function vaccineStatusBloom
                vaccineStatusBloom(w1, w2, listOfBloomFilters);
            } 
            else 
            {
                printf("error: You gave less number of parameters! \n");
            }
        }

        if (strcmp(word, "/vaccineStatus") == 0) 
        {
            char *w1 = getNext();
            char *w2 = getNext();

            if (w1 != NULL && w2 != NULL) 
            {
            	printf("vaccineStatus1\n");
                // call the function vaccineStatus1
                vaccineStatus1(w1, w2, listOfVaccinatedSkipLists);
            } 
            else if (w1 != NULL && w2 == NULL) 
            {
            	printf("vaccineStatus2\n");
                // call the function vaccineStatus2
                vaccineStatus2(w1, listOfVaccinatedSkipLists, listOfNotVaccinatedSkipLists);
            }
            else 
            {
                printf("error: You gave less number of parameters! \n");
            }
        }

        if (strcmp(word, "/populationStatus") == 0) 
        {
            char *w1 = getNext();
            char *w2 = getNext();
            char *w3 = getNext();
            char *w4 = getNext();

            if (w1 != NULL && w2 != NULL && w3 != NULL && w4 != NULL) 
            {
            	printf("populationStatus with 4 parameters\n");
                // call the function populationStatus1 with all four arguments
                populationStatus1(w1, w2, w3, w4, listOfNotVaccinatedSkipLists, listOfVaccinatedSkipLists);
            } 
            else if (w1 != NULL && w2 != NULL && w3 != NULL && w4 == NULL) 
            {
            	printf("populationStatus with 3 parameters\n");
                if (w2[2] == '-' && w3[2] == '-') // if two dates given
                {
                	// call the function populationStatus2 with three arguments
                	populationStatus2(w1, w2, w3, listOfNotVaccinatedSkipLists, listOfVaccinatedSkipLists, listOfCountries);
                }
                else if(w2[2] != '-' && w3[2] != '-')
                {
                	printf("ERROR: Please give two dates!\n");
                }
            }
            else 
            {
                printf("error: You gave less number of parameters! \n");
            }
        }

        if (strcmp(word, "/popStatusByAge") == 0) 
        {
            char *w1 = getNext();
            char *w2 = getNext();
            char *w3 = getNext();
            char *w4 = getNext();

            if (w1 != NULL && w2 != NULL && w3 != NULL && w4 != NULL) 
            {
            	printf("popStatusByAge with 4 parameters\n");
                // call the function popStatusByAge with all four arguments
                popStatusByAge1(w1, w2, w3, w4, listOfNotVaccinatedSkipLists, listOfVaccinatedSkipLists);
            } 
            else if (w1 != NULL && w2 != NULL && w3 != NULL && w4 == NULL) 
            {
            	printf("popStatusByAge with 3 parameters\n");
                if (w2[2] == '-' && w3[2] == '-') // if two dates given
                {
                	// call the function popStatusByAge with three arguments
                	popStatusByAge2(w1, w2, w3, listOfNotVaccinatedSkipLists, listOfVaccinatedSkipLists, listOfCountries);
                }
                else if(w2[2] != '-' && w3[2] != '-')
                {
                	printf("ERROR: Please give two dates!\n");
                }
            }
            else 
            {
                printf("error: You gave less number of parameters! \n");
            }
        }

        if (strcmp(word, "/insertCitizenRecord") == 0) 
        {
            char *w1 = getNext();
            char *w2 = getNext();
            char *w3 = getNext();
            char *w4 = getNext();
            char *w5 = getNext();
            char *w6 = getNext();
            char *w7 = getNext();
            char *w8 = getNext();

            if (w1 != NULL && w2 != NULL && w3 != NULL && w4 != NULL && w5 != NULL && w6 != NULL && w7 != NULL && w8 != NULL) 
            {
            	printf("insertCitizenRecord with 8 parameters\n");
            	// call the function insertCitizenRecord2 with all eight arguments
            	insertCitizenRecord2(w1, w2, w3, w4, w5, w6, w7, w8, listOfVaccinatedSkipLists, listOfNotVaccinatedSkipLists, listOfBloomFilters, listOfRecords, listOfCountries, listOfDates, bloomSize);
            } 
            else if (w1 != NULL && w2 != NULL && w3 != NULL && w4 != NULL && w5 != NULL && w6 != NULL && w7 != NULL && w8 == NULL) 
            {
            	printf("insertCitizenRecord with 7 parameters\n");
                // call the function insertCitizenRecord1 with seven arguments
                insertCitizenRecord1(w1, w2, w3, w4, w5, w6, w7, listOfNotVaccinatedSkipLists, listOfVaccinatedSkipLists, listOfBloomFilters, listOfRecords, listOfCountries, bloomSize);
            }
            else 
            {
                printf("error: You gave less number of parameters! \n");
            }
        }

        if (strcmp(word, "/vaccinateNow") == 0) 
        {
            char *w1 = getNext();
            char *w2 = getNext();
            char *w3 = getNext();
            char *w4 = getNext();
            char *w5 = getNext();
            char *w6 = getNext();

            if (w1 != NULL && w2 != NULL && w3 != NULL && w4 != NULL && w5 != NULL && w6 != NULL) 
            {
            	printf("vaccinenateNow\n");
                // call the function vaccinenateNow
                vaccinateNow(w1, w2, w3, w4, w5, w6, listOfVaccinatedSkipLists, listOfNotVaccinatedSkipLists, listOfBloomFilters, listOfRecords, listOfCountries, listOfDates, bloomSize);
            } 
            else 
            {
                printf("error: You gave less number of parameters! \n");
            }
        }

        if (strcmp(word, "/list-nonVaccinated-Persons") == 0) 
        {
            char *w1 = getNext();

            if (w1 != NULL) 
            {
            	printf("list-nonVaccinated-Persons\n");
                // call the function list-nonVaccinated-Persons
                listnonVaccinatedPeople(w1, listOfNotVaccinatedSkipLists);
            } 
            else 
            {
                printf("error: You gave less number of parameters! \n");
            }
        }

        if (strcmp(word, "/vaccineStatusBloom") != 0 && strcmp(word, "/vaccineStatus") != 0 && strcmp(word, "/populationStatus") != 0 && strcmp(word, "/popStatusByAge") != 0 && strcmp(word, "/insertCitizenRecord") != 0 && strcmp(word, "/vaccinateNow") != 0 && strcmp(word, "/list-nonVaccinated-Persons") != 0 && strcmp(word, "/exit") != 0)
        {
        	printf("Invalid request! \n");
        }

    } while (strcmp(line, "/exit") != 0);

	destroySkipListList(listOfVaccinatedSkipLists);
	destroySkipListList(listOfNotVaccinatedSkipLists);
	destroyBloomFilterList(listOfBloomFilters);
    destroyCountryList(listOfCountries);
    destroyDateVaccinatedList(listOfDates);
    destroyRecordList(listOfRecords);
    
    return 0;
}