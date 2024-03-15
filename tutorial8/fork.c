#include <stdio.h>
#include <unistd.h>

int main() {
	int childPID = fork();
  
	if (childPID == 0) {
		// This is the child
		while (1) {
			printf("  C\n");
			sleep(1);
		}
	}
	else { 
		// This is the parent
		while (1) {
			printf("P\n");
			sleep(1);
		}
	}
}
