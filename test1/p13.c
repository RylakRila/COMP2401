#include<stdio.h>

unsigned char keepCommonSetBits(unsigned char value1,
                                unsigned char value2) {
    unsigned char result = 0;
    
    result = value1 & value2;
    
    return result;
}

int main() {
    printf("%d\n", keepCommonSetBits(0b00011100, 0b00011100)); // 28

  printf("%d\n", keepCommonSetBits(0b11100011, 0b00011100)); // 0

  printf("%d\n", keepCommonSetBits(0b11111111, 0b10001000)); // 136

  printf("%d\n", keepCommonSetBits(0b10100101, 0b11111111)); // 165
}