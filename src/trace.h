#ifndef TRACE
#define TRACE

#include "basic_structures.h"

double euler(double start, double startValue,
    double(derivative)(double, double), double end, int steps);

double eulerSaveIntermediate(double start, double startValue,
    double(derivative)(double, double), double end, int steps,
    Pair* saveArray, int interval);

double eulerLength(double start, double startValue,
    double(derivative)(double, double), double end, int steps);

double rungeKutta4(double start, double startValue,
    double(derivative)(double, double), double end, int steps);

double bvpHelperDerivative(double x, double y);

double eulerShootInterpolate(double start, double startValue, double end, double endValue,
double(secondDerivative)(double, double, double), int eulerSteps, int secantSteps,
double tolerance, int maxInterpolatingSteps);

#endif