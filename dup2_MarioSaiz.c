/*	Mario Saiz
	Project Dup2
	OS: Professor Gallmeier
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
    int fd;

    printf("Example using dup2. \n");

    // open a file
    fd = open("myfile.txt", O_CREAT| O_RDWR, 0666);

    // now, use dup2 to redirect stdout to this file.
    // stdout has the value of 1
    dup2(fd, 1); // stdout will now be redirected to fd.

    printf("This will be printed to the file, not stdio\n");

    // now, let's show that the output of exec will also go to this file.
    execlp("ls", "ls", "-la", NULL);

    return(0);
}
