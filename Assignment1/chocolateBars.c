#include <stdio.h>

// const arrays to store info (name, price, # per box)
// of each chocolate bar and box in order
// 0 - Oh Henry
// 1 - Coffee Crisp
// 2 - Aero
// 3 - Smarties
// 4 - Crunchie
const char* CHOCO_BARS[5] = {"Oh Henry", "Coffee Crisp", "Aero", "Smarties",
                             "Crunchie"};

const float PRICES[5] = {0.87, 0.88, 0.50, 1.29, 0.98};

const int BARS_PER_BOX[5] = {24, 36, 48, 24, 36};

// HST constant
const float HST = 0.13;

// global variable to store number of boxes of each chocolate type
int boxOhHenry, boxCoffeeCrisp, boxAero, boxSmarties, boxCrunchie;

// since this code uses array to store info of each chocolate type
// we will need a way to map index of array to # boxes variable
int* getBoxNumByIndex(int i) {
    switch (i) {
    case 0:
        return &boxOhHenry;
    case 1:
        return &boxCoffeeCrisp;
    case 2:
        return &boxAero;
    case 3:
        return &boxSmarties;
    case 4:
        return &boxCrunchie;
    default:
        return NULL;
    }
}

int main() {
    // get the size of array by divide memory size of array by memory size of
    // item in array
    int types = sizeof(CHOCO_BARS) / sizeof(char*);
    
    for (int i = 0; i < types; i++)
        printf("%d. %-16s$%.2f each\n", i + 1, CHOCO_BARS[i], PRICES[i]);
    
    printf("\n");
    
    for (int i = 0; i < types; i++) {
        printf("How many boxes of %s bars would you like (%d bars per box)? ",
               CHOCO_BARS[i], BARS_PER_BOX[i]);
        
        // the address of each # boxes variable
        // use it in scanf() to capture user input
        int* userInput = getBoxNumByIndex(i);
        
        scanf("%d", userInput);
        while (getchar() != '\n');
    }
    
    printf("\n");
    
    // printf("%d %d %d %d %d", boxOhHenry, boxCoffeeCrisp, boxAero,
    // boxSmarties, boxCrunchie);
    float totalCost = 0.0;
    
    for (int i = 0; i < types; i++) {
        // get the address of each # boxes variable
        // and dereference it by *
        int currBoxNum = *getBoxNumByIndex(i);
        // printf("%.2f \n", (*getBoxNumByIndex(i)) * BARS_PER_BOX[i] *
        // PRICES[i]);
        float costPerType = currBoxNum * BARS_PER_BOX[i] * PRICES[i];
        totalCost += costPerType;
        printf("%3d boxes of %-12s (%d x $%.2f per box) = $ %8.2f\n",
               currBoxNum, CHOCO_BARS[i], BARS_PER_BOX[i], PRICES[i],
               costPerType);
    }
    
    printf(
        "-----------------------------------------------------------\n"); // 59
    printf("%-47s= $ %8.2f\n", "Sub Total", totalCost);
    float tax = totalCost * HST;
    printf("%-47s= $ %8.2f\n", "HST", tax);
    totalCost += tax;
    printf("===========================================================\n");
    printf("%-47s= $ %8.2f\n", "Amount Due", totalCost);
    
    return 0;
}
