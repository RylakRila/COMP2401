#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "restaurant.h"

void main() {
  // Set up the random seed
  srand(time(NULL));
  
  for (int i = 0; i < 20; i++) {
    pid_t pid = fork();
    
    if (pid < 0) {
      printf("*** Error forking\n");
      exit(-1);
    } else if (pid == 0) {
      // Child process
      int numItems = rand() % 10 + 1;
      char *argv[numItems + 2];
      
      argv[0] = "./customer";
      
      for (int j = 1; j <= numItems; j++) {
        // Generate a random number between 1 and 10
        // include space for the null terminator
        char *item = malloc(3 * sizeof(char));
        sprintf(item, "%d", rand() % NUM_MENU_ITEMS + 1);
        argv[j] = item;
      }
      
      argv[numItems + 1] = NULL;
      
      // execute the customer process
      if (execvp(argv[0], argv) == -1) {
        printf("*** Error executing customer\n");
        exit(-1);
      }
      
    } else {
      // Parent process
      usleep(rand() % 10 * 500000);
    }
  }
}

