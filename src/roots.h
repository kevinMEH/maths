#ifndef ROOTS
#define ROOTS

int findIterations(double(rootFinder)(int), double realValue, double tolerance);
double bisection(double(operation)(double), double start, double end, int iterations);
double newtons(double(operation)(double), double(derivative)(double), double estimate, int iterations);
double fnewtons(double(combinedOperation)(double), double estimate, int iterations);
double secant(double(operation)(double), double first, double second, int iterations);
double fixedPoint(double(operation)(double), double estimate, int iterations);

#endif