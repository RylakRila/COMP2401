#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
	// Starting number to check (i.e., 438303492847323243)
	unsigned long int 	number = (unsigned long int)553234941*(unsigned long int)792255623;
	char  commandString[80];
	
	// Check for 50 prime numbers starting with number and increasing by 1 each time
	for (int i=0; i<50; i++) {
		sprintf(commandString, "./build/client %lu\n", number);
		system(commandString);	
		number++; 
	}
	system("./build/client stats");
}