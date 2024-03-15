#include <stdio.h>
#include <unistd.h>

int main() {
	printf("PID = %d\n", getpid());
	int pid = fork();
  	printf("PID = %d\n", getpid());
  
	if (pid == 0) {
		fork();
		printf("PID = %d\n", getpid());
		
		sleep(10);
	}
	pid = fork();
	printf("PID = %d\n", getpid());
	
	if (pid != 0)
		sleep(1);
	
	sleep(1);
	printf("DONE: %d\n", getpid());
}
