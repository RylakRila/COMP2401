#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#include "primeServer.h"


// --------------------------------------------------------------
// This function attempts to connect to the server.
// --------------------------------------------------------------
int connectToServer() {
  struct sockaddr_in   clientAddress;
  
  // Create socket
  int clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (clientSocket < 0) {
    printf("*** CLIENT ERROR: Could open socket.\n");
    exit(-1);
  }

  // Setup address
  memset(&clientAddress, 0, sizeof(clientAddress));
  clientAddress.sin_family = AF_INET;
  clientAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
  clientAddress.sin_port = htons((unsigned short) SERVER_PORT);

  // Connect to server
  int status = connect(clientSocket, (struct sockaddr *) &clientAddress, sizeof(clientAddress));
  if (status < 0) {
    printf("*** CLIENT ERROR: Could not connect to server.\n");
    exit(-1);
  }

  printf("CLIENT CONNECTED\n");
  return clientSocket;
}


// --------------------------------------------------------------
// This is where the program starts.
// --------------------------------------------------------------
int main(int argc, char *argv[]) {
  int                 bytesRcv;
  char                buffer[80];   // stores sent and received data

  // Make sure user entered command line parameters properly
  if ((argc != 2) ||
    ((strcmp(argv[1], "stop") != 0) &&
     (strcmp(argv[1], "stats") != 0) &&
        (atol(argv[1]) <= 0))) {
    printf("PROGRAM USAGE:  ./client <command>\n");
    printf("  <command> may be:\n");
    printf("    stop  - stops the server\n");
    printf("    stats - asks for statistics from the server\n");
    printf("    <unsigned long> - a positive long integer\n");
    exit(-1);
  }
  
  // Attempt to connect to the server
  int clientSocket = connectToServer();
  
  // ADD THE INTERESTING STUFF HERE
  // Check if the user entered the "stop" command
  if (strcmp(argv[1], "stop") == 0) {
    buffer[0] = STOP;
    send(clientSocket, buffer, 1, MSG_NOSIGNAL);
  }
  // Check if the user entered the "stats" command
  else if (strcmp(argv[1], "stats") == 0) {
    buffer[0] = STATS;
    send(clientSocket, buffer, 1, MSG_NOSIGNAL);
    
    // Get the reply from the server
    bytesRcv = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRcv > 0) {
      StatsNumber  temp;
      temp.numberBytes[0] = buffer[0];
      temp.numberBytes[1] = buffer[1];
      temp.numberBytes[2] = buffer[2];
      temp.numberBytes[3] = buffer[3];
      unsigned int numbersChecked = temp.numberAsInt;
      temp.numberBytes[0] = buffer[4];
      temp.numberBytes[1] = buffer[5];
      temp.numberBytes[2] = buffer[6];
      temp.numberBytes[3] = buffer[7];
      unsigned int primesFound = temp.numberAsInt;
      
      printf("\nSTATS: %d numbers checked, %d prime numbers found so far\n",
             numbersChecked, primesFound);
    }
  }
  // Check if the user entered a number to compute
  else if (atol(argv[1]) > 0) {
    buffer[0] = COMPUTE;
    
    LargeNumber input;
    input.numberAsLong = atol(argv[1]);
    for (int i = 0; i < 8; i++) {
      buffer[i+1] = input.numberBytes[i];
    }
    
    buffer[1] = atoi(argv[1]);
    send(clientSocket, buffer, 9, MSG_NOSIGNAL);
    
    // Get the reply from the server
    bytesRcv = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRcv > 0) {
      ComputeTime  time;
      time.timeBytes[0] = buffer[0];
      time.timeBytes[1] = buffer[1];
      time.timeBytes[2] = buffer[2];
      time.timeBytes[3] = buffer[3];
      float timeToComputePrime = time.timeAsFloat;
      if (timeToComputePrime >= 0)
        printf("%ld is prime (%1.3f seconds)\n",
                (unsigned long int) atol(argv[1]), timeToComputePrime);
      else
        printf("%ld is not prime\n", (unsigned long int) atol(argv[1]));
    }
  }
  // Otherwise, the command is invalid
  else {
    printf("Invalid command\n");
  }
  
  close(clientSocket);  // Don't forget to close the socket !
  printf("CLIENT: Shutting down.\n");
}
