/*	Mario Saiz
	Project Semaphore
	OS: Professor Gallmeier
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>  // needed as per the man page for sem_open
#include <fcntl.h>     // needed for O_CREAT
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

#define SEM_NAME "Class_Named_Sem"

void *thread_function(void *arg)
{
  sem_t *sem = (sem_t*)arg;
  pid_t tid = gettid();

  // wait on the semaphore
  sem_wait(sem);

  printf("thread %d: in critical section\n", tid);

  sleep(5); // do something that takes a while

  printf("thread %d: exiting critical section\n", tid);
  sem_post(sem);

  pthread_exit(0);
}

int main(int argc, char *argv[])
{
  pthread_t t1, t2;  // we will use two threads.
  sem_t *sem = NULL; // pointer to a semaphore assigned the NULL pointer

  if(argc == 2)
  {
      printf("unlink flag used... ");
      if( 0 == strcasecmp(argv[1], "unlink") )
      {
        printf("unlinking semaphore %s\n", SEM_NAME);
        sem_unlink(SEM_NAME);
        exit(0);
      }
      printf("incorrect flag: %s\n", argv[1]);
      exit(1);
  }

  printf("creating semaphore %s\n", SEM_NAME);
  // create the named semaphore and initialize the value to 1
  sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
  if(SEM_FAILED == sem)
  {
    perror("sem_open failed");
    exit(1);
  }

  // To demonstrate that the named semaphore does not need to be in
  // in global memory, we create a pointer, initialize the semaphore,
  // and then we pass the semaphore to the threads. You could have
  // just as easily move the sem_t *sem; line above main to create
  // a global pointer instead.
  pthread_create(&t1, NULL, thread_function, (void*)sem);
  sleep(2);
  pthread_create(&t2, NULL, thread_function, (void*)sem);

  // wait for threads to finish
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("exiting...\n");

  return 0;
}
