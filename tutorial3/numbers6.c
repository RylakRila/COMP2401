#include <stdio.h>

// Print out the given number as binary (e.g., 75 prints as 01001011)
void printAsBinary(unsigned short data) {
    unsigned char bits[8];

    for (int i = 0; i < 8; i++) {
        bits[i] = data % 16;
        data /= 16;
    }

    for (int i = 8; i > 0; i--) {
        printf("%d ", bits[i - 1]);
    }

    printf("\n");
}

int main() {
	printAsBinary(56712);
}

