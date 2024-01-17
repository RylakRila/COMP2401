#include <stdio.h>

#define MAX_ITEM_NAME_SIZE      25

int main() {
    char* items[] = {"Pancake Mix", "Orange Juice", "Chocolate Bar", "Lolypop",
                         "24-pack Coke Classic", "plastic bag"};
    float prices[] = {3.99, 2.97, 1, 0.5, 6.99, 0.05};
    
    int numItems = sizeof(items) / sizeof(char*);

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
