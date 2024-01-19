/*
* Student Name: Yuntian Ye
* Student Number: 101322932
*/

#include <stdio.h>

// const char* CHOCO_BARS[5] = {"Oh Henry", "Coffee Crisp", "Aero", "Smarties",
//                              "Crunchie"};

// const float PRICES[5] = {0.87, 0.88, 0.50, 1.29, 0.98};
const float priceOhHenry = 0.87;
const float priceCoffeeCrisp = 0.88;
const float priceAero = 0.50;
const float priceSmarties = 1.29;
const float priceCrunchie = 0.98;

// const int BARS_PER_BOX[] = {24, 36, 48, 24, 36};
const int barsOhHenry = 24;
const int barsCoffeeCrisp = 36;
const int barsAero = 48;
const int barsSmarties = 24;
const int barsCrunchie = 36;

// HST constant
const float HST = 0.13;

int main() {
    // number of boxes of each chocolate type
    int boxOhHenry, boxCoffeeCrisp, boxAero, boxSmarties, boxCrunchie = 0;
    
    // int numBoxes[5] = {0, 0, 0, 0, 0};
    // int types = sizeof(CHOCO_BARS) / sizeof(char*);
    printf("1. Oh Henry        $%.2f each\n", priceOhHenry);
    printf("2. Coffee Crisp    $%.2f each\n", priceCoffeeCrisp);
    printf("3. Aero            $%.2f each\n", priceAero);
    printf("4. Smarties        $%.2f each\n", priceSmarties);
    printf("5. Crunchie        $%.2f each\n", priceCrunchie);
    
    printf("\n");

    /* for (int i = 0; i < types; i++) {
        printf("How many boxes of %s bars would you like (%d bars per box)? ",
               CHOCO_BARS[i], BARS_PER_BOX[i]);
        
        scanf("%d", &(numBoxes[i]));
        while (getchar() != '\n');
    }*/
    printf("How many boxes of Oh Henry bars would you like (%d bars per box)? ", barsOhHenry);
    scanf("%d", &boxOhHenry);
    while (getchar() != '\n');
    printf("How many boxes of Coffee Crisp bars would you like (%d bars per box)? ", barsCoffeeCrisp);
    scanf("%d", &boxCoffeeCrisp);
    while (getchar() != '\n');
    printf("How many boxes of Aero bars would you like (%d bars per box)? ", barsAero);
    scanf("%d", &boxAero);
    while (getchar() != '\n');
    printf("How many boxes of Smarties bars would you like (%d bars per box)? ", barsSmarties);
    scanf("%d", &boxSmarties);
    while (getchar() != '\n');
    printf("How many boxes of Crunchie bars would you like (%d bars per box)? ", barsCrunchie);
    scanf("%d", &boxCrunchie);
    while (getchar() != '\n');
    
    printf("\n"); // formatting
    
    // printf("%d %d %d %d %d", boxOhHenry, boxCoffeeCrisp, boxAero,
    // boxSmarties, boxCrunchie);
    float totalCost = 0.0;
    
    /* 
    for (int i = 0; i < types; i++) {
        // get the # boxes of each product
        int currBoxNum = numBoxes[i];
        
        float costPerProduct = currBoxNum * BARS_PER_BOX[i] * PRICES[i];
        totalCost += costPerProduct;
        printf("%3d boxes of %-12s (%d x $%.2f per box) = $ %8.2f\n",
               currBoxNum, CHOCO_BARS[i], BARS_PER_BOX[i], PRICES[i],
               costPerProduct);
    }*/
    float costOhHenry = boxOhHenry * barsOhHenry * priceOhHenry;
    printf("%3d boxes of Oh Henry     (%d x $%.2f per box) = $ %8.2f\n", 
           boxOhHenry, barsOhHenry, priceOhHenry, costOhHenry);

    float costCoffeeCrisp = boxCoffeeCrisp * barsCoffeeCrisp * priceCoffeeCrisp;
    printf("%3d boxes of Coffee Crisp (%d x $%.2f per box) = $ %8.2f\n", 
           boxCoffeeCrisp, barsCoffeeCrisp, priceCoffeeCrisp, costCoffeeCrisp);

    float costAero = boxAero * barsAero * priceAero;
    printf("%3d boxes of Aero         (%d x $%.2f per box) = $ %8.2f\n", 
           boxAero, barsAero, priceAero, costAero);

    float costSmarties = boxSmarties * barsSmarties * priceSmarties;
    printf("%3d boxes of Smarties     (%d x $%.2f per box) = $ %8.2f\n", 
           boxSmarties, barsSmarties, priceSmarties, costSmarties);

    float costCrunchie = boxCrunchie * barsCrunchie * priceCrunchie;
    printf("%3d boxes of Crunchie     (%d x $%.2f per box) = $ %8.2f\n", 
           boxCrunchie, barsCrunchie, priceCrunchie, costCrunchie);
     

    totalCost += (costOhHenry + costCoffeeCrisp + costAero + costSmarties + 
        costCrunchie);
    
    printf("-----------------------------------------------------------\n");
    printf("%-47s= $ %8.2f\n", "Sub Total", totalCost);
    float tax = totalCost * HST;
    printf("%-46s = $ %8.2f\n", "HST", tax);
    totalCost += tax;
    printf("===========================================================\n");
    printf("%-46s = $ %8.2f\n", "Amount Due", totalCost);
    
    return 0;
}
