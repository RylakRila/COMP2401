#include <stdio.h>
#include <string.h>

#define LIST_MAX	25

// Returns 1 if the given list of names is sorted alphabetically and 0 otherwise
int isSorted(char *names[], unsigned char listSize) {
	for (int n=1; n<listSize; n++) {
        if (strcmp(names[n], names[n - 1]) < 0)
            return 0;
	}
	return 1;
}


int main() {
	char *names[][LIST_MAX] = {{"Charlie", "Ernie", "Hans", "Le", "Muhammad", "Romeo", "Zachary"},
	                   {"Mephibosheth", "Abby", "Betty", "Duong", "Fiona", "Gertrude", "Isabelle", 
	                    "Jackie", "Kyle", "Le", "Noah", "Omar", "Patty", "Qi", "Sanju", "Theresa", 
	                    "Uriyah", "Vera", "Wade", "Xavier", "Yusuf"},
	                   {"Connie", "Elmo", "Rolf", "Henry", "Lola", "Melvin", "Zihao", "Yandu"}};
	unsigned char listSizes[] = {7, 21, 8};
	
	unsigned char numLists = sizeof(names)/sizeof(names[0]);
	for (int i=0; i<numLists; i++) {
		if (isSorted(names[i], listSizes[i]))
			printf("List %d is sorted\n",i);
		else
			printf("List %d is NOT sorted\n",i);
	}
}

