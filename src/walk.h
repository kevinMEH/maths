#ifndef WALK
#define WALK

#include "matrix.h"

double totalDistance(Matrix* distanceMatrix, int* path);

int* greedyPath(Matrix* distanceMatrix, int startIndex);
int* metropolisPath(Matrix* distanceMatrix, int startIndex, double(rng)(), double temperature, int iterations);
int* linearAnnealingPath(Matrix* distanceMatrix, int startIndex, double(rng)(), double startTemperature, double endTemperature, int iterations);

#endif