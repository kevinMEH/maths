#ifndef INTERPOLATE
#define INTERPOLATE

#include "polynomial.h"

typedef struct Point {
    double x;
    double y;
} Point;

void lagrange(Point* points, int numPoints, Polynomial* result);

#endif