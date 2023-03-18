#include "integrate.h"

double trapezoidal(double lower, double upper, int blocks, double(function)(double)) {
    double interval = upper - lower;
    double sumDiv2 = function(lower) + function(upper);
    sumDiv2 /= 2;
    for(int i = 1; i < blocks; i++) {
        // We do interval * (i / blocks) instead of stepSize * i for
        // precision reasons. (where stepSize = (upper - lower)/blocks,
        // stepSize being constant will lose percision due to rounding.)
        sumDiv2 += function(lower + interval * (i / blocks));
    }
    return interval * sumDiv2 / blocks;
}