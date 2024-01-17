#include <stdio.h>

int main() {
    char items[4][14] = {"Pancake Mix", "Orange Juice", "Chocolate Bar", "Lolypop"};
    float prices[] = {3.99, 2.97, 1, 0.5};
    
    float total = 0;

    for (int i=0; i<4; i++) {
        printf("%-20s%4.2f\n", items[i], prices[i]);
        total += prices[i];
    }
    printf("-------------------------\n");
    printf("Sub Total           %4.2f\n", total);
    printf("Tax (13% HST)       %4.2f\n", total * 0.13);
    printf("-------------------------\n");
    printf("Total               %4.2f\n", total * 1.13);
}
