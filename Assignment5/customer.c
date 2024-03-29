#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "restaurant.h"

#define BUFFER_LIMIT		100

// A RestaurantServer connection ... when made
int                 clientSocket;  // client socket id
struct sockaddr_in  clientAddress; // client address

volatile sig_atomic_t signalOneReceived = 0;
volatile sig_atomic_t signalTwoReceived = 0;

int connectToServer(struct sockaddr_in *serverAddress, int *status) {
  int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serverSocket < 0) {
    printf("*** CUSTOMER ERROR: Could open socket to Restaurant Server\n");
    exit(-1);
  }
    
  memset(serverAddress, 0, sizeof(struct sockaddr_in));
  (*serverAddress).sin_family = AF_INET;
  (*serverAddress).sin_addr.s_addr = inet_addr(SERVER_IP);
  (*serverAddress).sin_port = htons((unsigned short) SERVER_PORT);
  
  *status = connect(serverSocket, (struct sockaddr *)serverAddress, sizeof(struct sockaddr_in));
  if ((*status) < 0) {
    printf("*** CUSTOMER ERROR: Could not connect to Restaurant Server\n");
    exit(-1);
  }
  
  printf("Connected to Restaurant Server\n");
  return serverSocket;
}

void handleSig1(int sig) {
  signalOneReceived = 1;
}

void handleSig2(int sig) {
  signalTwoReceived = 1;
}

// Start up a Customer process. There should be a sequence of integers as command line arguments.  
// Each integer must be a number from 1 to the number of menu items at the restaurant.
void main(int argc, char *argv[]) {
	struct sockaddr_in   restaurantServerAddress; // client address for restaurant server
	int                  restaurantServerSocket;  // client socket id for restaurant server
	int                                  status;  // status from a sent message
	int					               bytesRcv;  // number of bytes received
	unsigned char buffer[MAX_ITEMS_PER_ORDER+3];  // buffer used for sending and receiving data (3 extra to allow for command and pid)
	
	char denied = 1;
	while(denied) {
    restaurantServerSocket = connectToServer(&restaurantServerAddress, &status);
    
    PidUnion pidUnion;
    pidUnion.pid = getpid();
    
    buffer[0] = ARRIVED;
    buffer[1] = pidUnion.buffer[0];
    buffer[2] = pidUnion.buffer[1];
    buffer[3] = pidUnion.buffer[2];
    buffer[4] = pidUnion.buffer[3];
    
    send(restaurantServerSocket, buffer, sizeof(PidUnion) + 1, MSG_NOSIGNAL);
    
    bytesRcv = recv(restaurantServerSocket, buffer, 1, 0);
    
    close(restaurantServerSocket);
    
    if (bytesRcv > 0 && buffer[0] == ACCEPTED) denied = 0;
    else if (bytesRcv > 0 && buffer[0] == DENIED) sleep(2);
	}
  
  if (!denied) {
    // waits for a SIGUSR1 signal
    signal(SIGUSR1, handleSig1);
    
    while(!signalOneReceived)
      sleep(1);
    
    int n = argc - 1;
    usleep(1000000 + 200000 * n);
    
    restaurantServerSocket = connectToServer(&restaurantServerAddress, &status);
    
    buffer[0] = PLACE_ORDER; // command
    buffer[1] = n; // number of items in the order
    // copy the order into the buffer, starting at index 2
    for (int i = 2; i <= n + 1; i++) {
      buffer[i] = atoi(argv[i - 1]);
    }
    
    send(restaurantServerSocket, buffer, n + 2, MSG_NOSIGNAL);
    
    close(restaurantServerSocket);
  }
  
  signal(SIGUSR2, handleSig2);
  
  while(!signalTwoReceived)
    sleep(1);
  
  exit(0);
}
