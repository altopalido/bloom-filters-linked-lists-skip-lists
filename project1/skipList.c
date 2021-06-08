#include "skipList.h"
#include "mytok.h"

/// create a node dynamically with random level and a key ///
skiplistNode* createNode(int level, int key, char** date, record* rec) {
    skiplistNode* node = (skiplistNode*)malloc(sizeof(node) + level*sizeof(*node)); 
    if (NULL == node) // checking
    {	
    	//printf("Node has not been created\n");
    	//free(node);
    	return NULL;
    } 
    node->key = key;
    node->date = date;
    //if(date != NULL)
        //printf("iiiiiiiiiiii %s\n", *(date));
    node->rec = rec;
    //printf("A node has been created\n");
    return node;
}

/// create an empty skip list dinamically ///
skiplist* createSkipList(char * listName) {
    int i;
    skiplist* l = (skiplist*) malloc( sizeof(*l) ); 
    if (NULL == l) // checking
    {
    	return NULL;
    }
    l->name = malloc(strlen(listName) + 1);
    strcpy(l->name, listName); // the name of the skip list  
    l->level = 1; // at the beginning we have only one level
    l->header = createNode(SKIPLIST_MAXLEVEL, -1, NULL, NULL); // the header is a node with level MAXLEVEL and key -1 (no key)
    if (NULL == l->header) // checking
    {
    	printf("Skip list has not been created\n");
        // free(l);
        return NULL;
    }
    for (i=0; i<SKIPLIST_MAXLEVEL; i++) {
        l->header->forwards[i] = NULL; // at the beginning the levels are empty of nodes
    }
    printf("The skip list %s has been created\n", listName);
    return l;
}


/// Each element in the list is represented by a node                    ///
/// the level of the node is chosen randomly while insertion in the list ///
/// The level for node is decided by the following algorithm             ///
int randomLevel() {
    int level = 1;
    while ((random()&0xFFFF) < (SKIPLIST_P * 0xFFFF))
        level += 1;
    return (level<SKIPLIST_MAXLEVEL) ? level : SKIPLIST_MAXLEVEL;
}


/// search for element in skip list                  ///
/// it returns 1 if we found the key, else returns 0 ///
/// start from highest level of skip list            ///
/// move the current pointer forward while key       /// 
/// is greater than key of node next to current      ///
/// Otherwise inserted current in update and         ///
/// move one level down and continue search          ///
int search(skiplist* l, int key) {
    skiplistNode *current = l->header;
    int found = 0;
    int i;
    for (i=l->level-1; i>=0; i--) // start from top
    { 
        while (current->forwards[i] && current->forwards[i]->key < key)
        {
            current = current->forwards[i];
        }
    }
    current = current->forwards[0];
    if(current && current->key == key) // If current node have key equal to search key, we have found our target node
    {	
    	printf("Key %d found\n", key );
    	found = 1;
    	return found;
    }  

    //printf("Key %d not found\n", key );
    return found;
}

/// return the date that the citizen with the id has been vaccinated ///
char* searchDate(skiplist* l, int key) {
    skiplistNode *current = l->header;
    int i;
    for (i=l->level-1; i>=0; i--) // start from top
    { 
        while (current->forwards[i] && current->forwards[i]->key < key)
        {
            current = current->forwards[i];
        }
    }
    current = current->forwards[0];
    if(current && current->key == key) // If current node have key equal to search key, we have found our target node
    {   
        //printf("iiiiiiiiiiii %s\n", *(current->date));
        return *(current->date);
    }  
    return NULL;
}

/// return the record with information for the citizen with this id ///
record* searchRecord(skiplist* l, int key) {
    skiplistNode *current = l->header;
    int i;
    for (i=l->level-1; i>=0; i--) // start from top
    { 
        while (current->forwards[i] && current->forwards[i]->key < key)
        {
            current = current->forwards[i];
        }
    }
    current = current->forwards[0];
    if(current && current->key == key) // If current node have key equal to search key, we have found our target node
    {   
        return current->rec;
    }  
    return NULL;
}

