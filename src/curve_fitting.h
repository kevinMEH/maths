#ifndef CURVE_FITTING
#define CURVE_FITTING

#include "matrix.h"
#include "polynomial.h"
#include "basic_structures.h"

void leastSquaresPolynomial(Point* points, int numPoints, int degree, Vector results);

#endif