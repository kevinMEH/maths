#ifndef INTEGRATE
#define INTEGRATE

double midpoint(double lower, double upper, int blocks, double(function)(double));
double trapezoidal(double lower, double upper, int blocks, double(function)(double));
double simpson13(double lower, double upper, int blocks, double(function)(double));

#endif