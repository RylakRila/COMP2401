#include <stdio.h>
#include <string.h>
#include <time.h>
#include "phoneNetwork.h"

int customerID = 100001;

// helper function definition
unsigned int calcMinOver(unsigned short minAllowed, unsigned short minUsed);

char registerCustomer(PhoneNetworkType *phoneNetwork, char *name, 
                      char *phoneNum, int minAllowed) {
    // alias for the number of customers
    int counter = phoneNetwork->numCustomers;
    
    if (counter < MAX_CUSTOMERS) {
        // set up id, name, and phone number
        phoneNetwork->customers[counter].id = customerID;
        phoneNetwork->customers[counter].name = name;
        phoneNetwork->customers[counter].number = phoneNum;
        
        // set up plan
        PlanType plan;
        plan.minutesAllowed = minAllowed;
        plan.minutesUsed = 0;
        phoneNetwork->customers[counter].plan = plan;
        
        // set up number of calls
        phoneNetwork->customers[counter].numInCalls = 0;
        phoneNetwork->customers[counter].numOutCalls = 0;
        
        // increment number of customers and ID by 1
        phoneNetwork->numCustomers += 1;
        customerID += 1;
        
        return 1;
    } else {
        return 0;
    }
}

void displayCharges(PhoneNetworkType *phoneNetwork) {
    printf("%-16s %-19s %4s %3s %3s %8s %8s %10s %10s %10s %11s\n", 
           "Phone Number", "Name", "Plan", "Out", "In", 
           "Used", "Over", "Base", "Extra", "HST", "Total");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < phoneNetwork->numCustomers; i++) {
        char plan[6]; // 6 characters for the plan, including the null terminator
        
        unsigned short minutesAllowed = phoneNetwork->customers[i].plan.minutesAllowed;
        unsigned short minutesUsed = phoneNetwork->customers[i].plan.minutesUsed;
        unsigned int minutesOver = 0; // minutes over the allowed minutes
        
        float basePrice;
        float extraPrice;
        float hst;
        char  total[11];
        
        // set up value accordingly based on customer's plan
        switch (minutesAllowed) {
            case UNLIMITED:
                strcpy(plan, "UN");
                
                // calculate the charges
                basePrice = UNLIMITED_BASE_PRICE;
                extraPrice = 0;
                hst = (basePrice + extraPrice) * HST;
                break;
            case PAY_PER_MINUTE:
                strcpy(plan, "PPM");
                // Assume PPM_MINUTES is minutes allowed
                minutesOver = calcMinOver(PPM_MINUTES, minutesUsed);
                
                // calculate the charges
                // if minutesOver is 0, then only base price is charged
                basePrice = PPM_BASE * (minutesUsed - minutesOver); 
                extraPrice = PPM_OVER * minutesOver;
                hst = (basePrice + extraPrice) * HST;
                break;
            default:
                sprintf(plan, "%u", minutesAllowed);
                minutesOver = calcMinOver(minutesAllowed, minutesUsed);
                
                // calculate the charges
                basePrice = BASE_PRICE;
                extraPrice = EXTRA_MINUTE_PRICE * minutesOver;
                hst = (basePrice + extraPrice) * HST;
                break;
        }
        
        sprintf(total, "$%7.2f", basePrice + extraPrice + hst);
        
        // print out the charges
        printf("%-16s %-19s %4s %3d %3d %8d %8d %10.2f %10.2f %10.2f %11s\n",
               phoneNetwork->customers[i].number, 
               phoneNetwork->customers[i].name, 
               plan, 
               phoneNetwork->customers[i].numOutCalls,
               phoneNetwork->customers[i].numInCalls,
               minutesUsed, minutesOver, 
               basePrice, extraPrice, hst, total);
    }
}

// calculate the number of minutes over the allowed minutes
unsigned int calcMinOver(unsigned short minAllowed, unsigned short minUsed) {
    if (minUsed > minAllowed) {
        return minUsed - minAllowed;
    }
    return 0;
}

