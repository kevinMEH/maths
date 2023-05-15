#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include "matrix.h"

double totalDistance(Matrix* distanceMatrix, int* path) {
    double distance = 0.0;
    for(int i = 1; i < distanceMatrix->rows; i++) {
        distance += valueAt(distanceMatrix, path[i - 1], path[i]);
    }
    return distance;
}

// The distanceMatrix should be a matrix such that each row represents place i,
// and each column represents the distance from place i to place j.
int* greedyPath(Matrix* distanceMatrix, int startIndex) {
    // TODO: Use bitmap if matrix width less than or equal to 64
    int size = distanceMatrix->rows;
    int used[size];
    memset(used, 0, sizeof(int) * size);
    int* path = (int*) calloc(size, sizeof(int));
    used[startIndex] = 1;
    int lastIndex = path[0] = startIndex;
    for(int i = 1; i < size; i++) { // Filling up the path
        int leastCostIndex = 0;
        for(int j = 0; j < size; j++) { // Find first unused index
            if(used[j] == 0) {
                leastCostIndex = j;
                break;
            }
        }
        for(int j = leastCostIndex + 1; j < size; j++) { // Find least distance index
            if(valueAt(distanceMatrix, lastIndex, j)
            < valueAt(distanceMatrix, lastIndex, leastCostIndex)
            && used[j] == 0) {
                leastCostIndex = j;
            }
        }
        lastIndex = path[i] = leastCostIndex;
        used[leastCostIndex] = 1;
    }
    return path;
}

/**
 * Metropolis Hastings walk to find optimal path.
 * Switching strategy: switching two random array elements, except for first.
 * Not a very good strategy, ideally rotating / switching random number of
 * elements. TODO:
 * 
 * THIS FUNCTION USES BASE 2 FOR THE PROBABILITY FUNCtiON EXPONENTIAL AS THAT IS
 * MORE INTUITIVE.
 * 
 * Assuming temperature = 1:
 * If the new distance is greater by 1, the chance of switching is 1/2.
 * If the new distance is greater by 2, the chance of switching is 1/4.
 * Increasing the temperature will make switching more frequent
*/
int* metropolisPath(Matrix* distanceMatrix, int startIndex, double(rng)(), double temperature, int iterations) {
    int size = distanceMatrix->rows;
    int sizem1 = size - 1;
    int* path = greedyPath(distanceMatrix, startIndex);
    int* bestPath = (int*) malloc(sizeof(int) * size);
    double bestDistance = totalDistance(distanceMatrix, path);
    while(iterations-- != 0) {
        double originalDistance = totalDistance(distanceMatrix, path);
        int firstIndex = 1 + (int)(rng() * sizem1);
        int secondIndex = 1 + (int)(rng() * sizem1);
        int temp = path[firstIndex];
        path[firstIndex] = path[secondIndex];
        path[secondIndex] = temp;
        double modifiedDistance = totalDistance(distanceMatrix, path);
        if(modifiedDistance < bestDistance) {
            memcpy(bestPath, path, sizeof(int) * size);
            bestDistance = modifiedDistance;
        } else {
            if(rng() >= (1 / exp2((modifiedDistance - originalDistance) / temperature))) {
                // Switch back
                int temp = path[firstIndex];
                path[firstIndex] = path[secondIndex];
                path[secondIndex] = temp;
            }
        }
    }
    free(path);
    return bestPath;
}

// Linear simulated annealing walk
int* linearAnnealingPath(Matrix* distanceMatrix, int startIndex, double(rng)(),
double startTemperature, double endTemperature, int iterations) {
    double deltaTemp = startTemperature - endTemperature;
    int total = iterations;

    int size = distanceMatrix->rows;
    int sizem1 = size - 1;
    int* path = greedyPath(distanceMatrix, startIndex);
    int* bestPath = (int*) malloc(sizeof(int) * size);
    double bestDistance = totalDistance(distanceMatrix, path);
    while(iterations-- != 0) {
        double originalDistance = totalDistance(distanceMatrix, path);
        int firstIndex = 1 + (int)(rng() * sizem1);
        int secondIndex = 1 + (int)(rng() * sizem1);
        int temp = path[firstIndex];
        path[firstIndex] = path[secondIndex];
        path[secondIndex] = temp;
        double modifiedDistance = totalDistance(distanceMatrix, path);
        if(modifiedDistance < bestDistance) {
            memcpy(bestPath, path, sizeof(int) * size);
            bestDistance = modifiedDistance;
        } else {
            if(rng() >= (1 / exp2(
                    (modifiedDistance - originalDistance)
                    / (endTemperature + deltaTemp * ((double) iterations) / total)
                ))
            ) {
                // Switch back
                int temp = path[firstIndex];
                path[firstIndex] = path[secondIndex];
                path[secondIndex] = temp;
            }
        }
    }
    free(path);
    return bestPath;
}