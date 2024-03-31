#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define 	MAX_NAME_SIZE		15


typedef struct per {
	char			firstName[MAX_NAME_SIZE];
	char			lastName[MAX_NAME_SIZE];
	unsigned short	age;
	char			gender;
} Person;


int main(int argc, char *argv[]) {
	FILE 	*fd;

	fd = fopen("binaryNames.bin", "r+");
	if (!fd) {
		printf("Error opening binaryfile for reading\n");
		exit(-1);
	}
	
	// Read all the people from the file
	Person aPerson;
	int		 numPeople = 0;
	
    unsigned char length = 0;
	while(1) {
        length = fgetc(fd);
        if (feof(fd)) break;
        fread(aPerson.lastName, sizeof(char), length, fd);
        aPerson.lastName[length] = '\0';
        length = fgetc(fd);
		fread(aPerson.firstName, sizeof(char), length, fd);
        aPerson.firstName[length] = '\0';
    
		fread(&aPerson.age, sizeof(unsigned short), 1, fd);
        (aPerson.age)++;
        fseek(fd, -2, SEEK_CUR);
        fwrite(&aPerson.age, sizeof(unsigned short), 1, fd);
		fread(&aPerson.gender, sizeof(char), 1, fd);
		
		printf("(%d) - %s %s, %d (%c)\n", ++numPeople, aPerson.lastName,
					 aPerson.firstName, aPerson.age, aPerson.gender);
	}
	
	
	fclose(fd);
}
