#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "person.h"


// Maximum number of co-workers allowed
#define MAX_COWORKERS 10	



int main(int argc, char *argv[]) {
  Person 	coworkers[MAX_COWORKERS];
	
  srand(time(NULL));
  
  // Add some co-workers to the array
  for (int i=0; i<MAX_COWORKERS; i++) {
    createSamplePerson(&coworkers[i]);
    
    // If a person with the name of this last-added person is already in the array
    // then over-write it next time by finding a person with a different name
    if (alreadyContains(coworkers, i, coworkers[i].first, coworkers[i].last))
    	i--;
  }
  

  // Print the list of co-workers
  processEveryone(coworkers, MAX_COWORKERS, print);
  // Increase everyone's salary
  processEveryone(coworkers, MAX_COWORKERS, increaseSalary);
  printf("\n");
  
  // Print the list of co-workers again
  processEveryone(coworkers, MAX_COWORKERS, print);
  // Sort by decreasing order of salaries
  qsort(coworkers, MAX_COWORKERS, sizeof(Person), compareSalaries);
  printf("\n");

  // Print the list of co-workers again
  processEveryone(coworkers, MAX_COWORKERS, print);
}
