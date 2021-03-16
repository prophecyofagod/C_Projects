/*	Mario Saiz
	Project 4
	OS: Professor Gallmeier
*/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char* argv[]) {
	char* file = argv[1];
		int fd;
			struct flock lock;

	printf ("opening %s\n", file);
		fd = open (file, O_WRONLY);
	printf ("locking\n");
		memset (&lock, 0, sizeof(lock));
			lock.l_type = F_WRLCK;
				fcntl (fd, F_SETLKW, &lock);
	printf ("locked; hit Enter to unlock... ");
		getchar ();
	printf ("unlocking\n");
		lock.l_type = F_UNLCK;
			fcntl (fd, F_SETLKW, &lock);
				close (fd);
					return 0;
}
