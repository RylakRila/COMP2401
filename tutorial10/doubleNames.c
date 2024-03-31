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
		people[numPeople].firstName[0] = '\0';
		people[numPeople].lastName[0] = '\0';
        
		fscanf(fd, "%s", people[numPeople].firstName);
        if (strlen(people[numPeople].firstName) == 0) break;
        if (people[numPeople].firstName[0] == ',') {
            fscanf(fd, "\n");
            continue;
        }

        c = fgetc(fd);
        char lastNameMissing = people[numPeople].firstName
            [strlen(people[numPeople].firstName) - 1] == ',';
        if (lastNameMissing) // Chop off comma at the end of first name
            people[numPeople].firstName[strlen(people[numPeople].firstName - 1)] = '\0';
        else {
            fscanf(fd, "%[^ ,\r\n]s", people[numPeople].lastName);
            c = fgetc(fd); // Read in space or comma or end-of-line char
        }

		if ((c == '\n') || (c == '\r')) {
            people[numPeople].age = 0;
            people[numPeople].gender = '?';
        } else {
            // Handle the merging of the middle initial with the first name
            if ((c == ' ') && !lastNameMissing) {
                strcat(people[numPeople].firstName, " ");
                strcat(people[numPeople].firstName, people[numPeople].lastName);
                fscanf(fd, "%[^,]s", people[numPeople].lastName);
                c = fgetc(fd); // Read in the comma character
            }
            
            // Now read the age
            people[numPeople].age = 0;
            char temp[5]; // temporary space to read in an age
            fscanf(fd, "%[^,\r\n]s", temp);
            people[numPeople].age = atoi(temp);

            c = fgetc(fd); // read the comma or (\r or \n) character
            if (c != ',') {
                if ((people[numPeople].age == 0) || (c == '\n') || (c == '\r')) {
                    people[numPeople].gender = '?';
                    numPeople++;
                    if (c == '\r') fgetc(fd); // read the '\n' if there
                    continue;
                }
            }

            // Now read the gender
            c = fgetc(fd); // read the space or end-of-line characters
            if ((c != '\n') && (c != '\r')) {
                c = fgetc(fd); // read the gender character
                people[numPeople].gender = c;
                // Read in the end-of-line characters(s)
                if ((c = fgetc(fd)) == '\r') fgetc(fd);
            } else {
                people[numPeople].gender = '?';
                if (c == '\r') fgetc(fd); // Read the '\n' if there
            }
        }
        

		printf("%s, %s (%d) - %c\n", 
               people[numPeople].lastName, 
               people[numPeople].firstName,
               people[numPeople].age,
               people[numPeople].gender);
		numPeople++;
	}
	printf("%d\n", numPeople);
	
	fclose(fd);
}


