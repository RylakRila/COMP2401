#include <stdio.h>
#include <stdlib.h>


// Compute the average value of of an array arr of floats, given the numItems in the array.
// Return the value in the avg variable
void average(float *arr, int numItems, float *avg) {
  *avg = 0;
  for (int i=0; i<numItems; i++) 
    *avg += arr[i];
  *avg /= numItems;
}

// Compute the maximum value of of an array arr of floats, given the numItems in the array.
// Return the value in the max variable
void maximum(float *arr, int numItems, float *max) {
  *max = -1;
  for (int i=0; i<numItems; i++) 
    if (arr[i] > *max)
    	*max = arr[i];
}

// Compute the minimum value of of an array arr of floats, given the numItems in the array.
// Return the value in the min variable
void minimum(float *arr, int numItems, float *min) {
  *min = 9999999;
  for (int i=0; i<numItems; i++) 
    if (arr[i] < *min)
    	*min = arr[i];
}