/// start from highest level in the list and compare key of next node with the key to be inserted          ///
/// if key of next node is less than key to be inserted then we keep on moving forward on the same level   ///
/// else store the pointer to current node i at update[i] and move one level down and continue our search. ///
void skiplistInsert(skiplist* l, int key, char** date, record* rec) {
	// update[i] holds the pointer to node at level i from which we moved down to level i-1
	// so after insertion we can link nodes at every level with the new node
    skiplistNode *update[SKIPLIST_MAXLEVEL]; 
    skiplistNode *p = l->header;
    int i;
    //    start from highest level of skip list 
    //    move the current pointer forward while key  
    //    is greater than key of node next to current 
    //    Otherwise inserted current in update and  
    //    move one level down and continue search 
    for (i=l->level-1; i>=0; i--) //start from top 
    { 
        while (p->forwards[i] && p->forwards[i]->key < key) //keep on moving forward on the same level
        {
            p = p->forwards[i];
        }
        update[i] = p;
    }

    int level = randomLevel();

    // If random level is greater than list's current 
    // level (node with highest level inserted in  
    // list so far), initialize update value with pointer 
    // to header for further use 
    if (level > l->level) 
    {
        for (i=l->level; i<level; i++)
        {
            update[i] = l->header;
        }
        // update the list current level
        l->level = level;
    }

    p = createNode(level, key, date, rec);

    // insert the new node in all the level lists by re-arranging pointers
    for (i=0; i<level; i++) 
    {
        p->forwards[i] = update[i]->forwards[i];
        update[i]->forwards[i] = p;
    }
    printf("Successfully inserted %d key\n", key);
}

///  start from highest level and search for key          ///
///  after deleting we re-arrange pointers in every level ///
///  remove levels with no elements if any                ///
void skiplistDelete(skiplist* l, int key) {
    skiplistNode *update[SKIPLIST_MAXLEVEL]; 
    skiplistNode *p = l->header;
    int i;

    // start from highest level of skip list 
    // move the current pointer forward while key  
    // is greater than key of node next to current 
    // Otherwise inserted current in update and  
    // move one level down and continue search 
    for (i=l->level-1; i>=0; i--) 
    {
        while (p->forwards[i] && p->forwards[i]->key < key)
        {
            p = p->forwards[i];
        }
        update[i] = p;
    }

    // reached level 0 and forward pointer to  
    // right, which is possibly our desired node.
    p = p->forwards[0];

    if (!p || p->key != key) // not found
    {
        return;
    }

    //  start from lowest level and rearrange 
    //  pointers just like we do in singly linked list 
    //  to remove target node
    for (i=0; i<l->level; i++) 
    {
        if (update[i]->forwards[i] == p)
        {
            update[i]->forwards[i] = p->forwards[i];
        }
    }
    // After deletion of element there could be levels with no elements, 
    // so we will remove these levels as well by decrementing the level of Skip list.
    while (l->level > 1 && NULL == l->header->forwards[l->level - 1])
    {
        l->level --;
    }
    skiplistFreeNode(p);
    printf("Successfully deleted %d key\n", key);
}

/// display function prints all the records of the skip list.                                      ///
/// If the skip list is empty it returns 0 else returns the total number of citizens in skip list. ///
int display(skiplist* l) 
{
    int i = 0;
    skiplistNode *current = l->header->forwards[0];
    while (current != NULL) 
    {
        printf("%s %s %s %s %s\n", current->rec->citizenID, current->rec->firstName, current->rec->lastName, *current->rec->country, current->rec->age);
        //printf("%d \n", current->key); 
        current = current->forwards[0]; 
        i++;
    }
    return i;
}

/// The function returns total number of citizens from the country "country" in the skip list ///
int citizenNumber(skiplist* l, char* country) 
{
    int i = 0;
    skiplistNode *current = l->header->forwards[0];
    while (current != NULL) 
    {
        if (strcmp(*current->rec->country,country) == 0)
        {
            i++;
        } 
        current = current->forwards[0]; 
    }
    return i;
}

