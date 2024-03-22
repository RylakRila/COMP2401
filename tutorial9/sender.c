#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main() {
  int pid, choice, result;

  printf("Enter PID of the prime-computing program: ");
  scanf("%d", &pid);

  while (1) {
    printf("Enter command to send to handler (i.e., 1, 2 or 3), or anything else to quit this program:\n");
    printf(" (1) pause/resume computations\n");
    printf(" (2) display statistics\n");
    printf(" (3) stop program\n");
    printf(">> ");
    scanf("%d", &choice);
    
    switch(choice) {
      case 1: result = kill(pid, SIGUSR1);
      	break;
      case 2: result = kill(pid, SIGUSR2);
      	break;
      case 3: result = kill(pid, SIGINT);
      	break;
      default: exit(0);
    }
    if (result == -1) {
      printf("*** Error sending signal to Process %d ***\n", pid);
      exit(-1);
    }
  }
}
