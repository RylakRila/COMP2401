#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Main Program PID = %d\n", getpid());
	int childPID = fork();
  
	if (childPID == 0) {
		printf("Child PID = %d\n", getpid());
		// This is the child
		while (1) {
			printf("  C\n");
			sleep(1);
		}
	}
	else {
		fork();
		printf("Parent PID = %d\n", getpid());
		// This is the parent
		while (1) {
			printf("P\n");
			sleep(1);
		}
	}
}
