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
    
    scanf("%d", &numDrivers);
    while (getchar() != '\n');
    
    if (numDrivers < 2 || numDrivers > 200)
        exit(0);
    
    scanf("%d", &numPackages);
    while (getchar() != '\n');
    
    if (numPackages < 10 || numPackages > 50000)
        exit(0);
    
    printf("%d %d\n", numDrivers, numPackages);
    
    // set random seed as current time
    srand(time(NULL));
    
    // randomly generates coordinate for drivers
    coordinate_t driversCoor[numDrivers];
    
    for (int i = 0; i < numDrivers; i++) {
        driversCoor[i] = randCoord();
    }
    
    // set random seed as current process id
    srand(getpid());
    
    // an array to store coordinates of packages
    coordinate_t packagesCoor[numPackages];
    
    // an array to store index of each driver for each package
    int driverIndices[numPackages];
    
    for (int i = 0; i < numPackages; i++) {
        // randomly generates coordinate for packages
        // and store it in some temp variable in scope
        packagesCoor[i] = randCoord();
        coordinate_t currPackage = packagesCoor[i];
        
        // started by set smallest to largest it can get
        // which is the city diameter
        double smallest = 60.0;
        // for current packages, calculate distance between
        // package and each driver, find smallest
        for (int j = 0; j < numDrivers; j++) {
            double currDistance = // calculate the distance
                euclideanDistance(currPackage, driversCoor[j]);
            // printf("%.2f\n", currDistance);
 
            // if it is less than current smallest value
            // set it to be smallest, and update the driver
            // indices for current package in indices Array 
            if (smallest > currDistance) {
                smallest = currDistance;
                driverIndices[i] = j;
            }
        }
        
        printf("%.2f %.2f %d ", packagesCoor[i].x, packagesCoor[i].y,
               driverIndices[i]);
    }
    
    printf("\n");
    
    return 0;
}