/// The function returns number of citizens vaccinated in a range date ///
int citizenRangeDate(skiplist* l, char* country, int day1i, int month1i, int year1i, int day2i, int month2i, int year2i)
{
    int num = 0;
    skiplistNode *current = l->header->forwards[0];
    while (current != NULL) 
    {
        // convert day month year to separate integers
        char* d = *current -> date;
        char date[11];
        strcpy(date, d);
        char* day = getFirst1(date);
        char* month = getNext1();
        char* year = getNext1();
        int dayi = atoi(day);
        int monthi = atoi(month);
        int yeari = atoi(year);
        // end of converting

        // if current date is between given dates
        if (((yeari>year1i) || (yeari == year1i && monthi>month1i) || (yeari == year1i && monthi == month1i && dayi>day1i)) &&  ((yeari<year2i) || (yeari == year2i && monthi<month2i) || (yeari == year2i && monthi == month2i && dayi<day2i)) && strcmp(*current->rec->country,country) == 0)
         {
            num++;
         }
        if ((year1i == year2i && month1i == month2i && day1i==day2i) && strcmp(*current->rec->country,country) == 0 && (yeari == year2i && monthi == month2i && dayi==day2i))
        {
            num++;
        } 
        current = current->forwards[0]; 
    }
    return num;
}

/// The function returns number of citizens vaccinated in a range date and the age is 0-20 ///
int citizenRangeDate0_20(skiplist* l, char* country, int day1i, int month1i, int year1i, int day2i, int month2i, int year2i)
{
    int num = 0;
    skiplistNode *current = l->header->forwards[0];
    while (current != NULL) 
    {
        // convert day month year to separate integers
        char* d = *current -> date;
        char date[11];
        strcpy(date, d);
        char* day = getFirst1(date);
        char* month = getNext1();
        char* year = getNext1();
        int dayi = atoi(day);
        int monthi = atoi(month);
        int yeari = atoi(year);
        // end of converting

        // if current date is between given dates
        if (((yeari>year1i) || (yeari == year1i && monthi>month1i) || (yeari == year1i && monthi == month1i && dayi>day1i)) &&  ((yeari<year2i) || (yeari == year2i && monthi<month2i) || (yeari == year2i && monthi == month2i && dayi<day2i)) && strcmp(*current->rec->country,country) == 0 && atoi(current->rec->age)>=0 && atoi(current->rec->age)<=20)
         {
            num++;
         }
        if ((year1i == year2i && month1i == month2i && day1i==day2i) && strcmp(*current->rec->country,country) == 0 && (yeari == year2i && monthi == month2i && dayi==day2i) &&  atoi(current->rec->age)>=0 && atoi(current->rec->age)<=20)
        {
            num++;
        } 
        current = current->forwards[0]; 
    }
    return num;
}

/// The function returns number of citizens vaccinated in a range date and the age is 20-40 ///
int citizenRangeDate20_40(skiplist* l, char* country, int day1i, int month1i, int year1i, int day2i, int month2i, int year2i)
{
    int num = 0;
    skiplistNode *current = l->header->forwards[0];
    while (current != NULL) 
    {
        // convert day month year to separate integers
        char* d = *current -> date;
        char date[11];
        strcpy(date, d);
        char* day = getFirst1(date);
        char* month = getNext1();
        char* year = getNext1();
        int dayi = atoi(day);
        int monthi = atoi(month);
        int yeari = atoi(year);
        // end of converting

        // if current date is between given dates
        if (((yeari>year1i) || (yeari == year1i && monthi>month1i) || (yeari == year1i && monthi == month1i && dayi>day1i)) &&  ((yeari<year2i) || (yeari == year2i && monthi<month2i) || (yeari == year2i && monthi == month2i && dayi<day2i)) && strcmp(*current->rec->country,country) == 0 && atoi(current->rec->age)>=20 && atoi(current->rec->age)<=40)
         {
            num++;
         }
        if ((year1i == year2i && month1i == month2i && day1i==day2i) && strcmp(*current->rec->country,country) == 0 && (yeari == year2i && monthi == month2i && dayi==day2i) &&  atoi(current->rec->age)>=20 && atoi(current->rec->age)<=40)
        {
            num++;
        } 
        current = current->forwards[0]; 
    }
    return num;
}

