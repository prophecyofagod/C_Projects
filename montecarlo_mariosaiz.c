/*	Mario Saiz
	Extra Credit: Monte Carlo
	OS: Professor Gallmeier
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

void* Function(void* i);

#define MAX_THREADS 200
unsigned long long total[MAX_THREADS] = {0};    
	unsigned long long in[MAX_THREADS] = {0};       
		double tolerance, change, new, old = 0.0;
			long thread_num;
				pthread_mutex_t         mutex = PTHREAD_MUTEX_INITIALIZER;



int main(int argc, char **argv){
	long i;
    	struct timeval start, end;
    		double secs;
    			unsigned long long master_total;
    				pthread_t* threads;
    if (argc != 3){
        printf("\nMust pass 2 arguments:  (Tolerance) (# of Threads)");
        	exit(-1);
    }
    thread_num = atoi ( argv[1]);
    	tolerance = atof ( argv[2]);
    if (( thread_num < 1) || ( tolerance < 0.0) || (thread_num > 200)) {
        printf("\nIncorrect tolerance or threads.");
        	exit (-1);
    }
    threads = malloc(thread_num*sizeof(pthread_t)); 
    	tolerance = tolerance * tolerance;
    		change = 0.5;
    			srand48(clock());
    				gettimeofday (&start, NULL);
    for( i = 0; i < thread_num; i++ ){
        pthread_create(&threads[i], NULL, Function, (void*)i);
    }
    for( i = 0; i < thread_num; i++ ){
        pthread_join(threads[i], NULL);
    }
    gettimeofday (&end, NULL);
    	master_total = 0;
    for( i = 0; i < thread_num; i++ ){
        master_total = master_total + total[i];
    }
    secs = (( double)end.tv_sec - (double)start.tv_sec )
    	+ (( double)end.tv_usec - (double)start.tv_usec )/1000000.0;
    		printf ( "Estimation of pi is %.12f in %llu iterations , %.6f seconds.\n", new, master_total, secs );
}
void* Function(void* i){

    long my_spot = (long) i;
    	long rc;
    		long j;
    			unsigned long long my_total;
    				unsigned long long my_in;
    do
    {
        double x, y;
        	x = drand48();
        		y = drand48();
        			total[my_spot]++;
        if (( x*x + y*y) <= 1.00){
            in[my_spot]++;
        }
        if(total[my_spot] % 1000 == 0){
            while ( j < thread_num){
                my_total = my_total + total[j];
                	my_in = my_in + in[j];
            }
            my_total = my_total;
        		rc = pthread_mutex_lock(&mutex);
        			new = 4.0 * (double)my_in/( double)my_total;
        				change = fabs (new - old);
        					old = new;
        						rc = pthread_mutex_unlock(&mutex);
        }
    }while (change > tolerance );
    	return NULL;
}
