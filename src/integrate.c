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
    double sum = function(lower) + function(upper);
    for(int i = 1; i < blocks - 1; i++) {
        sum += 2 * function(lower + interval * i / blocks);
    }
    for(int i = 0; i < blocks - 1; i++) {
        sum += 4 * function(lower + interval * (i + 0.5) / blocks);
    }
    return (interval / blocks) * sum / 6;
}