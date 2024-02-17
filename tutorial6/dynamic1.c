#include <stdio.h>
#include <stdlib.h>

struct Person {
	char         *name;
	unsigned int  age;
	float	      height;
};

// An array of people
struct Person **people;
int           peopleCount;


// A function to display a person, showing their height, age and name
void printPerson(struct Person *p) {
	printf("%2.1f-foot %2d-year old %s\n", p->height, p->age, p->name);
}

// This is where it all starts
int main() {
	char       *names[] = {"Charlie", "Betty", "Le", "Muhammad", "Zachary", "Lola", "Connie", "Yandu", 
	                       "Mephibosheth", "Abby", "Duong", "Qi", "Zihao", "Uriyah", "Sanju", "Yusuf"};
	unsigned int ages[] = {12, 14, 8, 6, 15, 17, 6, 9, 12, 13, 13, 16, 15, 15, 15, 17};
	float     heights[] = {4.3, 4.5, 3.8, 3.2, 4.6, 4.7, 3.3, 3.9, 4.5, 4.2, 4.5, 5.9, 5.4, 5.2, 5.3, 5.8};

	people = malloc(sizeof(struct Person *) * sizeof(names)/sizeof(char *));
    if (people == NULL) {
        printf("ERROR: Out of Memory when allocating people array\n");
        exit(-1);
    }
	// Initialize a few people
	for (int i=0; i<sizeof(names)/sizeof(char *); i++) {
        people[i] = malloc(sizeof(struct Person));
        if (people == NULL) {
            printf("ERROR: Out of Memory when allocating person %d\n", i);
            exit(-2);
        }
		people[i]->name = names[i];
		people[i]->age = ages[i];
		people[i]->height = heights[i];
		peopleCount++;
		printPerson(people[i]);
	}
 
    for(int i = 0; i < sizeof(names)/sizeof(char *); i++)
        free(people[i]);
    free(people);
}

