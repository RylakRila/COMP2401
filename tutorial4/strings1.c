#include <stdio.h>

int isLetter(char c) {
    if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))
        return 1;
    return 0;
}

int main() {
	char a = 97;
	char b = 65;
	char c = 48;
	char d = 45;
	char e = 32;
	char f = 10;
	
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("c = %d\n", c);
	printf("d = %d\n", d);
	printf("e = %d\n", e);
	printf("f = %d\n", f);
	printf("\n");
	printf("a = %c\n", a);
	printf("b = %c\n", b);
	printf("c = %c\n", c);
	printf("d = %c\n", d);
	printf("e = %c\n", e);
	printf("f = %c\n", f);
	printf("done\n");

    if ((c >= 48) && (c <= 57))
        printf("c represents a digit\n");
    else
        printf("c does not represent a digit\n");

    if (isLetter(a)) printf("a is ok\n");
    if (isLetter(b)) printf("b is ok\n");
    if (isLetter(c)) printf("c is ok\n");
}
