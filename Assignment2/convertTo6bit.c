#include <stdio.h>
#include <string.h>

#include "usefulTools.h"

/*
* Yuntian Ye
* 101322932
*/

unsigned char monoCharSwitch(unsigned char *in);

int main(int argc, char *argv[]) {
    unsigned char stringIn[MAX_STRING_SIZE+1];
    unsigned char stringOut[MAX_STRING_SIZE+1];
    
    // Determine if debugging should be on or not
    unsigned char debug = isDebugMode(argc, argv);
	
    // Get the sentence from the user
    scanf("%[^\n]s", stringIn);
    unsigned char numBytesIn = strlen(stringIn);
    
    // INSERT YOUR CODE HERE
    // Make sure that you store the resulting string into stringOut
    
    for (int i = 0; i <= numBytesIn; i++) {
        unsigned char *in = &stringIn[i];
        unsigned char *out = &stringOut[i];
        
        if (*in >= 32 && *in <= 63) // various symbols
            *out = *in;
        else if (*in >= 65 && *in <= 73) // A - I
            *out = *in - 64;
        else if (*in >= 97 && *in <= 105) // a - i
            *out = *in - 96;
        else if (*in >= 74 && *in <= 90) // J - Z
            *out = *in - 63;
        else if (*in >= 106 && *in <= 122) // j - z
            *out = *in - 95;
        else
            // handle single character mapping & all other
            // characters maps to 31, by switch statement
            *out = monoCharSwitch(in);
    }
    
    // If debugging is on, display the converted string as 2 digit codes
    if (debug) {
        printf("%d bytes entered\n", numBytesIn);
        for (int i=0; i<=numBytesIn; i++)
            printf("%02d ", stringOut[i]);
        printf("\n");
    }
    
    // Output to the next program
    sendOutputString(numBytesIn, stringOut);
}

unsigned char monoCharSwitch(unsigned char *in) {
    switch(*in) {
        case 0:
            return 0;
            break;
        case 10:
            return 10;
            break;
        case 91:
            return 28;
            break;
        case 93:
            return 29;
            break;
        case 64:
            return 30;
            break;
        default:
            return 31;
            break;
    }
}
