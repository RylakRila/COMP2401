#include <stdio.h>
#include <math.h>

#define	MAX_STRING_SIZE  255


// Print an unsigned char as 6 binary digits
void printAs6BitBinary(unsigned char n) {
  for (int i=5; i>=0; i--) {
    if ((int)(n/pow(2,i)) > 0) {
      printf("1");
      n = n - pow(2,i);
    }
    else
      printf("0");
  }
  printf("\n");
}

// Print an unsigned char as 8 binary digits
void printAs8BitBinary(unsigned char n) {
  for (int i=7; i>=0; i--) {
    if ((int)(n/pow(2,i)) > 0) {
      printf("1");
      n = n - pow(2,i);
    }
    else
      printf("0");
  }
  printf("\n");
}


// Get up to 255 characters as input from the user (or piped in from another program).
// The first character is the number of characters to be read in
unsigned char getInputString(unsigned char *stringIn) {
	unsigned char numChars = getc(stdin);
	unsigned char c = '?';
	unsigned int  count = 0;
	while ((c != '\n') && (count<MAX_STRING_SIZE)) {
		c = getc(stdin);
		stringIn[count++] = c;
	}
	return numChars;
}

// Print out (or pipe out to another program) the converted string
void sendOutputString(unsigned char size, unsigned char *stringOut) {
	printf("%c", size);
	for (int i=0; i<size; i++)
		printf("%c", stringOut[i]);
	printf("%c", 0);
}

// Return true if the program was run with the debug option on (i.e., -d) and false otherwise
unsigned char isDebugMode(int argc, char *argv[]) {
	if (argc != 2)
		return 0;
	if ((argv[1][0] == '-') && (argv[1][1] == 'd'))
		return 1;
	return 0;
}


