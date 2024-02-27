#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "phoneNetwork.h"

// char registerCustomer(PhoneNetworkType *phoneNetwork, char *name, 
//                       char *phoneNum, int minAllowed);

// void displayCharges(PhoneNetworkType *phoneNetwork);

// void resetMonth(PhoneNetworkType *phoneNetwork);

// char recordCall(PhoneNetworkType* phoneNetwork, char *callerNum, 
// 				char *receiverNum, time_t startTime, time_t endTime);

// void displayCallLog(PhoneNetworkType *PhoneNetwork);

// This the sample data for 20 customers to be used for testing
char *SampleNames[] = {"Rob Banks", "April Rain", "Rita Book", "Sue Permann", "Tim Bur", 
                       "Paddy O'Lantern", "Sam Pull", "Sandy Beach", "Adam Bomm", "Hugo First", 
                       "Dan Druff", "Mabel Syrup", "Mike Rohsopht", "Adam Sapple", "Moe Skeeto", 
                       "Anita Bath", "Rusty Chain", "Stu Pitt", "Val Crow", "Neil Down"};

char *SampleNumbers[] = {"(613)111-1111", "(819)222-2222", "(613)333-3333", "(343)444-4444", 
                         "(819)555-5555", "(613)666-6666", "(343)777-7777", "(613)888-8888", 
                         "(819)999-9999", "(613)555-1234", "(613)555-5678", "(613)666-1234", 
                         "(613)666-5678", "(343)777-1234", "(613)777-5678", "(819)888-1234", 
                         "(343)888-5678", "(613)999-1234", "(613)999-5678", "(613)444-1234"};
                         
unsigned short int SamplePlans[] = 
					{UNLIMITED, 200, PAY_PER_MINUTE, UNLIMITED, PAY_PER_MINUTE, UNLIMITED,
                    200, UNLIMITED, UNLIMITED, UNLIMITED, 200, UNLIMITED, UNLIMITED, 
                    100, 200, UNLIMITED, PAY_PER_MINUTE, 200, UNLIMITED, UNLIMITED};


// This is where the fun begins
int main() {
	PhoneNetworkType	phoneNetwork;
	
	srand(time(NULL));
	
	int numSamples = sizeof(SampleNames) / sizeof(char *);
	
	// Register some customers according to the sample arrays above
	// ...
	phoneNetwork.numCustomers = 0;
	for (int i = 0; i < numSamples; i++) {
		registerCustomer(&phoneNetwork, SampleNames[i], SampleNumbers[i], SamplePlans[i]);
	}
	
	// Reset the phoneNetwork calls for a new month
	// ...
	resetMonth(&phoneNetwork);
	
	// Simulate 100 calls being made randomly between customers.
	// ...
	for (int i = 0; i < 100; i++) {
		CustomerType *caller;
		CustomerType *callee;
		// generate random caller and callee, ensuring they are different
		do {
			caller = &phoneNetwork.customers[rand() % phoneNetwork.numCustomers];
			callee = &phoneNetwork.customers[rand() % phoneNetwork.numCustomers];
		} while(strcmp(caller->number, callee->number) == 0);
		
		struct tm startTime; startTime.tm_year = 2024 - 1900; startTime.tm_mon = 1; 
		struct tm endTime; endTime.tm_year = 2024 - 1900; endTime.tm_mon = 1;
		// generate random start and end times, ensuring 
		// start time is before end time
		// and the duration is at most 2 hours
		do {
			startTime.tm_mday = rand() % 29 + 1;
			startTime.tm_hour = rand() % 24;
			startTime.tm_min = rand() % 60;
			startTime.tm_sec = rand() % 60;
			
			endTime.tm_mday = rand() % 29 + 1;
			endTime.tm_hour = rand() % 24;
			endTime.tm_min = rand() % 60;
			endTime.tm_sec = rand() % 60;
		} while (mktime(&startTime) >= mktime(&endTime) || (mktime(&endTime) - mktime(&startTime) > SEC_2H));
		
		// record the call
		recordCall(&phoneNetwork, caller->number, callee->number, mktime(&startTime), mktime(&endTime));
	}
	
	// Go through the recorded calls and display them
	// ...
	displayCallLog(&phoneNetwork);
	
	printf("\n\n");
	
	// Display the monthly charges for all customers
	// ...
	displayCharges(&phoneNetwork);
}
