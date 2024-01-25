#include <stdio.h>

// Return 1 if bit bitNum is set in the given byte c and return 0 otherwise
int isBitSet(unsigned char data, int bitNumber) {
    return (data & (1 << bitNumber)) != 0;
}


int main() {
	unsigned char value = 0b11110000;

  printf("bit 0 = %d\n", isBitSet(value, 0));
  printf("bit 1 = %d\n", isBitSet(value, 1));
  printf("bit 2 = %d\n", isBitSet(value, 2));
  printf("bit 3 = %d\n", isBitSet(value, 3));
  printf("bit 4 = %d\n", isBitSet(value, 4));
  printf("bit 5 = %d\n", isBitSet(value, 5));
  printf("bit 6 = %d\n", isBitSet(value, 6));
  printf("bit 7 = %d\n", isBitSet(value, 7));
}

