#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define		GROWTH_AMOUNT 	5;

struct Person {
	char         *name;
	unsigned int  age;
	float	        height;
};

typedef struct Person 	Classmate;

// Some sample people data
char       *Names[] = {"Charlie", "Betty", "Le", "Muhammad", "Zachary", "Lola", "Connie", "Yandu", 
	                     "Mephibosheth", "Abby", "Duong", "Qi", "Zihao", "Uriyah", "Sanju", "Yusuf"};
unsigned int Ages[] = {12, 14, 8, 6, 15, 17, 6, 9, 12, 13, 13, 16, 15, 15, 15, 17};
float     Heights[] = {4.3, 4.5, 3.8, 3.2, 4.6, 4.7, 3.3, 3.9, 4.5, 4.2, 4.5, 5.9, 5.4, 5.2, 5.3, 5.8};



// Dynamically-allocate a Person struct. Return 0 if all went ok and -1 otherwise.
// Return the person through the p paramater
int createPerson(Classmate **p, unsigned char setAge) {
	// Allocate space to store a person
	*p = malloc(sizeof(Classmate));
	if (p == NULL)
		return(-1);
	
	// Assign a random person from the above list
	int r = rand()%16;
	(*p)->name = Names[r];
	if (setAge) (*p)->age = Ages[r];
	(*p)->height = Heights[r];
	return 0;
}


// A function to display a person, showing their height, age and name
void printPeople(Classmate **p, int count) {
	for (int i=0; i<count; i++)
		printf("%2.1f-foot %2d-year old %s\n", p[i]->height, p[i]->age, p[i]->name);
}


// This is where it all starts
int main(int argc, char *argv[]) {
	int    peopleCapacity = GROWTH_AMOUNT; // Current array capacity
	int    peopleCount = 0;		// Current data in the array
    unsigned char   assignAges = 1;

    if ((argc < 2) || (argc > 3)) {
        printf("PROGRAM USAGE:  ./dynamic3 [arraySize] {-noages}\n");
        printf("-noages is optional\n");
        exit(-1);
    }

    if ((argc == 3) && (strcmp(argv[2], "-noages") != 0)) {
        printf("PROGRAM USAGE:  ./dynamic3 [arraySize]\n");
        printf("{-noages} invalid argument\n");
        exit(-1);        
    } else if ((argc == 3) && (strcmp(argv[2], "-noages") == 0)) {
        assignAges = 0;
    } 
	
	// if (strcmp(argv[2], "-noages") == 0)
    // 	assignAges = 0;
	// else {
    // 	printf("PROGRAM USAGE:  ./dynamic3 [arraySize] {-noages}\n");
    // 	printf("-noages is optional\n");
    // 	exit(-1); 
	// }
	
    if ((atoi(argv[1]) <= 0) || (atoi(argv[1]) > 100)) {
        printf("PROGRAM USAGE:  ./dynamic3 [arraySize]\n");
        printf("[arraySize] - must be between 1 and 100, inclusively\n");
        exit(-1);
    }

    peopleCount = atoi(argv[1]);

	// Create an array to hold 5 people to start
	Classmate  **people = malloc(sizeof(Classmate *) * peopleCapacity);
	if (people == NULL) {
		printf("ERROR: Out of Memory\n");
		exit(-1);
	}
	
	// Add peopleCount people to the array
	for (int i=0; i<peopleCount; i++) {
		// If there is not enough space, make a bigger array that can hold 5 more people
		if (i == peopleCapacity) {
			peopleCapacity += GROWTH_AMOUNT;
			people = realloc(people, sizeof(Classmate *) * peopleCapacity);
			if (people == NULL) {
				printf("ERROR: Out of Memory\n");
				exit(-2);
			}
		}
		if (createPerson(&people[i], assignAges)) {
			printf("ERROR: Out of Memory\n");
			exit(-3);
		}
	}
	
	// Display the people
	printPeople(people, peopleCount);
	
	// Free the people
	for (int i=0; i<peopleCount; i++)
		free(people[i]);
	free(people);
}

