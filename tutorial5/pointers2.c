#include <stdio.h>


typedef struct Person {
	char           *name;
	unsigned int    age;
	float	        height;
    struct Person  *friend;
} Classmate;


void printPerson(Classmate *p) {
	printf("%2.1f-foot %2d-year old %s\n", p->height, p->age, p->name);
}


int main() {
	unsigned char numPeople = 16;

	Classmate people[numPeople];
  
	char       *names[] = {"Charlie", "Betty", "Le", "Muhammad", "Zachary", "Lola", "Connie", "Yandu", 
	                       "Mephibosheth", "Abby", "Duong", "Qi", "Zihao", "Uriyah", "Sanju", "Yusuf"};
	unsigned int ages[] = {12, 14, 8, 6, 15, 17, 6, 9, 12, 13, 13, 16, 15, 15, 15, 17};
	float     heights[] = {4.3, 4.5, 3.8, 3.2, 4.6, 4.7, 3.3, 3.9, 4.5, 4.2, 4.5, 5.9, 5.4, 5.2, 5.3, 5.8};

	for (int i=0; i<numPeople; i++) {
		people[i].name = names[i];
		people[i].age = ages[i];
		people[i].height = heights[i];
	}
    
	for (int i=0; i<numPeople; i++)
		printPerson(&people[i]);
}

