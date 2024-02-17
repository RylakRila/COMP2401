#include <stdio.h>
#include <stdlib.h>

struct Person {
	char         *name;
	unsigned int  age;
	float	        height;
};
typedef struct Person   Classmate;

// Dynamically-allocate a Person struct. Return 0 if all went ok and -1 otherwise.
// Return the person through the p paramater
int createPerson(Classmate** p) {
		*p = malloc(sizeof(struct Person));
		if (p == NULL)
			return(-1);
		return 0;
}


// A function to display a person, showing their height, age and name
void printPerson(Classmate* p) {
	printf("%2.1f-foot %2d-year old %s\n", p->height, p->age, p->name);
}

void printPeople(Classmate** p, int count) {
    for (int i = 0; i < count; i++)
        printf("%2.1f-foot %2d-year old %s\n", p[i]->height, p[i]->age, p[i]->name);
}


// This is where it all starts
int main() {
	char*        names[] = {"Charlie", "Betty", "Le", "Muhammad", "Zachary", "Lola", "Connie", "Yandu", 
	                       "Mephibosheth", "Abby", "Duong", "Qi", "Zihao", "Uriyah", "Sanju", "Yusuf"};
	unsigned int ages[] = {12, 14, 8, 6, 15, 17, 6, 9, 12, 13, 13, 16, 15, 15, 15, 17};
	float     heights[] = {4.3, 4.5, 3.8, 3.2, 4.6, 4.7, 3.3, 3.9, 4.5, 4.2, 4.5, 5.9, 5.4, 5.2, 5.3, 5.8};

	// Count the people supplied in the fixed arrays above
	int peopleCount = sizeof(names)/sizeof(char *);
	
	// This will hold an array of people pointers
	Classmate* people[peopleCount]; 

	
	// Initialize the people according to the fixed data above
	int i;
	for (i=0; i<peopleCount; i++) {
		if (createPerson(&people[i])) break;
		people[i]->name = names[i];
		people[i]->age = ages[i];
		people[i]->height = heights[i];
	}
	
	// Check if there were errors creating the people and indicate if there was a problem
	if (i != peopleCount) 
		printf("WARNING: Out of Memory. Only %d people were created.\n", i);
	
	// Display the people
	// for (int i=0; i<peopleCount; i++) 
	//	printPerson(people[i]);
    
    printPeople(people, peopleCount);
	
	// Free the people
	for (int i=0; i<peopleCount; i++)
		free(people[i]);
}

