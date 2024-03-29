#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <sys/time.h>
#include <time.h>

#include "restaurant.h"


// Get the current time in microseconds
long getTimeInMicroseconds(){
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

// Initialize the order taker by creating the server socket, setting up the server address,
// binding the server socket and setting up the server to listen for guest clients.
void initializeServer(int *serverSocket, struct sockaddr_in  *serverAddress) {
	int status;

	// Create the server socket
	*serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*serverSocket < 0) {
		printf("*** RESTAURANT SERVER ERROR: Could not open socket.\n");
		exit(-1);
	}

	// Setup the server address
	memset(serverAddress, 0, sizeof(*serverAddress)); // zeros the struct
	(*serverAddress).sin_family = AF_INET;
	(*serverAddress).sin_addr.s_addr = htonl(INADDR_ANY);
	(*serverAddress).sin_port = htons((unsigned short)SERVER_PORT);

	// Bind the server socket
	int one = 1; 
	setsockopt(*serverSocket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
 	status = bind(*serverSocket,  (struct sockaddr *)serverAddress, sizeof(*serverAddress));
	if (status < 0) {
		printf("*** RESTAURANT SERVER ERROR: Could not bind socket.\n");
		exit(-1);
	}

	// Set up the line-up to handle up to 10 buffered guests 
	status = listen(*serverSocket, 10);
	if (status < 0) {
		printf("*** RESTAURANT SERVER ERROR: Could not listen on socket.\n");
		exit(-1);
	}
}



// Handle client requests coming in through the server socket.  This code should run
// indefinitiely.  It should wait for a client to send a request, process it, and then
// close the client connection and wait for another client.  The requests that may be
// handled are as follows:
//
//   SHUT_DOWN - causes the server to go offline.  No response is returned.
//
//   ARRIVED - from a customer requesting to get in line to order
//
//	 PLACE_ORDER - from a customer placing his/her order

void startAcceptingCustomers(Restaurant *restaurant) {
	unsigned char       inBuffer[MAX_ITEMS_PER_ORDER+1], response[10];
	char                online = 1;
	int                 addrSize, bytesRcv;

	int                 serverSocket, clientSocket;
	struct sockaddr_in  serverAddress, clientAddr;

	// Initialize the server
	initializeServer(&serverSocket, &serverAddress);
	addrSize = sizeof(clientAddr);
	printf("\nORDER TAKER: online\n");
  	
	// Wait for customers now
	while (online) {
		// Accept a client connection
		clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize);
		if (clientSocket < 0) {
			printf("*** ORDER TAKER ERROR: Could not accept incoming connection.\n");
			exit(-1);
		}
		
		// Receive the command from the client
		bytesRcv = recv(clientSocket, inBuffer, sizeof(inBuffer), 0);
		if (bytesRcv > 0) printf("ORDER TAKER: Received customer request: %d\n", inBuffer[0]);
		
		// Process the command
		switch (inBuffer[0]) {
			case SHUT_DOWN:
				online = 0;
				close(clientSocket);
				break;
			case ARRIVED:
				sem_wait(&(restaurant->LineupSemaphore));
				if (restaurant->driveThruLine[0].customerPid != 0) {
					response[0] = DENIED;
					printf("ORDER TAKER: Customer denied\n");
					
					send(clientSocket, response, 1, MSG_NOSIGNAL);
				} else {
					response[0] = ACCEPTED;
					
					PidUnion pidUnion;
					pidUnion.buffer[0] = inBuffer[1];
					pidUnion.buffer[1] = inBuffer[2];
					pidUnion.buffer[2] = inBuffer[3];
					pidUnion.buffer[3] = inBuffer[4];
					restaurant->driveThruLine[0].customerPid = pidUnion.pid;
					restaurant->driveThruLine[0].startedOrder = 0;
					restaurant->driveThruLine[0].order.orderNumber = NO_ORDER_YET;
					printf("ORDER TAKER: Customer %d accepted\n", pidUnion.pid);
					
					send(clientSocket, response, 1, MSG_NOSIGNAL);
				}
				sem_post(&(restaurant->LineupSemaphore));
				close(clientSocket);
				break;
			case PLACE_ORDER:
				sem_wait(&(restaurant->LineupSemaphore));
				restaurant->driveThruLine[4].order.numItems = inBuffer[1];
				printf("Number of items: %d\n", inBuffer[1]);
				
				int total = 0;
				int maxCookTime = 0;
				
				for (int i = 0; i < inBuffer[1]; i++) {
					char currItemId = inBuffer[i+2];
					restaurant->driveThruLine[4].order.items[i].name = ItemNames[currItemId];
					restaurant->driveThruLine[4].order.items[i].cost = ItemPrices[currItemId];
					
					// Calculate the total time for the order
					total += ItemPrepTime[currItemId];
					total += ItemFillTime[currItemId];
					if (ItemCookTime[currItemId] > maxCookTime)
						maxCookTime = ItemCookTime[currItemId];
					total += PACK_TIME;
					
					restaurant->driveThruLine[4].order.orderNumber = restaurant->nextOrderNumber++;
				}
				restaurant->driveThruLine[4].order.secondsUntilReady = total + maxCookTime;
				printf("takes %d to finish order %d\n", total + maxCookTime, restaurant->driveThruLine[4].order.orderNumber);
				sem_post(&(restaurant->LineupSemaphore));
				close(clientSocket);
				break;
			default:
				printf("*** ORDER TAKER ERROR: Unknown command received.\n");
				break;
		}
	}
	
	// This will be reached only when the server shuts down
	close(serverSocket);
}

