#include <stdio.h>

void printAges(unsigned int *a, unsigned char size) {
	for (int i=0; i<size; i++) 
		printf("%d, ", a[i]);
	printf("\n");
}

int main() {
	unsigned int ages[] = {12, 14, 8, 6, 15, 17, 6, 9, 12, 13, 13, 16, 15, 15, 15, 17};
	unsigned char numAges = sizeof(ages)/sizeof(unsigned int);
	
	printAges(ages, numAges);
    printf("%p\n", &ages[0]);
    printf("%p\n", &ages[1]);
    printf("%p\n", &ages[2]);

}

