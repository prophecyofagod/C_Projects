/*	Mario Saiz
	Project Mutex
	OS: Professor Gallmeier
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

pthread_mutex_t lock;
int counter;

void * thread_function(void *arg)
{
  pid_t tid = gettid();

  pthread_mutex_lock(&lock);
  printf("thread %d: in critical section\n");

  // critical section
  counter = counter + 1;
  sleep(2);
  printf("thread %d done: counter value = %d\n", tid, counter);

  pthread_mutex_unlock(&lock);

  pthread_exit(10);
}

int main(int argc, char *argv[])
{
  pthread_t t1, t2;
  int error;
  void * retval;

  // initialize pthread_mutex
  pthread_mutex_init(&lock, NULL);

  error = pthread_create(&t1, NULL, thread_function, NULL);
  if(error != 0)
  {
    printf("thread creation error\n");
    exit(0);
  }

  error = pthread_create(&t2, NULL, thread_function, NULL);
  if(error != 0)
  {
    printf("thread creation error\n");
    exit(0);
  }

  pthread_join(t1, &retval);
  printf("main - thread 1 returned value %d\n", (int)retval);
  pthread_join(t2, NULL);

  pthread_mutex_destroy(&lock);

  return 0;
}
