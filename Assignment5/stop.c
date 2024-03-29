#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "restaurant.h"


void main() {
	int                 clientSocket;  // client socket id
	struct sockaddr_in  clientAddress; // client address
	int                 status;
	
	char buffer[1];
	
	// create the client socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket < 0) {
		printf("*** CLIENT ERROR: Could not open socket.\n");
		exit(-1);
	}
	
	// setup the server address
	memset(&clientAddress, 0, sizeof(clientAddress));
	clientAddress.sin_family = AF_INET;
	clientAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
	clientAddress.sin_port = htons((unsigned short)SERVER_PORT);
	
	// connect to the server
	status = connect(clientSocket, (struct sockaddr *) &clientAddress, sizeof(clientAddress));
	if (status < 0) {
		printf("*** CLIENT ERROR: Could not connect.\n");
		exit(-1);
	}
	printf("Connected to server.\n");
	
	buffer[0] = SHUT_DOWN;
	// send the server the SHUT_DOWN command
	send(clientSocket, buffer, 1, 0);
	// close the socket
	close(clientSocket);
}