void resetMonth(PhoneNetworkType *phoneNetwork) {
    // reset minutes used and number of calls for each customer
    for (int i = 0; i < phoneNetwork->numCustomers; i++) {
        phoneNetwork->customers[i].plan.minutesUsed = 0;
        phoneNetwork->customers[i].numInCalls = 0;
        phoneNetwork->customers[i].numOutCalls = 0;
    }
    
    // reset calls array and number of calls
    for (int i = 0; i < phoneNetwork->numCalls; i++) {
        phoneNetwork->calls[i].madeFrom = NULL;
        phoneNetwork->calls[i].madeTo = NULL;
        phoneNetwork->calls[i].startTime = 0;
        phoneNetwork->calls[i].endTime = 0;
    }
    phoneNetwork->numCalls = 0;
}

char recordCall(PhoneNetworkType* phoneNetwork, char *callerNum, char *receiverNum, time_t startTime, time_t endTime) {
    // if network reached maximum number of calls
    if (phoneNetwork->numCalls >= MAX_CALLS)
        return 0;
    
    // if caller number or receiver number is NULL or if they are the same
    if (callerNum == NULL || receiverNum == NULL || strcmp(callerNum, receiverNum) == 0)
        return 0;
    
    // if start time is later than or equal to end time
    if (startTime >= endTime) 
        return 0;
    
    unsigned int duration = (endTime - startTime + 59) / 60;
    CustomerType *caller;
    CustomerType *receiver;
    
    for (int i = 0; i < phoneNetwork->numCustomers; i++) {
        if (strcmp(phoneNetwork->customers[i].number, callerNum) == 0) {
            phoneNetwork->customers[i].numOutCalls += 1;
            phoneNetwork->customers[i].plan.minutesUsed += duration;
            caller = &(phoneNetwork->customers[i]);
        }
        
        if (strcmp(phoneNetwork->customers[i].number, receiverNum) == 0) {
            phoneNetwork->customers[i].numInCalls += 1;
            // if receiver's plan is pay per minute then add duration to minutes used
            if (phoneNetwork->customers[i].plan.minutesAllowed == PAY_PER_MINUTE) {
                phoneNetwork->customers[i].plan.minutesUsed += duration;
            }
            receiver = &(phoneNetwork->customers[i]);
        }
    }
    
    phoneNetwork->calls[phoneNetwork->numCalls].madeFrom = caller;
    phoneNetwork->calls[phoneNetwork->numCalls].madeTo = receiver;
    phoneNetwork->calls[phoneNetwork->numCalls].startTime = startTime;
    phoneNetwork->calls[phoneNetwork->numCalls].endTime = endTime;
    phoneNetwork->numCalls += 1;
    return 1;
}

void displayCallLog(PhoneNetworkType *PhoneNetwork) {
    printf("%-15s %-15s %-21s %-21s %13s\n", 
           "Call From #", "Call To #", "Start Time:", "End Time:", "Call Length");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < PhoneNetwork->numCalls; i++) {
        char startTime[21];
        char endTime[21];
        char duration[14];
        
        struct tm start = *localtime(&PhoneNetwork->calls[i].startTime);
        struct tm end = *localtime(&PhoneNetwork->calls[i].endTime);
        
        sprintf(startTime, "%d-%02d-%02d %02d:%02d:%02d", 
                start.tm_year + 1900, start.tm_mon + 1, start.tm_mday, 
                start.tm_hour, start.tm_min, start.tm_sec);
        sprintf(endTime, "%d-%02d-%02d %02d:%02d:%02d", 
                end.tm_year + 1900, end.tm_mon + 1, end.tm_mday, 
                end.tm_hour, end.tm_min, end.tm_sec);
        sprintf(duration, "%.1f minutes",
               (PhoneNetwork->calls[i].endTime - PhoneNetwork->calls[i].startTime) / 60.0);
        
        printf("%-15s %-15s %-21s %-21s %13s\n", 
               PhoneNetwork->calls[i].madeFrom->number, 
               PhoneNetwork->calls[i].madeTo->number, 
               startTime, endTime, duration);
    }
}
