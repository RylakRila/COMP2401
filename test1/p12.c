#include <stdio.h>

unsigned char byteWith2BitPattern(unsigned char pattern) {

    unsigned char result = pattern;
    
    unsigned char temp;
    
    temp = result << 2; // shift left by 2 then
    result = result | temp; // filled with pattern 
    
    temp = result << 4; // shift left by 4 since we have double the pattern 
    result = result | temp; // then filled with doubled pattern

    return result;

}

int main() {
    printf("%d\n", byteWith2BitPattern(0b00)); // displays 00000000

    printf("%d\n", byteWith2BitPattern(0b01)); // displays 01010101

    printf("%d\n", byteWith2BitPattern(0b10)); // displays 10101010

    printf("%d\n", byteWith2BitPattern(0b11)); // displays 11111111
}

