#include <math.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#include "trace.h"
#include "basic_structures.h"
#include "polynomial.h"
#include "interpolate.h"
#include "roots.h"

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


double bvpHelperDerivativeVariable;
double bvpHelperStepSize;
double(*bvpHelperSecondDerivative)(double, double, double);
double bvpHelperDerivative(double x, double y) {
    double oldDerivative = bvpHelperDerivativeVariable;
    bvpHelperDerivativeVariable += bvpHelperStepSize * bvpHelperSecondDerivative(x, y, bvpHelperDerivativeVariable);
    return oldDerivative;
}

extern Polynomial* storedPolynomial;
Polynomial* storedPolynomial2;
double storedPolynomialEvaluate2(double x) {
    return polynomialEvaluate(storedPolynomial2, x);
}


// Boundary value problem solver:
// Given start and ending values, and the second derivative, finds the inital
// slope such that we will reach the end value within the tolerance allowed
// 
// MAKE SURE TO CHECK AFTERWARDS THE VALUE RETURNED!!! IT MAY NOT BE THE DESIRED
// VALUE IF THE FUNCTION RETURNS EARLY AFTER REACHING MAX INTERPOLATING STEPS.
// Too many steps is bad because it may mess up interpolating. Use another
// algorithm if this fails, or perhaps different starting points. (Not 0 and 1)
double eulerShootInterpolate(double start, double startValue, double end, double endValue,
double(secondDerivative)(double, double, double), int eulerSteps, int secantSteps,
double tolerance, int maxInterpolatingSteps) {
    bvpHelperSecondDerivative = secondDerivative;
    double stepSize = (end - start) / eulerSteps;
    bvpHelperStepSize = stepSize;
    bvpHelperDerivativeVariable = 0;
    double endValueSlopeZero = euler(start, startValue, bvpHelperDerivative, end, eulerSteps);
    bvpHelperDerivativeVariable = 1;
    double endValueSlopeOne = euler(start, startValue, bvpHelperDerivative, end, eulerSteps);
    
    maxInterpolatingSteps -= 1;

    Point* points = (Point*) malloc(sizeof(Point) * maxInterpolatingSteps);
    points[0] = (Point) { 0, endValueSlopeZero };
    points[1] = (Point) { 1, endValueSlopeOne };
    int numPoints = 2;

    // Polynomial of slope vs endValue
    Polynomial interpolate = createPolynomial(maxInterpolatingSteps);
    storedPolynomial = &interpolate;
    Polynomial interpolateDerivative = createPolynomial(maxInterpolatingSteps - 1);
    storedPolynomial2 = &interpolateDerivative;

    // y = v0 + (v1 - v0) x
    // x = (y - a0) / (a1 - a0)
    double lastGuess = (endValue - endValueSlopeZero) / (endValueSlopeOne - endValueSlopeZero);

    while(--maxInterpolatingSteps > 0) {
        lagrange(points, numPoints, &interpolate);
        // Secant finds the zero point, so will have to subtract desired endValue
        Term subtractEndValue = { -endValue, 0 };
        addTermToPolynomial(&interpolate, &subtractEndValue);
        derivativePolynomial(&interpolate, &interpolateDerivative);
        
        double predictedSlope = newtons(storedPolynomialEvaluate, storedPolynomialEvaluate2, lastGuess, secantSteps);
        
        bvpHelperDerivativeVariable = lastGuess = predictedSlope;
        double endValuePredictedSlope = euler(start, startValue, bvpHelperDerivative, end, eulerSteps);
        if(fabs(endValuePredictedSlope - endValue) < tolerance) {
            deletePolynomial(&interpolate);
            deletePolynomial(&interpolateDerivative);
            free(points);
            return predictedSlope;
        }
        // Clear polynomial as required by lagrange
        memset(interpolate.terms, 0, sizeof(Term) * numPoints);
        points[numPoints++] = (Point) { predictedSlope, endValuePredictedSlope };
    }
    lagrange(points, numPoints, &interpolate);
    Term subtractEndValue = { -endValue, 0 };
    addTermToPolynomial(&interpolate, &subtractEndValue);

    double finalPredictedSlope = newtons(storedPolynomialEvaluate, storedPolynomialEvaluate2, lastGuess, secantSteps);

    deletePolynomial(&interpolate);
    deletePolynomial(&interpolateDerivative);
    free(points);
    return finalPredictedSlope;
}