/// The function returns number of citizens vaccinated in a range date and the age is 40-60 ///
int citizenRangeDate40_60(skiplist* l, char* country, int day1i, int month1i, int year1i, int day2i, int month2i, int year2i)
{
    int num = 0;
    skiplistNode *current = l->header->forwards[0];
    while (current != NULL) 
    {
        // convert day month year to separate integers
        char* d = *current -> date;
        char date[11];
        strcpy(date, d);
        char* day = getFirst1(date);
        char* month = getNext1();
        char* year = getNext1();
        int dayi = atoi(day);
        int monthi = atoi(month);
        int yeari = atoi(year);
        // end of converting

        // if current date is between given dates
        if (((yeari>year1i) || (yeari == year1i && monthi>month1i) || (yeari == year1i && monthi == month1i && dayi>day1i)) &&  ((yeari<year2i) || (yeari == year2i && monthi<month2i) || (yeari == year2i && monthi == month2i && dayi<day2i)) && strcmp(*current->rec->country,country) == 0 && atoi(current->rec->age)>=40 && atoi(current->rec->age)<=60)
         {
            num++;
         }
        if ((year1i == year2i && month1i == month2i && day1i==day2i) && strcmp(*current->rec->country,country) == 0 && (yeari == year2i && monthi == month2i && dayi==day2i) &&  atoi(current->rec->age)>=40 && atoi(current->rec->age)<=60)
        {
            num++;
        } 
        current = current->forwards[0]; 
    }
    return num;
}

/// The function returns number of citizens vaccinated in a range date and the age is 60+ ///
int citizenRangeDate60(skiplist* l, char* country, int day1i, int month1i, int year1i, int day2i, int month2i, int year2i)
{
    int num = 0;
    skiplistNode *current = l->header->forwards[0];
    while (current != NULL) 
    {
        // convert day month year to separate integers
        char* d = *current -> date;
        char date[11];
        strcpy(date, d);
        char* day = getFirst1(date);
        char* month = getNext1();
        char* year = getNext1();
        int dayi = atoi(day);
        int monthi = atoi(month);
        int yeari = atoi(year);
        // end of converting

        // if current date is between given dates
        if (((yeari>year1i) || (yeari == year1i && monthi>month1i) || (yeari == year1i && monthi == month1i && dayi>day1i)) &&  ((yeari<year2i) || (yeari == year2i && monthi<month2i) || (yeari == year2i && monthi == month2i && dayi<day2i)) && strcmp(*current->rec->country,country) == 0 && atoi(current->rec->age)>=60)
         {
            num++;
         }
        if ((year1i == year2i && month1i == month2i && day1i==day2i) && strcmp(*current->rec->country,country) == 0 && (yeari == year2i && monthi == month2i && dayi==day2i) &&  atoi(current->rec->age)>=60)
        {
            num++;
        } 
        current = current->forwards[0]; 
    }
    return num;
}

/// free memory ///
void skiplistFreeNode(skiplistNode* node) 
{
    if (NULL == node) 
    {
    	return;
    }
    //recordFree(node->rec);
    free(node);
    node = NULL;
}

/// free memory ///
void skiplistFree(skiplist* l) {
    if (NULL == l) 
    {
    	return;
    }
    skiplistNode *p = l->header;
    skiplistNode *next;
    while (p) {
        next = p->forwards[0];
        skiplistFreeNode(p);
        p = next;
    }
    printf("skiplist %s has been destroyed\n", l->name);
    free(l->name);
    free(l);
    l = NULL;
}
