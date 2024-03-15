#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "person.h"
#include "stats.h"


// The starting base salary for an employee
#define BASE_SALARY 20000


// Print the information of a person showing the name, age and maximum salary
void print(Person *p) {
	float 	maxSalary = 0;

	setlocale(LC_ALL, "");
	maximum(p->salary, NUM_SAMPLE_YEARS, &maxSalary);

	printf("Name: %s %s, Age: %hu, Max Salary: $%'8d\n",
          p->first, p->last, p->age, (int)maxSalary);
}


// Create a sample person with random information
void createSamplePerson(Person *p) {
	// Global ID counter to give unique ID to each person
	static unsigned int id = 100001;
	
	// Sample names
	char *first[5] = { "Jim",   "Han",    "Mary",  "Robin",   "Sam" };
	char *last[5]  = { "Class", "Deeman", "Goround", "Banks", "Pull" };

	// Choose a random name
	strncpy(p->last, last[rand() % 5], MAX_NAME_LENGTH);
	strncpy(p->first, first[rand() % 5], MAX_NAME_LENGTH);

	p->id = id++;
	p->age = (rand() % 45) + 21; // Between 21 and 65
	p->salary[0] = BASE_SALARY + (rand() & 10000);
	
	// Populate the salary information increasing up to $10,000 per year
	for (int i=1; i<NUM_SAMPLE_YEARS; i++)
		p->salary[i] = p->salary[i-1] + (rand() & 10000);
}


// Determine if the person with the given first and last name is already in the array. 
// Return 1 if it is already there and otherwise returns 0
char alreadyContains(Person people[], int numPeople, char *first, char*last) {
	for (int i=0; i<numPeople; i++) {
		if ((strcmp(people[i].first, first) == 0) && (strcmp(people[i].last, last) == 0))
			return 1;
	}
	return 0;
}

void processEveryone(Person people[], int numPeople, void (*pFun)(Person *p)) {
    for (int i=0; i<numPeople; i++)
        pFun(&people[i]);
} 

void increaseSalary(Person *p) {
    p->salary[NUM_SAMPLE_YEARS - 1] += 1000;
}

int compareSalaries(const void *param1, const void *param2) {
    Person *p1 = (Person *)param1;
    Person *p2 = (Person *)param2;

    if (p1->salary[NUM_SAMPLE_YEARS-1] < p2->salary[NUM_SAMPLE_YEARS-1]) return 1;
    if (p1->salary[NUM_SAMPLE_YEARS-1] > p2->salary[NUM_SAMPLE_YEARS-1]) return -1;
    return 0;
}
