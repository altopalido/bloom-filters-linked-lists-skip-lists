#include "fileHandling.h"


/// open a data file and check if opened successfully ///
FILE * openFile(char * f)
{
	FILE* file = fopen(f,"r"); //file pointer set to read-only
	if( file == NULL )
	{
		perror("Unable to open file!");
        exit(1);
	}
	else
	{
		printf("File opened succesfully!\n");
		return (file);
	}
}

/// close a file ///
void closeFile(FILE * f)
{	
	fclose(f);
	printf("File closed successfully!\n");
}

/// read a file line by line dynamicallyand return number of lines ///
int readFile(FILE * f)
{
	int numberOfLines = 0;
	size_t sz = 0;
	ssize_t len = 0;
	char *line = NULL;
	while((len = getline(&line, &sz, f)) >= 0 )
	{
		// printf("%s\n", line);
		numberOfLines++;
	}
	free(line);
	return numberOfLines;
}


/// give an input sentence and store each word in an array. Return the number of words. ///
int readWords(char* Sentence, char wordArray[8][30])
{
	int i = 1;
	char *token;
	token = strtok(Sentence," ");
	strcpy(wordArray[0],token); //put the first word in array
	while (token != NULL)
	{
		token = strtok(NULL," ");
		if (token != NULL)
		{
			strcpy(wordArray[i], token);
			i++;
		}
	}
	return i; //return total number of words 
}