/*
* Student Name: Yuntian Ye
* Student Number: 101322932
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <unistd.h>

#define M_PI 3.14159265358979323846 /* pi */

const double CITY_DIAMETER = 60;
const double CITY_RADIUS = CITY_DIAMETER / 2;

typedef struct Coordinate {
    double x;
    double y;
} coordinate_t;

// generate random number within circle using polar coordinate
coordinate_t randCoord() {
    coordinate_t coord;
    
    // multiple 2pi by random number in [0, 1]
    // to get an angle theta between 0 and 2pi
    double theta = (rand() / (double)RAND_MAX) * 2 * M_PI;
    // randomly generates the r for polar coordinates
    // by multiplying it by radius of city (circle)
    double r = sqrt(rand() / (double)RAND_MAX) * CITY_RADIUS;
    // by area formula of circle: pi * r^2.
    // If we randomly generates a value of r, it has 1/2 possibility
    // to located on first half of the radius, which eventually on 1/4
    // of area of circle around center. Thus, for uniform distribution,
    // we take square root to cancel this
    
    // convert polar to rectangular
    coord.x = r * cos(theta);
    coord.y = r * sin(theta);
    
    return coord;
}

double euclideanDistance(coordinate_t a, coordinate_t b) {
    double distanceX = a.x - b.x;
    double distanceY = a.y - b.y;
    
    return sqrt(distanceX * distanceX + distanceY * distanceY);
}

int main() {
    int numDrivers = 0;
    int numPackages = 0;
    
    do {
        printf("Enter number of delivery drivers: ");
        scanf("%d", &numDrivers);
        while (getchar() != '\n');
        
        if (numDrivers < 2 || numDrivers > 200)
            printf(" *** Number of delivery drivers must be between 2 and 200 ***\n");
    } while (numDrivers < 2 || numDrivers > 200);
    
    do {
        printf("Enter number of packages to be delivered: ");
        scanf("%d", &numPackages);
        while (getchar() != '\n');
        
        if (numPackages < 10 || numPackages > 50000)
            printf(" *** Number of packages must be between 10 and 50000 ***\n");
    } while (numPackages < 10 || numPackages > 50000);
    
    // set random seed as current time
    srand(time(NULL));
    
    printf("\nDrivers: %d\n", numDrivers);
    // randomly generates coordinate for drivers
    coordinate_t driversCoor[numDrivers];
    
    for (int i = 0; i < numDrivers; i++) {
        driversCoor[i] = randCoord();
        printf("%6.2f  %6.2f\n", driversCoor[i].x, driversCoor[i].y);
    }
    
    // set random seed as current process id
    srand(getpid());
    
    printf("\nPackages: %d\n", numPackages);
    // an array to store coordinates of packages
    coordinate_t packagesCoor[numPackages];
    
    // an array to store index of each driver for each package
    int driverIndices[numPackages];
    
    for (int i = 0; i < numPackages; i++) {
        // randomly generates coordinate for packages
        packagesCoor[i] = randCoord();
        
        // for current packages, calculate distance between
        // package and each driver, find smallest
        double smallest = 60.0;
        coordinate_t currPackage = packagesCoor[i];
        for (int j = 0; j < numDrivers; j++) {
            double currDistance =
                euclideanDistance(currPackage, driversCoor[j]);
            // printf("%.2f\n", currDistance);
            if (smallest > currDistance) {
                smallest = currDistance;
                driverIndices[i] = j;
            }
        }
        
        printf("%6.2f  %6.2f %d\n", packagesCoor[i].x, packagesCoor[i].y,
               driverIndices[i]);
    }
    
    return 0;
}
