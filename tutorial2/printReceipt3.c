
#include <stdio.h>

#define MAX_ITEM_NAME_SIZE      25
#define ITEM_LIMIT              10

int main() {
    char items[ITEM_LIMIT][MAX_ITEM_NAME_SIZE+1];
    float prices[ITEM_LIMIT];
    
    float total = 0;
    
    int numItems = 0;

    while(1) {
        // printf("Enter an item name: ");
        scanf("%s", items[numItems]);

        // printf("Enter an item price (use 0 to quit): ");
        scanf("%f", &prices[numItems]);

        if (prices[numItems] == 0)
            break;
        else {
            printf("%-25s%8.2f\n", items[numItems], prices[numItems]);
            total += prices[numItems]; 
            numItems++;
        }

        if (numItems == ITEM_LIMIT)
            break;
    }
    
    for (int i = 0; i < MAX_ITEM_NAME_SIZE + 8; i++) {
        printf("-");
    }
    printf("\n");
    
    printf("%-25s%8.2f\n", "Sub Total", total);
    printf("%-25s%8.2f\n", "Tax (13% HST)", total * 0.13);

    for (int i = 0; i < MAX_ITEM_NAME_SIZE + 8; i++) {
        printf("-");
    }
    printf("\n");

    printf("%-25s%8.2f\n", "Total", total * 1.13);
}

