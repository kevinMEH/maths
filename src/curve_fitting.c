#include <math.h>
#include "basic_structures.h"
#include "matrix.h"
#include "curve_fitting.h"

void leastSquaresPolynomial(Point* points, int numPoints, int degree, Vector results) {
    int polynomialLength = degree + 1;
    double mainMatrixArray[numPoints * polynomialLength];
    Matrix mainMatrix = { numPoints, polynomialLength, mainMatrixArray };

    double bArray[numPoints];
    Vector b = { numPoints, bArray };

    for(int i = 0; i < numPoints; i++) {
        Point point = points[i];
        b.elements[i] = point.y;
        for(int j = 0; j < polynomialLength; j++) {
            *addressAt(&mainMatrix, i, j) = pow(point.x, j);
        }
    }

    double transposedMatrixArray[numPoints * polynomialLength];
    Matrix transposedMatrix = { polynomialLength, numPoints, transposedMatrixArray };
    transpose(&mainMatrix, &transposedMatrix);

    // A^T b - A^T A x_ = 0
    // A^T b = A^T A x_
    double matrixProductArray[polynomialLength * polynomialLength];
    Matrix matrixProduct = { polynomialLength, polynomialLength, matrixProductArray };
    mmProduct(&transposedMatrix, &mainMatrix, &matrixProduct);

    double inversedProductArray[polynomialLength * polynomialLength];
    Matrix inversedProduct = { polynomialLength, polynomialLength, inversedProductArray };
    inverse(&matrixProduct, &inversedProduct); // (A^T A)^-1

    double transposedTimesBArray[polynomialLength];
    Vector transposedTimesB = { polynomialLength, transposedTimesBArray };
    mvProduct(&transposedMatrix, &b, &transposedTimesB); // A^T b
    
    mvProduct(&inversedProduct, &transposedTimesB, &results); // (A^T A)^-1 (A^T) b = x_
}