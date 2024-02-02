#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define     LIST_MAX    25

int main() {
	char *names[][LIST_MAX] = {{"Charlie", "Ernie", "Hans", "Le", "Muhammad", "Romeo", "Zachary"},
	                   {"Mephibosheth", "Abby", "Betty", "Duong", "Fiona", "Gertrude", "Isabelle", 
	                    "Jackie", "Kyle", "Le", "Noah", "Omar", "Patty", "Qi", "Sanju", "Theresa", 
	                    "Uriyah", "Vera", "Wade", "Xavier", "Yusuf"},
	                   {"Connie", "Elmo", "Rolf", "Henry", "Lola", "Melvin", "Zihao", "Yandu"}};
    unsigned char listSizes[] = {7, 21, 8};

    unsigned char numLists = sizeof(names) / sizeof(names[0]);
    for (int i = 0; i < numLists; i++) {
        for (int n = 0; n < listSizes[i]; n++)
            printf("%s\n", names[i][n]);
    }
}

