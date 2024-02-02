#include <stdio.h>
#include <string.h>

int main() {
	char *names[] = {"Charlie", "Ernie", "Hans", "Betty", "Le", "Muhammad", "Romeo", "Zachary",
	                 "Lola", "Melvin", "Connie", "Yandu", "Mephibosheth", "Wade", "Abby", "Duong", 
	                 "Henry", "Theresa", "Kyle", "Fiona", "Qi", "Gertrude", "Zihao", "Isabelle", 
	                 "Vera", "Jackie", "Le", "Uriyah", "Noah", "Patty", "Sanju", "Xavier", "Yusuf",
	                 "Elmo", "Rolf", "Omar"};
	unsigned char numNames = sizeof(names)/sizeof(char *);
    int max = 0;
    for (int i = 0; i < numNames; i++) {
        if (strlen(names[i]) > max)
            max = strlen(names[i]);
    }

    printf("%d\n", max);

	// Sort the names by repeatedly finding the smallest name and 
	// moving it to the front of the unsorted portion of the list
	for (int i=0; i < numNames - 1; i++) {
        unsigned char smallestIndex = i;
        for (int j = i + 1; j < numNames; j++) {
            if (j < numNames && strcmp(names[j], names[smallestIndex]) < 0)
                smallestIndex = j;
        }
        char* temp;
        if (smallestIndex != i) {
            temp = names[i];
            names[i] = names[smallestIndex];
            names[smallestIndex] = temp;
        }
	}

	// Display the sorted list
	for (int i=0; i<numNames; i++) 
		printf("%s\n", names[i]);
}

