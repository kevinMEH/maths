#include <stdio.h>
#include <math.h>
#include "roots.h"

// Slow, a helper function for testing to find the number of iterations needed to find roots within a tolerance.
// The rootFinder function takes a single argument which represents the number of iterations to perform.
// It should return the estimated x value. All other parameters should be filled for it.
int findIterations(double(rootFinder)(int), double realValue, double tolerance) {
    int iterations = 1;
    double difference = 999;
    while(difference > tolerance) {
        difference = rootFinder(iterations++) - realValue;
        if(difference < 0) difference = -difference;
    }
    return iterations;
}

// Start value and value MUST have opposite signs.
// The operation parameter should be a function pointer representing the equation
// taking 1 double as a parameter.
double bisection(double(operation)(double), double start, double end, int iterations) {
    while(iterations-- != 0) {
        double startValue = operation(start);
        double midpoint = (start + end) / 2;
        double midpointValue = operation(midpoint);
        if(midpointValue > 0) {
            if(startValue > 0) {
                start = midpoint;
            } else {
                end = midpoint;
            }
        } else {
            if(startValue < 0) {
                start = midpoint;
            } else {
                end = midpoint;
            }
        }
    }
    return (start + end) / 2;
}

double newtons(double(operation)(double), double(derivative)(double), double estimate, int iterations) {
    while(iterations-- != 0) {
        estimate = estimate - operation(estimate) / derivative(estimate);
    }
    return estimate;
}

// Fast Newtons: f(x) / f'(x) can sometimes be simplified and put into
// a single combinedOperation, which is then passed into this function.
double fnewtons(double(combinedOperation)(double), double estimate, int iterations) {
    while(iterations-- != 0) {
        estimate = estimate - combinedOperation(estimate);
    }
    return estimate;
}

double secant(double(operation)(double), double old, double current, int iterations) {
    while(iterations-- != 0) {
        double currentValue = operation(current);
        double rise = (currentValue - operation(old));
        double prev = current;
        current = current - (current - old) * currentValue / rise;
        // x - run * f(x) / rise == x - f(x) / (rise / run)
        // Multiplication is faster than division.
        old = prev;
    }
    return current;
}

double fixedPoint(double(operation)(double), double estimate, int iterations) {
    while(iterations-- != 0) {
        estimate = operation(estimate);
    }
    return estimate;
}



// Jacobi iteration to find the set of values when input into the matrix gives the solutions.
// The result will be stored in the estimate vector.
// Matrix must be square. Solution, estimate, and result must match width/height of matrix.
void jacobiIteration(Matrix* matrix, Vector* solution, Vector* estimate, int iterations) {
    int columns = matrix->columns;
    double diagonalElements[columns];
    Vector diagonal = { columns, diagonalElements }; // Diagonal matrix as vector to save space
    double tempElements[columns];
    Vector temp = { columns, tempElements };
    extractDiagonalsToVector(matrix, &diagonal);
    for(int i = 0; i < columns; i++) {
        diagonal.elements[i] = 1 / diagonal.elements[i];
    }
    
    while(iterations-- != 0) {
        mvProduct(matrix, estimate, &temp);
        vvSubtract(solution, &temp, &temp);
        vvMultiply(&diagonal, &temp, estimate);
    }
}