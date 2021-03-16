/*	Mario Saiz
	Project 1
	OS: Professor Gallmeier
*/


#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main() {
    
	pid_t pid;
    char buffer[1024];
    int numOne[2];
    int numTwo[2];

    pipe(numOne);
    if (pipe(numOne)==-1) {
        fprintf(stderr, "Pipe Failed");
        	return 1;
	}
	pipe(numTwo);
    if (pipe(numTwo)==-1) {
        fprintf(stderr, "Pipe Failed");
        	return 1;
    }
    pid = fork();
     if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        	return 1;
    }
    if (pid > 0) {

        int i;
        close(numOne[1]);

        read(numOne[0], buffer, sizeof(buffer));
        for(i = 0; i<sizeof(buffer); i++) {
            if(islower(buffer[i]))
                buffer[i] = toupper(buffer[i]);
            		else
                		buffer[i] = tolower(buffer[i]);
        }
        write(numTwo[1], buffer, strlen(buffer) + 1);
        	wait(NULL);
    }
    else if (pid == 0) {

        close(numOne[0]);

        printf("Your input: ");
        	fgets(buffer, sizeof(buffer), stdin);
        		printf("\nThe original message was: %s", buffer);
        			write(numOne[1], buffer, strlen(buffer) + 1);
        				read(numTwo[0], buffer, sizeof(buffer));
        					printf("The inverted message is: %s",buffer);
        exit(0);
    }
    return 0;
}
