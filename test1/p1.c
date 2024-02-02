#include<stdio.h>

char maze[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                     {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                     {1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
                     {1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
                     {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                     {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
                     {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                     {1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
                     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int main() {
    int dead_ends = 0;
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int walls = 0;
            
            if (maze[i][j] == 0) {
                walls += maze[i-1][j] == 1 ? 1 : 0; // up
                walls += maze[i+1][j] == 1 ? 1 : 0; // down
                walls += maze[i][j - 1] == 1 ? 1 : 0; // left
                walls += maze[i][j + 1] == 1 ? 1 : 0; // right
            }
            
            if (walls == 3) dead_ends += 1;
        }
    }
    
    printf("%d\n", dead_ends);
}