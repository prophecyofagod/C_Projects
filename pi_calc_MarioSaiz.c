/*

    Monte carlo calculation of pi - single threaded case

    Consider a circle drawn inside a unit square (each side has length 1). The radius of the circle is 1/2.

    The area of the square is side * side = 1*1 = 1,
    The area of the circle is pi*r*r = pi * (1/2)*(1/2) = pi/4

    We can use random numbers to estimate the area of the square and the area of the circle. We can easily generate
    a large number of random points within the unit square. Then, for each point we can easily calculate if the 
    point falls within the circle. d = x*x + y*y.  If d <=1, d is inside the circle. 

    Given this set of points, the area of the circule is simply the ratio of (# circle pts)/(# square pts)
    and the number of square points is the total number of random points generated. 

    Since we carefully chose our geometry, this area should be pi/4. Equating the two, we get

    pi = 4 * (#circle pts)/(#total pts)

    The accuracy of pi will depend on the number of random points generated. We will ignore the properties
    of random distributions and whether or not the built-in random functions are good enough. 

	What values of N are needed to achieve a reasonable value of pi? Play around. The number is larger
	than what you might expect. You may need to run well over a million iterations!

	This problem represents a class of parallel programming problems that are called "embarrassingly parallel"
	https://en.wikipedia.org/wiki/Embarrassingly_parallel. We can easily create any number of parallel versions
	of the loop over n and combine the results at the end. Your task, if you choose to accept it, is to create
	a parallel version of this code using pThreads.  

    Extra credit assignment: create a multi-threaded version of this code with the following specification:
    1) Allow the user to specify the number of threads to run on the command line:
       ./pi_calc <N> <number of threads>
    2) Spawn the correct number of threads such that each thread performs an independent version of the
       counting portion of monte-carlo iteration, each using N iterations
    3) when each thread is complete, each thread will pass the count values back to the main program
    4) the main program adds up the total number of iterations and the total number of circule count values
    5) finally, the main program will calculate the pi estimate. 

    Note: you do not need to pass the value of N back to the main thread since that is known in advance. You 
    can calculate the total number of iterations with: total_counts = N * number of threads

    Use pThreads for the threading model and include your name in the file comments. 

    Email your submission by the end of day April 9th - the last class before presenations. 

    This extra credit project will have the same value as a linux programming assignment and will be added
    to your total grade.  


*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Usage(char *name)
{
	printf("%s <N>\n", name);
	printf(" - N is the total number of random numbers to use in the simulation\n");
	exit(1);
}


int main(int argc, char * argv[])
{
	int n, i; 
	double x_rnd, y_rnd, dist;
	long c_count = 0L;
	double pi = 0.0;


	// use: calc_pi <N> 
	if(argc < 2)
		Usage(argv[0]);

	n = atoi(argv[1]);
	printf("using %d random numbers\n", n);

	srand(time(NULL)); // initialize random number generator with current time

    /* this code will need to be run in each thread */
	for(i=0; i< n; i++)
	{
		x_rnd = (double)rand()/(double)RAND_MAX;
		y_rnd = (double)rand()/(double)RAND_MAX;
		dist = sqrtl(x_rnd*x_rnd + y_rnd*y_rnd);

		if(dist <= 1.0)
			c_count++;
	}

	/* you will need to obtain each threads c_count value and sum them here */

	// calculate the estimate of PI = 4.0 * (#points in circle)/total points
	pi = 4.0* (double)c_count/(double)n;

	printf("Monte Carlo pi: %lf\n", pi);

	return 0;
}