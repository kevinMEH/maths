#include <math.h>

double average(double* array, int size) {
    double total = 0.0;
    for(int i = 0; i < size; i++) {
        total += array[i];
    }
    return total / size;
}

double standardDeviation(double* array, int size) {
    double innerSum = 0.0;
    double mean = average(array, size);
    for(int i = 0; i < size; i++) {
        innerSum += pow(array[i] - mean, 2);
    }
    return sqrt(innerSum / size);
}