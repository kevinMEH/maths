#include "integrate.h"

double midpoint(double lower, double upper, int blocks, double(function)(double)) {
    double interval = upper - lower;
    double sum = 0.0;
    for(int i = 0; i < blocks - 1; i++) {
        sum += function(lower + interval * (i + 0.5) / blocks);
    }
    return interval * sum / blocks;
}

double trapezoidal(double lower, double upper, int blocks, double(function)(double)) {
    double interval = upper - lower;
    double sumDiv2 = function(lower) + function(upper);
    sumDiv2 /= 2;
    for(int i = 1; i < blocks; i++) {
        // We do interval * i / blocks instead of stepSize * i for
        // precision reasons. (where stepSize = (upper - lower)/blocks,
        // stepSize being constant will lose percision due to rounding.)
        sumDiv2 += function(lower + interval * i / blocks);
    }
    return interval * sumDiv2 / blocks;
}

double simpson13(double lower, double upper, int blocks, double(function)(double)) {
    double interval = upper - lower;
    double sumDiv2 = function(lower) + function(upper);
    sumDiv2 /= 2;
    for(int i = 1; i < blocks - 1; i++) {
        sumDiv2 += function(lower + interval * i / blocks);
    }
    for(int i = 0; i < blocks - 1; i++) {
        sumDiv2 += 2 * function(lower + interval * (i + 0.5) / blocks);
    }
    return (interval / blocks) * sumDiv2 / 3;
}

// You have to pass in a random number generator function, taking void returning double between 0 and 1.
// Will generate a random point in the box enclosed by left right, upper lower
// The x value of the point will be input into the function. If the value returned is greater
// then area is included (point is under the curve). If the real value is less, then not included.
// Returns box area * included / total
double monteCarlo(double left, double right, double lower, double upper, double(function)(double), double(rng)(void), unsigned long long points) {
    double width = right - left;
    double height = upper - lower;
    unsigned long long total = points;
    unsigned long long under = 0;
    while(points-- != 0) {
        double x = left + width * rng();
        double y = lower + height * rng();
        double realY = function(x);
        if(y <= realY) under++;
    }
    return width * height * ((double) under / total);
}

// Same as monteCarlo but there is an upper curve and a lower curve.
// The random point will only be counted if it is below the upper curve and above the lower curve.
double monteCarloWithin(double left, double right, double lower, double upper, double(upperCurve)(double), double(lowerCurve)(double), double(rng)(void), unsigned long long points) {
    double width = right - left;
    double height = upper - lower;
    unsigned long long total = points;
    unsigned long long within = 0;
    while(points-- != 0) {
        double x = left + width * rng();
        double y = lower + height * rng();
        double upperY = upperCurve(x);
        double lowerY = lowerCurve(x);
        if(y <= upperY && y >= lowerY) within++;
    }
    return width * height * ((double) within / total);
}

// Same as regular monteCarlo, but you pass in a custom evaluator function.
// The function will be passed the x and y coordinate, and the function should
// return 0 if it is not included or 1 if it is included.
double monteCarloCustom(double left, double right, double lower, double upper, int(evaluator)(double, double), double(rng)(void), unsigned long long points) {
    double width = right - left;
    double height = upper - lower;
    unsigned long long total = points;
    unsigned long long included = 0;
    while(points-- != 0) {
        double x = left + width * rng();
        double y = lower + height * rng();
        if(evaluator(x, y)) included++;
    }
    return width * height * ((double) included / total);
}