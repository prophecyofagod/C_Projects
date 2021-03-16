/*	Mario Saiz
	Project Token
	OS: Professor Gallmeier
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
	char test[80];
	char *sep = " |"; // space and pipe '|'
	char *word, *phrase, *brkt, *brkb;

	strcpy(test, "ps -aux | more > out.txt");

	printf("using the string: %s\n", test);

	for(word = strtok(test, sep); word; word = strtok(NULL, sep))
	{
		printf("so far, we are at: %s\n", word);
	}

	return(0);
}