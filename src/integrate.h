#ifndef INTEGRATE
#define INTEGRATE

double midpoint(double lower, double upper, int blocks, double(function)(double));
double trapezoidal(double lower, double upper, int blocks, double(function)(double));
double simpson13(double lower, double upper, int blocks, double(function)(double));
double monteCarlo(double left, double right, double lower, double upper, double(function)(double), double(rng)(void), unsigned long long points);
double monteCarloWithin(double left, double right, double lower, double upper, double(upperCurve)(double), double(lowerCurve)(double), double(rng)(void), unsigned long long points);
double monteCarloCustom(double left, double right, double lower, double upper, int(evaluator)(double, double), double(rng)(void), unsigned long long points);

#endif