#include <stdio.h>
#include <string.h>

#include "usefulTools.h"

/*
* Yuntian Ye
* 101322932
*/

int main(int argc, char *argv[]) {
    unsigned char stringIn[MAX_STRING_SIZE];
    unsigned char stringOut[MAX_STRING_SIZE];
    
    // Determine if debugging should be on or not
    unsigned char debug = isDebugMode(argc, argv);
    
    // Get the sentence from the user
    unsigned char numBytesIn = getInputString(stringIn);
    
    unsigned char numBytesOut = 0;
    
    // INSERT YOUR CODE HERE
    // Make sure that you: 
    //    1. Store the result string into stringOut
    //    2. Set the numBytesOut value to the length of stringOut
    
    unsigned short buffer = 0; // To hold the concatenated bits
    int bitCount = 0; // To count the number of bits in the buffer
    
    // Concatenate the 8-bit values into the bitStream
    for (int i = 0; i < numBytesIn; ++i) {
        buffer <<= 8;
        buffer |= stringIn[i];
        bitCount += 8;
        
        // Check if we have enough bits (6 or more) to form a 6-bit chunk
        while (bitCount >= 6) {
            bitCount -= 6; // Decrease the bitCount by 6
            
            // Extract the 6-bit chunk and store it in stringOut
            // we have to mask it by 00111111 to take only the 6bits
            unsigned char chunk = (buffer >> bitCount) & 63;
            stringOut[numBytesOut++] = chunk;
        }
    }
    
    // cut off the redundant 6 bits 000000
    if (stringOut[numBytesOut - 1] == 0) {
        numBytesOut -= 1;
    }
    
    // If debugging is on, display the expanded string as sequences of 8-bit binary values
    if (debug) {
        printf("Input bytes = %d\n\n", numBytesIn);
        printf("Output bytes = %d\n\n", numBytesOut);
        printf("Expansion ratio = %1.1f%%\n\n", 100*(float)(numBytesOut/(float)numBytesIn));
        printf("Before expansion:\n");
        for (int i=0; i<numBytesIn; i++)
            printAs8BitBinary(stringIn[i]);
        printf("\n");
        
        printf("After expansion:\n");
        for (int i=0; i<numBytesOut; i++)
            printAs6BitBinary(stringOut[i]);
        printf("\n");
        
        printf("Here is the resulting string:\n");
    }
    
    // Output to the next program
    sendOutputString(numBytesOut, stringOut);
}