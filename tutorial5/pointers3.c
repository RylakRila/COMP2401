#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Definition of a Classmate
typedef struct Person {
	char           *name;
	unsigned int    age;
	float           height;
	struct Person  *friend;
} Classmate;



// Display a Classmate, showing their height, age, name and friend's name
void printClassmate(Classmate *p) {
	printf("%2.1f-foot %2d-year old %s paired-up with %s\n", p->height, p->age, p->name, p->friend->name);
}

// Return 1 if the two class mates can be paired-up as friends and 0 otherwise
int canBePairedUp(Classmate *p1, Classmate *p2) {
	return ((p1->friend == NULL) && (p2->friend == NULL)) && (p1 != p2);
}


// This is where the program begins
int main() {
	srand(1); // Make sure we have reasonably-random values
	
	unsigned char numPeople = 16;
  
	Classmate people[numPeople];
  
	char       *names[] = {"Charlie", "Betty", "Le", "Muhammad", "Zachary", "Lola", "Connie", "Yandu", 
	                       "Mephibosheth", "Abby", "Duong", "Qi", "Zihao", "Uriyah", "Sanju", "Yusuf"};
	unsigned int ages[] = {12, 14, 8, 6, 15, 17, 6, 9, 12, 13, 13, 16, 15, 15, 15, 17};
	float     heights[] = {4.3, 4.5, 3.8, 3.2, 4.6, 4.7, 3.3, 3.9, 4.5, 4.2, 4.5, 5.9, 5.4, 5.2, 5.3, 5.8};


	// Initialize all classmates
	for (int i=0; i<numPeople; i++) {
		people[i].name = names[i];
		people[i].age = ages[i];
		people[i].height = heights[i];
        people[i].friend = NULL;
	}
	
	// Pair up all Classmates by finding them a random friend
	for (int i=0; i<numPeople; i++) {
        if (people[i].friend != NULL) continue;
		while(1) {
			unsigned char friendIndex = rand()%numPeople;
			
			if (canBePairedUp(&people[i], &people[friendIndex])) {
				people[i].friend = &people[friendIndex];
                people[friendIndex].friend = &people[i];
				break;
			}
		}
	}
	
	// Display all classmates
	for (int i=0; i<numPeople; i++)
		printClassmate(&people[i]);
}

