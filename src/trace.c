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