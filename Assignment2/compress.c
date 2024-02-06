#include <stdio.h>
#include <string.h>

#include "usefulTools.h"


int main(int argc, char *argv[]) {
    unsigned char stringIn[MAX_STRING_SIZE+1];
    unsigned char stringOut[MAX_STRING_SIZE+1];
    
    // Determine if debugging should be on or not
    unsigned char debug = isDebugMode(argc, argv);
	
    // Get the sentence from the user
    unsigned char numBytesIn = getInputString(stringIn);
    
    // Convert to new ASCII values
    unsigned char numBytesOut = 0;
    
    // INSERT YOUR CODE HERE
    // Make sure that you: 
    //    1. Store the result string into stringOut
    //    2. Set the numBytesOut value to the number of bytes you wrote to stringOut
    unsigned short buffer = 0; // Buffer to hold the bits
    int numBufferBits = 0; // Counter for the number of useful bits in buffer
    
    for (int i = 0; i < numBytesIn; ++i) {
        // Shift the buffer to the left by 6 to make room for the new value
        buffer <<= 6;
        // Set the empty room we make to current 6 bits
        buffer |= stringIn[i];
        // Increment the bufferBits by 6
        numBufferBits += 6;
        
        // If there are at least 8 bits in the buffer, write them out to stringOut
        while (numBufferBits >= 8) {
            // since we write 8 bits to stringOut
            // each time. Decrease bufferBits by 8
            // because these 8 bits no longer useful
            numBufferBits -= 8;
            
            // shift the buffer by number of useful bits and put them in stringOut
            // this shifting is to make sure we include the original bits
            stringOut[numBytesOut] = (buffer >> numBufferBits);
            // if there are more than 8 useful bits in current buffer, and
            // we want to include these useful bits, we have to temporarily
            // shift the buffer right by the # beyond 8bits. That is, shift 
            // left by (# current bits) - (# bits to write in output "8")
            // = # beyond 8bits. Therefore we shift buffer right by numBufferBits
            // before write in output, since we've already subtracted it by 8
            
            numBytesOut += 1; // increment # byte in output by 1
        }
    }
    
    // If there are remaining bits in the buffer after processing all input, 
    // shift them left to form a full 8bits and write out
    if (numBufferBits > 0) {
        // numBufferBits means the # useful bits leftover in the buffer
        // if we want to make them to form a full 8 bit string, we have to shift
        // them left by the difference between (# bits) and 8
        stringOut[numBytesOut] = (buffer << (8 - numBufferBits));
        numBytesOut += 1;
    }
    
    // If debugging is on, display the compression ratio as well as the
    // compressed string as sequences of 8-bit binary values
    if (debug) {
        printf("Compression ratio = %1.1f%%\n\n", 100*(float)(numBytesOut/(float)numBytesIn));
        printf("Before compression:\n");
        for (int i=0; i<numBytesIn; i++)
          printAs6BitBinary(stringIn[i]);
        printf("\n");
        
        printf("After compression:\n");
        for (int i=0; i<numBytesOut; i++)
          printAs8BitBinary(stringOut[i]);
        printf("\n");
            
        printf("Here is the resulting string:\n");
    }
    
    // Output to the next program
    sendOutputString(numBytesOut, stringOut);

}
