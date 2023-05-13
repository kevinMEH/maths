#include <math.h>
#include "basic_structures.h"
#include "trace.h"

// Preferably: Use powers of 2 for step count to reach end correctly
double euler(double start, double startValue, double(derivative)(double, double), double end, int steps) {
    double stepSize = (end - start) / steps;
    for(int count = 0; count < steps; count++) {
        start += stepSize;
        startValue += stepSize * derivative(start, startValue);
    }
    return startValue;
}

/**
 * Modification of euler() to capture intermediate value pairs.
 * 
 * saveArray should be sufficiently large to store steps / interval elements.
 * 
 * Interval specifies the number of steps to before saving another element into
 * the array. Values will be saved before steps are performed.
 * 
 * The first step will always be the first one to be saved.
*/
double eulerSaveIntermediate(double start, double startValue,
double(derivative)(double, double),double end, int steps,
Pair* saveArray, int interval) {
    double stepSize = (end - start) / steps;
    int saveArrayCounter = 0;
    for(int count = 0; count < steps; count++) {
        if(count % interval == 0) {
            saveArray[saveArrayCounter].first = start;
            saveArray[saveArrayCounter].second = startValue;
            saveArrayCounter++;
        }
        start += stepSize;
        startValue += stepSize * derivative(start, startValue);
    }
    return startValue;
}

double eulerLength(double start, double startValue, double(derivative)(double, double), double end, int steps) {
    double length = 0.0;
    double stepSize = (end - start) / steps;
    double stepSizeSquared = stepSize * stepSize;
    for(int count = 0; count < steps; count++) {
        start += stepSize;
        double increment = stepSize * derivative(start, startValue);
        startValue += increment;
        length += sqrt(stepSizeSquared + increment * increment);
    }
    return length;
}

double rungeKutta4(double start, double startValue, double(derivative)(double, double), double end, int steps) {
    double stepSize = (end - start) / steps;
    double halfStepSize = stepSize / 2;
    for(int count = 0; count < steps; count++) {
        double k1 = derivative(start, startValue);
        double k2 = derivative(start + halfStepSize, startValue + halfStepSize * k1);
        double k3 = derivative(start + halfStepSize, startValue + halfStepSize * k2);
        start += stepSize;
        double k4 = derivative(start, startValue + stepSize * k3);
        startValue += stepSize * ((k1 + 2 * k2 + 2 * k3 + k4) / 6);
    }
    return startValue;
}