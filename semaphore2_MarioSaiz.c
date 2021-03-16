/*	Mario Saiz
	Project Semaphore 2
	OS: Professor Gallmeier
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

// create a shared semaphore - this must be global in this example.
sem_t mutex;

// thread function
void *thread_function(void *arg)
{
  // get this thread's id
  pid_t tid = gettid();

  // wait on the semaphore
  sem_wait(&mutex);
  printf("%d: enter critical section\n", tid);

  // critical section is here
  sleep(5); // do something for a while...

  printf("%d: exiting critical section\n", tid);
  sem_post(&mutex);
}

int main(int argc, char *argv[])
{
  // two threads...
  pthread_t t1, t2;

  // initialize the semaphore
  //      first argument is the semaphore variable
  //      second argument: 0 => semaphore is shared between threads
  //                     : 1 => semaphore is shared between processes
  //      third arguement: initial value
  // N.B. second argument = 0 requires that the semaphore be located
  //      somewhere in memory visible to all of the threads. that would
  //       be either a global variable or use dynamically allocated memory
  sem_init(&mutex, 0, 1);

  // create two threads with an arbitrary time delay between creation
  printf("main: creating thread 1\n");
  pthread_create(&t1, NULL, thread_function, NULL);
  sleep(2);
  printf("main: creating thread 2\n");
  pthread_create(&t2, NULL, thread_function, NULL);

  // wait for threads to finish
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  // clean up and exit
  sem_destroy(&mutex);
  return 0;
}
