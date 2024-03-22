#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "primeServer.h"

// This function determines if the given number is prime. It also computes the number of 
float isPrime(unsigned long int n) {
	struct timeval 	startTime, endTime; 	// These keep track of the start and end times
	gettimeofday(&startTime, NULL);
  
	int max = (int)sqrt(n);
	for (int i=2; i<=max; i++) {
		if (n % i == 0)
			return -1;
	}
  
	gettimeofday(&endTime, NULL);
  
	// Return the time that has elapsed (in seconds)
	return (endTime.tv_sec + endTime.tv_usec/1000000.0) - 
	       (startTime.tv_sec + startTime.tv_usec/1000000.0);
}

unsigned int numbersChecked = 0; 	// count of all numbers that have been checked so far 
unsigned int primeNumbersFound = 0; // count of numbers that were determined to be prime

// --------------------------------------------------------------
// This function attempts to set up the server and put it online.
// --------------------------------------------------------------
int startServer() {
	struct sockaddr_in  serverAddress;

  // Create the server socket
  int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serverSocket < 0) {
    printf("*** PRIME SERVER ERROR: Could not open socket.\n");
    exit(-1);
  }

  // Setup the server address
  memset(&serverAddress, 0, sizeof(serverAddress)); // zeros the struct
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = htons((unsigned short) SERVER_PORT);

  // Bind the server socket
  int status = bind(serverSocket,  (struct sockaddr *)&serverAddress, sizeof(serverAddress));
  if (status < 0) {
    printf("*** PRIME SERVER ERROR: Could not bind socket.\n");
    exit(-1);
  }

  // Set up the line-up to handle up to 5 clients in line 
  status = listen(serverSocket, 5);
  if (status < 0) {
    printf("*** PRIME SERVER ERROR: Could not listen on socket.\n");
    exit(-1);
  }

	// All went well ... so we are up and running
	printf("PRIME SERVER ON-LINE\n");
	return serverSocket;
}


// --------------------------------------------------------------
// This is where the program starts.
// --------------------------------------------------------------
int main() {
  struct sockaddr_in  clientAddr;
  int                 addrSize, bytesRcv;
  char                buffer[30];
  char*               response = "OK";
  
  // Start up the server and return its socket id
  int serverSocket = startServer();
  unsigned char   online = 1;
  // Wait for clients now
  while (online) {
    addrSize = sizeof(clientAddr);
    printf("============================================================\n");
    int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &addrSize);
    if (clientSocket < 0) {
      printf("*** PRIME SERVER ERROR: Could accept incoming client connection.\n");
      exit(-1);
    }
    printf("PRIME SERVER: Received client connection.\n");
    
		// ADD THE INTERESTING STUFF HERE
		// Get the message from the client
    bytesRcv = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRcv > 0) printf("PRIME SERVER: Received client request: %d\n", buffer[0]);
    
    switch (buffer[0]) {
      case 1: // handle the STOP command
        online = 0;
        break;
      case 2: // handle the STATS command
        // buffer[0] = numbersChecked;
        // buffer[1] = primeNumbersFound;
        StatsNumber  temp;
        temp.numberAsInt = numbersChecked;
        buffer[0] = temp.numberBytes[0];
        buffer[1] = temp.numberBytes[1];
        buffer[2] = temp.numberBytes[2];
        buffer[3] = temp.numberBytes[3];
        temp.numberAsInt = primeNumbersFound;
        buffer[4] = temp.numberBytes[0];
        buffer[5] = temp.numberBytes[1];
        buffer[6] = temp.numberBytes[2];
        buffer[7] = temp.numberBytes[3];
        send(clientSocket, buffer, 8, 0);
        break;
      case 3: // handle the COMPUTE command
        LargeNumber numberUnion;
        for (int i = 0; i < 8; i++)
          numberUnion.numberBytes[i] = buffer[i+1];
        unsigned long int  number = numberUnion.numberAsLong;
        
        float timeToComputePrime = isPrime(number);
        if (timeToComputePrime >= 0) {
          printf("%ld is prime (%1.3f seconds)\n",
                  (unsigned long int) number, timeToComputePrime);
          primeNumbersFound++;
        }
        numbersChecked++;
        
        // Send back the computation time (or -1.0 if it was not prime)
        ComputeTime  time;
        time.timeAsFloat = timeToComputePrime;
        buffer[0] = time.timeBytes[0];
        buffer[1] = time.timeBytes[1];
        buffer[2] = time.timeBytes[2];
        buffer[3] = time.timeBytes[3];
        send(clientSocket, buffer, 4, 0);
        break;
      default:// handle invalid commands
        // do nothing
    }
    
    printf("PRIME SERVER: Closing client connection.\n");
    close(clientSocket); // Close this client's socket
    
		// MAYBE ADD SOME CODE HERE TOO
    
    
    
  }
  
  // Don't forget to close the sockets!
  close(serverSocket);
  printf("PRIME SERVER OFF-LINE\n");
}
