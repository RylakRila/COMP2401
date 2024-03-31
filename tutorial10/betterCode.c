#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAX_NAME_SIZE    15
#define	MAX_NAMES        100

typedef struct per {
	char              firstName[MAX_NAME_SIZE];
	char              lastName[MAX_NAME_SIZE];
	unsigned short    age;
	char              gender;
} Person;

// Save the adjusted data to a binary file
void saveData(char *aFileName, Person people[], int numPeople) {
    FILE *fd;

    // Open a file with the given fileName for writing
    fd = fopen(aFileName, "w");
    if (!fd) {
        printf("Error opening binary file for writing\n");
        exit(-1);
    }

    // Write the numPeople to the file from the people array
    for (int i=0; i<numPeople; i++) {
        fputc(strlen(people[i].lastName), fd);
        fwrite(people[i].lastName, sizeof(char), strlen(people[i].lastName), fd);
        fputc(strlen(people[i].firstName), fd);
        fwrite(people[i].firstName, sizeof(char), strlen(people[i].firstName), fd);
        fwrite(&people[i].age, sizeof(unsigned short), 1, fd);
        fwrite(&people[i].gender, sizeof(char), 1, fd);
    }

    fclose(fd);
}

int main(int argc, char *argv[]) {

	FILE 	*fd;
	char	 c;

	fd = fopen("names5.txt", "r");
	if (!fd) {
		printf("Error opening file\n");
		exit(-1);
	}
	
	// Read all the people from the file
	Person people[MAX_NAMES];
	int numPeople = 0;
	
	while(1) {
		// Set the default values for attributes that may be missing in the file
	  people[numPeople].firstName[0] = '\0';
	  people[numPeople].lastName[0] = '\0';
	  people[numPeople].age = 0;
	  people[numPeople].gender = '?';

		// Read in the first name
		fscanf(fd, "%s", people[numPeople].firstName);
		
		// Handle case where the firstName was empty (i.e., End-Of-File was reached)
		if (strlen(people[numPeople].firstName) == 0)
				break;

		// Check case where the first name was missing ... ignore the person altogether
		if (people[numPeople].firstName[0] == ',') {
			fscanf(fd, "\n");
			continue; 
		}
		c = fgetc(fd); // Read in the space character after the first name
		
		// If there is a comma at the end of the first name, then the last name is missing
		char lastNameMissing = people[numPeople].firstName[
                       strlen(people[numPeople].firstName)-1] == ',';
		
		// If the last name was missing, erase the comma in the first name, 
		// otherwise read in the last name
		if (lastNameMissing)
			people[numPeople].firstName[strlen(people[numPeople].firstName)-1] = '\0';
		else {
			fscanf(fd, "%[^ ,\r\n]s", people[numPeople].lastName);
			c = fgetc(fd); // Read in the space or comma or end-of-line character
		}

		// If the line ended after the name was read in, allow the default 
		// age and gender values then go to the next person in the file
		if ((c == '\n') || (c == '\r')) {
			numPeople++;
			continue;
		}
		
		// It is possible that the lastName was actuially a middle initial.
		// If the separator character was a comma, then this is the situation
		if ((c == ' ') && !lastNameMissing) {
			// Join the middle initial (read in as lastName) to the firstName
			strcat(people[numPeople].firstName, " ");
			strcat(people[numPeople].firstName, people[numPeople].lastName);
			fscanf(fd, "%[^ ,]s", people[numPeople].lastName);
			c = fgetc(fd); // Read in the comma character
		}
			
		// Now read the age
		people[numPeople].age = 0;
		char temp[5]; // temporary space to read in an age
		fscanf(fd, "%[^,\r\n]s", temp);	
		people[numPeople].age = atoi(temp);

		c = fgetc(fd); // read the , (or \r or \n) character
		if (c != ',') {
			// If the age was not there (i.e., 0) or the line ended abrubtly,
			// then move onto the next person in the list
			if ((people[numPeople].age == 0) || (c == '\n') || (c == '\r')) {
				numPeople++;
				if (c == '\r') fgetc(fd); // read the '\n' if there
				continue;
			}
		}

		// Now read the gender
		c = fgetc(fd); // read the space or end-of-line characters
		
		// If there was a gender (i.e., the line did not end abruptly), 
		// then set it 
		if ((c != '\n') && (c != '\r')) {
			c = fgetc(fd); // read the gender character
			people[numPeople].gender = c;
			// Read in the end-of-line character(s)
			if ((c = fgetc(fd)) == '\r') fgetc(fd);
		}
		else
			if (c == '\r') fgetc(fd); // read the '\n' if there
	
		// The person has been read in  from the file, so increase the count
		numPeople++;
	}
	
	// Close the file
	fclose(fd);
	
	// Display the data that was read in from the file
	printf("%d people were read in from the file as follows:\n", numPeople);
	for (int i=0; i<numPeople; i++) {
		printf("%2d %s, %s (",i+1, people[i].lastName, people[i].firstName);
		if (people[i].age == 0)
			printf("?");
		else 
			printf("%d", people[i].age);
		printf(") - %c\n", people[i].gender);
	}
    saveData("binaryNames.bin", people, numPeople);
}


