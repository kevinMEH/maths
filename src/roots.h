#ifndef ROOTS
#define ROOTS

#include "matrix.h"

int findIterations(double(rootFinder)(int), double realValue, double tolerance);
double bisection(double(operation)(double), double start, double end, int iterations);
double newtons(double(operation)(double), double(derivative)(double), double estimate, int iterations);
double fnewtons(double(combinedOperation)(double), double estimate, int iterations);
double secant(double(operation)(double), double first, double second, int iterations);
double fixedPoint(double(operation)(double), double estimate, int iterations);

void jacobiIteration(Matrix* matrix, Vector* solution, Vector* estimates, int iterations);
void gaussSeidelIteration(Matrix* matrix, Vector* solution, Vector* estimates, int iterations);
void successiveOverRelaxation(Matrix* matrix, Vector* solution, Vector* estimates, double relaxationFactor, int iterations);

double eigenIteration(Matrix* matrix, Vector* guess, int iterations);

#endif