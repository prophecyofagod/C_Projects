/*	Mario Saiz
	Homework 1
	OS: Professor Gallmeier
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <xlocale.h>

#define READ 0
#define WRITE 1

#define BUFFERSIZE 80

char * get_string()
{
   char *ptr = (char *)malloc(BUFFERSIZE * sizeof(char*));
   
   printf("Please enter a string: ");
   return(gets(ptr)); 

}

// swaps case in place
void swap_case(char *ptr,int len)
{
  int i;
  char c;

  for(i=0; i< len; i++)
  {
     c = ptr[i];
     ptr[i] = tolower(ptr[i]);
     if(ptr[i] == c) ptr[i] = toupper(ptr[i]);
  }
  
  return;
}

int main(int argc, char *argv[])
{
   int fd_pipe1[2];
   int fd_pipe2[2];
   pid_t pid;

   // create pipe used to send message from parent to child
   if(pipe(fd_pipe1) < 0)
   {
      perror("pipe 1 failed\n");
      exit(1);
   }

   // create the pipe used to send message from child to parent
   if(pipe(fd_pipe2) < 0 )
   {
     perror("pipe 2 creation failed\n");
     exit(1);
   }

   
   pid = fork();

   if(pid < 0)
   {
      perror("fork: ");
      exit(1);
   }


   if(pid > 0) // parent
   {
      char *ptr;
      char output[BUFFERSIZE];
      int len;
     
      // close read end of pipe 1
      close(fd_pipe1[READ]);

      // close write end of pipe 2
      close(fd_pipe2[WRITE]);

      ptr = get_string();
      len = strlen(ptr) + 1;
      if(ptr != NULL) 
         write(fd_pipe1[WRITE], ptr, len);

     read(fd_pipe2[READ], output, len);    
     printf("The output is: %s\n", output);

     wait(NULL); // wait for child to complete
     exit(0);

   }
   else if(pid == 0) // child
   {
      char input[BUFFERSIZE];
      int len;

      // close write end of pipe 1
      close(fd_pipe1[WRITE]);

      // close read end of pipe 2
      close(fd_pipe2[READ]);

      // read string from parent
      len = read(fd_pipe1[READ], input, BUFFERSIZE);
      swap_case(input, len);
      
      write(fd_pipe2[WRITE], input, len);

      printf("child is done... exiting\n");
      exit(0);
   }	   

   // we should not get here
   printf("something really bad happened\n");

   return 0;
}
