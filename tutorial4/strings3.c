#include <stdio.h>
#include <string.h>

int main() {
    char *lowerCase[] = {"Mephibosheth", "Abby", "Betty", "Charlie", "Duong", "Ernie", "Fiona", "Gertrude", 
                        "Hans", "Isabelle", "Jackie", "Kyle", "Le", "Muhammad", "Noah", "Omar", "Patty", "Qi", 
                        "Romeo", "Sanju", "Theresa", "Uriyah", "Vera", "Wade", "Xavier", "Yusuf", "Zachary"};

    int numNames = sizeof(lowerCase)/sizeof(char *);
    int max = 0;
    for (int i = 0; i < numNames; i++) {
        if (strlen(lowerCase[i]) > max)
            max = strlen(lowerCase[i]);
    }

    char upperCase[numNames][max + 1];

    for (int i=0; i<numNames; i++)
        strcpy(upperCase[i], lowerCase[i]);
    
    strncpy(upperCase[1], "Elizabeth-Ann", max);
    strncpy(upperCase[9], "Sarah-Alexandra", max);
    upperCase[1][max] = '\0';
    upperCase[9][max] = '\0';

    for (int i=0; i<numNames; i++) {
        for (int j=1; j<strlen(upperCase[i]); j++) {
            if ((upperCase[i][j] >= 'a') && (upperCase[i][j] <= 'z')) {
                upperCase[i][j] = upperCase[i][j] - 32; 
            }
        }
    }

    for (int i=0; i<numNames; i++)
        printf("%s\n", lowerCase[i]);
    
    for (int i=0; i<numNames; i++) 
        printf("%s\n", upperCase[i]);
}

