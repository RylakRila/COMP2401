#include <stdio.h>

#define MAX_ITEM_NAME_SIZE      25
#define ITEM_LIMIT              10

int getItemsFromUser(char itemsArray[][MAX_ITEM_NAME_SIZE + 1], 
                     float pricesArray[]) {
    int count = 0;

    while(1) {
        printf("Enter an item name: ");
        scanf("%s", itemsArray[count]);

        printf("Enter an item price (use 0 to quit): ");
        scanf("%f", &pricesArray[count]);

        if (pricesArray[count] == 0)
            break;
        else
            count++;

        if (count == ITEM_LIMIT)
            break;
    }

    return count;
}

int main() {
    char items[ITEM_LIMIT][MAX_ITEM_NAME_SIZE+1];
    float prices[ITEM_LIMIT];
    
    int numItems = getItemsFromUser(items, prices);

    float total = 0;
    
    for (int i=0; i<numItems; i++) {
        printf("%-25s%8.2f\n", items[i], prices[i]);
        total += prices[i];
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

