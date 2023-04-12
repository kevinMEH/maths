#ifndef TRACE
#define TRACE

double euler(double start, double startValue, double(derivative)(double, double), double end, int steps);
double rungeKutta4(double start, double startValue, double(derivative)(double, double), double end, int steps);

#endif