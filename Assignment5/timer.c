#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>

#include "restaurant.h"


// Go into an infinite loop to update the time that food needs to be processed by decrementing the
// secondsUntilReady values for each order that was placed
void *runTimer(void *r) {
	Restaurant *restaurant = (Restaurant *)r;
	
	while(1) {
		usleep(30000); // wait 1/30th of a second ... roughly
		for (int i = 0; i < MAX_CUSTOMERS; i++) {
			if (restaurant->driveThruLine[i].order.orderNumber != NO_ORDER_YET &&
			    restaurant->driveThruLine[i].order.secondsUntilReady > 0) {
				restaurant->driveThruLine[i].order.secondsUntilReady--;
			}
		}
	}
}


