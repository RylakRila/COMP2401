#include "stdio.h"

int fun(int x) {
	if (x > 5) { 
		x++;
		return(x);
	}
}


int main() {
	int x = 12;

	printf("fun(%d) = %d\n", x, fun(x));

	return 0;
}

