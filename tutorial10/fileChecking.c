#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE   25
#define MAX_NAMES       100

void main(int argc, char *argv[]) {
    FILE  *fd;
    
    fd = fopen("names1.txt", "r");
    if (!fd) {
        printf("Error opening file\n");
        exit(-1);
    }

    char names[MAX_NAMES][MAX_NAME_SIZE];
    int numNames = 0;
    while(1) {
        names[numNames][0] = '\0';
        fscanf(fd, "%[^\r\n]s", names[numNames]);
        char c = fgetc(fd); // read in the CR or LF character
        // if it was a CR character, then also read in the LF character
        if (c == '\r') fgetc(fd);

        if (strlen(names[numNames]) == 0) break;
 
        printf("(%lu) %s\n", strlen(names[numNames]), names[numNames]);
        numNames++;
    }
    printf("%d\n", numNames);

    fclose(fd);
}


