#include <stdio.h>
#include <string.h>

#include "usefulTools.h"

/*
* Yuntian Ye
* 101322932
*/

unsigned char monoCharSwitch(unsigned char *in);

int main(int argc, char *argv[]) {
    unsigned char stringIn[MAX_STRING_SIZE];
    unsigned char stringOut[MAX_STRING_SIZE];
    
    // Determine if debugging should be on or not
    unsigned char debug = isDebugMode(argc, argv);
    
    // Get the sentence from the user
    unsigned char numBytesIn = getInputString(stringIn);
    
    
    // INSERT YOUR CODE HERE
    // Make sure that you store the resulting string into stringOut
    
    for (int i = 0; i <= numBytesIn; i++) {
        unsigned char *in = &stringIn[i];
        unsigned char *out = &stringOut[i];
        
        if (*in >= 32 && *in <= 63) {
            *out = *in;
        } else if (*in >= 1 && *in <= 9) {
            *out = *in + 64;
        } else if (*in >= 11 && *in <= 27) {
            *out = *in + 63;
        } else if (*in == 31) {
            *out = 95;
        } else {
            *out = monoCharSwitch(in);
        }
    }
    
    stringOut[numBytesIn] = 0;
    
    // If debugging is on, display the converted string as 2 digit codes
    if (debug) {
        for (int i=0; i<=numBytesIn; i++)
            printf("%02d ", stringOut[i]);
        printf("\n");
    }
    
    // Output the final string
    printf("%s\n",stringOut);
}

unsigned char monoCharSwitch(unsigned char *in) {
    switch(*in) {
        case 0:
            return 0;
        case 10:
            return 10;
        case 28:
            return 91;
        case 29:
            return 93;
        case 30:
            return 64;
    }
}