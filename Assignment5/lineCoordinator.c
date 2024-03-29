#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>

#include "restaurant.h"

// Go into an infinite loop to update the driveThruLineup
void *runLineCoordination(void *r) {
	Restaurant *restaurant = (Restaurant *)r;
	
	while(1) {
		sleep(1); // a slight delay so that we don't use up a lot of CPU time
		
		sem_wait(&restaurant->LineupSemaphore);
		// signal the customer to pick up their order and leave
		if (restaurant->driveThruLine[9].customerPid != 0 &&
			restaurant->driveThruLine[9].order.secondsUntilReady <= 0) {
			int result = kill(restaurant->driveThruLine[9].customerPid, SIGUSR2);
			restaurant->driveThruLine[9].customerPid = 0;
			restaurant->driveThruLine[9].order.orderNumber = NO_ORDER_YET;
		}
		
		// move customers in the line-up to the right
		if (restaurant->driveThruLine[9].order.orderNumber == NO_ORDER_YET) {
			for (int i = 8; i >= 5; i--) {
				if (restaurant->driveThruLine[i].order.orderNumber != NO_ORDER_YET && restaurant->driveThruLine[i + 1].order.orderNumber == NO_ORDER_YET) {
					restaurant->driveThruLine[i + 1] = restaurant->driveThruLine[i];
					if (i == 5) {
						restaurant->driveThruLine[i].customerPid = 0;
						restaurant->driveThruLine[i].order.orderNumber = NO_ORDER_YET;
					}
				}
			}
		}
		
		// move the ordered customer to as close as pick-up position - one time
		if (restaurant->driveThruLine[4].order.orderNumber != NO_ORDER_YET) {
			for (int i = 9; i >= 5; i--) {
				if (restaurant->driveThruLine[i].order.orderNumber == NO_ORDER_YET) {
					restaurant->driveThruLine[i] = restaurant->driveThruLine[4];
					restaurant->driveThruLine[4].customerPid = 0;
					restaurant->driveThruLine[4].order.orderNumber = NO_ORDER_YET;
					break;
				}
			}
		}
		
		// move customers in the line-up to the ordering position
		if (restaurant->driveThruLine[4].customerPid == 0) {
			for (int i = 3; i >= 1; i--) {
				if (restaurant->driveThruLine[i].customerPid != 0 &&
					restaurant->driveThruLine[i + 1].customerPid == 0) {
					restaurant->driveThruLine[i + 1] = restaurant->driveThruLine[i];
					if (i == 1) restaurant->driveThruLine[i].customerPid = 0;
				}
			}
		}
		
		// move the first customer to as close as ordering position
		if (restaurant->driveThruLine[0].customerPid != 0) {
			for (int i = 4; i >= 1; i--) {
				if (restaurant->driveThruLine[i].customerPid == 0) {
					restaurant->driveThruLine[i] = restaurant->driveThruLine[0];
					restaurant->driveThruLine[0].customerPid = 0;
					break;
				}
			}
		}
		
		// signal the customer to start ordering
		if (restaurant->driveThruLine[4].customerPid != 0 && restaurant->driveThruLine[4].startedOrder == 0) {
			int result = kill(restaurant->driveThruLine[4].customerPid, SIGUSR1);
			restaurant->driveThruLine[4].startedOrder = 1;
		}
		sem_post(&restaurant->LineupSemaphore);
	}
}
