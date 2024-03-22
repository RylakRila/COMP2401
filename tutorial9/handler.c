#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <math.h>


// This function determines if the given number is prime. It also computes the number of 
float isPrime(unsigned long int n) {
	struct timeval 	startTime, endTime; 	// These keep track of the start and end times
	gettimeofday(&startTime, NULL);
  
	int max = (int)sqrt(n);
	for (int i=2; i<=max; i++) {
		if (n % i == 0)
			return 0;
	}
  
	gettimeofday(&endTime, NULL);
  
	// Return the time that has elapsed (in seconds)
	return (endTime.tv_sec + endTime.tv_usec/1000000.0) - 
	       (startTime.tv_sec + startTime.tv_usec/1000000.0);
}

unsigned int numbersChecked = 0; 	// count of all numbers that have been checked so far 
unsigned int primeNumbersFound = 0; // count of numbers that were determined to be prime
char paused = 0;

// Handle any incoming SIGUSR1 signal. Respond by toggling pause/resume mode.
void handlePauseResume(int i) {
	if (paused)
    	printf("RESUMING ...\n");
  	else
    	printf("PAUSED.\n");
	
	paused = 1 - paused; // toggle paused mode on/off
}

// Handle any incoming SIGUSR2 signal. Respond by displaying statistics.
void handleStatistics(int i) {
	printf("%d numbers have been checked, %d of them have been prime\n",    
			numbersChecked, primeNumbersFound);
}

int main() {
	signal(SIGUSR1, handlePauseResume);
	signal(SIGUSR2, handleStatistics);
	printf("\nPrime Calculator: Running (PID=%d)\n", getpid());
	// Starting number to check (i.e., 438303492847323243)
	unsigned long int 	number = (unsigned long int)553234941*(unsigned long int)792255623;
  
	// Go into an infinite loop check for prime numbers starting with number and increasing by 1 each time
	while (1) {
		if (!paused) {
			// Determine whether the number is prime, and get back the time it took to determine so
			float timeToComputePrime = isPrime(number);
			if (timeToComputePrime > 0) {
				printf("%ld is prime (%1.3f seconds)\n", number, timeToComputePrime);
				primeNumbersFound++;
			}
		
			numbersChecked++;	// increase the numbers checked counter
			number++;		// Check the next number
		}
	}
}
