#include <stdio.h>

// Set bit bitNumber to 0 in the data byte
unsigned char eraseBit(unsigned char data, int bitNumber) { 
    return (data & (255 - (1 << bitNumber)));
}

int main() {
    unsigned char value = 0b11110000;
    
    
    printf("original value with bit 0 erased = %d\n", eraseBit(value, 0));
    printf("original value with bit 1 erased = %d\n", eraseBit(value, 1));
    printf("original value with bit 2 erased = %d\n", eraseBit(value, 2));
    printf("original value with bit 3 erased = %d\n", eraseBit(value, 3));
    printf("original value with bit 4 erased = %d\n", eraseBit(value, 4));
    printf("original value with bit 5 erased = %d\n", eraseBit(value, 5));
    printf("original value with bit 6 erased = %d\n", eraseBit(value, 6));
    printf("original value with bit 7 erased = %d\n", eraseBit(value, 7));
}

