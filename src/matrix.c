#include <math.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

void printVector(Vector* vector) {
    printf("[\t");
    for(int i = 0; i < vector->size; i++) {
        printf("%lf\t", vector->elements[i]);
    }
    printf("]\n");
}

void printMatrix(Matrix* matrix) {
    printf("[");
    for(int i = 0; i < matrix->rows; i++) {
        printf("\t");
        for(int j = 0; j < matrix->columns; j++) {
            printf("%lf\t", *addressAt(matrix, i, j));
        }
        if(i < matrix->rows - 1) printf("\n");
    }
    printf("]\n");
}

Vector createVector(int size) {
    double* elements = (double*) calloc(size, sizeof(double));
    return (Vector) {
        size, elements
    };
}

Matrix createMatrix(int rows, int columns) {
    double* elements = (double*) calloc(rows * columns, sizeof(double));
    return (Matrix) {
        rows, columns, elements
    };
}

void deleteVector(Vector* vector) {
    free(vector->elements);
}

void deleteMatrix(Matrix* matrix) {
    free(matrix->elements);
}



// row parameter must be a valid row in the matrix given row count starts at 0.
// column parameter must be a valid column in the matrix given column count starts at 0.
inline double* addressAt(Matrix* matrix, int row, int column) {
    return &(matrix->elements[row * matrix->columns + column]);
}

// row parameter must be a valid row in the matrix. Row count starts at 0.
inline double* rowAt(Matrix* matrix, int row) {
    return &(matrix->elements[row * matrix->columns]);
}

void scalarProduct(double multiply, Vector* vector) {
    for(int i = 0; i < vector->size; i++) {
        vector->elements[i] *= multiply;
    }
}

// divisor must not be 0
void scalarDivide(double divide, Vector* vector) {
    for(int i = 0; i < vector->size; i++) {
        vector->elements[i] /= divide;
    }
}

void scalarProductArray(double multiply, double* array, int count) {
    for(int i = 0; i < count; i++) {
        array[i] *= multiply;
    }
}

void scalarDivideArray(double divide, double* array, int count) {
    for(int i = 0; i < count; i++) {
        array[i] /= divide;
    }
}

double dotSelf(Vector* vector) {
    double sum = 0.0;
    for(int i = 0; i < vector->size; i++) {
        sum += vector->elements[i] * vector->elements[i];
    }
    return sum;
}

double length(Vector* vector) {
    return sqrt(dotSelf(vector));
}

// Size of operands must be equal
double dotProduct(Vector* first, Vector* second) {
    double sum = 0.0;
    for(int i = 0; i < first->size; i++) {
        sum += first->elements[i] * second->elements[i];
    }
    return sum;
}

double dotProductArrays(double* first, double* second, int size) {
    double sum = 0.0;
    for(int i = 0; i < size; i++) {
        sum += first[i] * second[i];
    }
    return sum;
}

// [a, 1, b] * [1, 2] = 5
// [c, 2, d]
// column must be describe a valid column in the matrix; ie less than the matrix columns
// column is as if column count starts at 0.
double dotProductColumn(Matrix* matrix, int column, Vector* vector) {
    double sum = 0.0;
    for(int i = column, j = 0; i < matrix->columns * matrix->rows; i += matrix->columns, j++) {
        sum += matrix->elements[i] * vector->elements[j];
    }
    return sum;
}

// [a, 1, b] * [1, 2] = 5
// [c, 2, d]
// column must be describe a valid column in the matrix; ie less than the matrix columns
// column is as if column count starts at 0.
// Size of array is assumed to be the same as the rows of the matrix.
double dotProductColumnArray(Matrix* matrix, int column, double* array) {
    double sum = 0.0;
    for(int i = column, j = 0; i < matrix->columns * matrix->rows; i += matrix->columns, j++) {
        sum += matrix->elements[i] * array[j];
    }
    return sum;
}

// Add elements of array2 to array1
void addArrays(double* array1, double* array2, int size) {
    for(int i = 0; i < size; i++) {
        array1[i] += array2[i];
    }
}

// Subtract elements of array2 to array1
void subtractArrays(double* array1, double* array2, int size) {
    for(int i = 0; i < size; i++) {
        array1[i] -= array2[i];
    }
}

// Swaps elements of arrays
void swapArrays(double* array1, double* array2, int size) {
    for(int i = 0; i < size; i++) {
        double temp = array1[i];
        array1[i] = array2[i];
        array2[i] = temp;
    }
}

// Copy from array into result
void copyArrays(double* array, double* result, int size) {
    for(int i = 0; i < size; i++) {
        result[i] = array[i];
    }
}



// Size of vector must be equal to columns of matrix
// Size of result must be equal to rows of matrix
void mvProduct(Matrix* matrix, Vector* vector, Vector* result) {
    int columns = matrix->columns;
    double* vectorArray = vector->elements;
    for(int i = 0; i < matrix->rows; i++) {
        result->elements[i] = dotProductArrays(rowAt(matrix, i), vectorArray, columns);
    }
}

// Adds the elements of first and second together, and stores in result
// result is safe to be either elements.
// Matrices MUST BE THE SAME SIZE OR INCORRECT ADD OPERATION IS PERFORMED.
// All in bound elements in result will be replaced.
void mmAdd(Matrix* first, Matrix* second, Matrix* result) {
    for(int i = 0; i < first->rows * first->columns; i++) {
        result->elements[i] = first->elements[i] + second->elements[i];
    }
}

// Subtracts the elements of first and second together, and stores in result
// result is safe to be either elements.
// Matrices MUST BE THE SAME SIZE OR INCORRECT ADD OPERATION IS PERFORMED.
// All in bound elements in result will be replaced.
void mmSubtract(Matrix* first, Matrix* second, Matrix* result) {
    for(int i = 0; i < first->rows * first->columns; i++) {
        result->elements[i] = first->elements[i] - second->elements[i];
    }
}

// A1 B2 = C3
// Width of first must equal height of second
// Height of result must equal height of first
// Width of result must equal width of second
// All in bound elements in result will be replaced.
void mmProduct(Matrix* first, Matrix* second, Matrix* result) {
    for(int i = 0; i < result->rows; i++) {
        double* row = rowAt(first, i);
        for(int j = 0; j < result->columns; j++) {
            *addressAt(result, i, j) = dotProductColumnArray(second, j, row);
        }
    }
}

// Inverts a matrix, stores in result.
// TURNS THE INPUT SQUARE MATRIX INTO IDENTITY!!!
// Matrix must be invertible
void inverse(Matrix* square, Matrix* result) {
    int width = square->columns;
    double temp[width];
    double tempResult[width];
    identify(result);
    
    // Make triangular matrix
    for(int i = 0; i < width; i++) {
        reduce:;
        double* currentRow = rowAt(square, i);
        // Simplify first few elements of current row to 0s using upper rows.
        // Only need to simplify from 1st element to element before diagonal element.
        for(int j = 0; j < i; j++) {
            double factor = currentRow[j]; // Corresponding factor on current row
            if(factor != 0) { // If current element not zero, simplify
                double* upperRow = rowAt(square, j);
                // Copy selected upper row into temp array.
                // Upper row will already be triangular matrix, so only need to copy from j till end
                for(int k = j; k < width; k++) {
                    temp[k] = upperRow[k];
                }
                scalarProductArray(factor, &temp[j], width - j); // TODO: Performance check
                subtractArrays(&currentRow[j], &temp[j], width - j); // TODO: Performance check

                copyArrays(rowAt(result, j), tempResult, width);
                scalarProductArray(factor, tempResult, width);
                subtractArrays(rowAt(result, i), tempResult, width);
            }
            temp[j] = 0; // Only set current first element to 0. During the next iteration others behind will be overwritten.
        }
        // For diagonal element, check if zero. If zero, oversimplifed, move to appropriate row and redo.
        // Since we know the matrix is invertible, we are guaranteed to find/compute a non zero eventually.
        if(currentRow[i] == 0) {
            int j = i;
            while(currentRow[++j] == 0); // Find proper location, keep searching until nonzero.
            swapArrays(currentRow, rowAt(square, j), width);
            swapArrays(rowAt(result, i), rowAt(result, j), width);
            goto reduce;
        }
        // Else, if not zero, normalize current row
        double factor = currentRow[i];
        scalarDivideArray(factor, &currentRow[i], width - i);
        scalarDivideArray(factor, rowAt(result, i), width);
    }
    // Reduce triangular matrix from bottom right
    for(int i = width - 2; i >= 0; i--) { // Start from second to last row
        double* currentRow = rowAt(square, i);
        for(int j = width - 1; j > i; j--) { // Start from last column to before diagonal element
            double factor = currentRow[j];
            currentRow[j] = 0; // Same as subtracting by factor * corresponding j simplified row since all rows below simplifed.

            copyArrays(rowAt(result, j), tempResult, width);
            scalarProductArray(factor, tempResult, width);
            subtractArrays(rowAt(result, i), tempResult, width);
        }
    }
}

// Turn into identity matrix. Matrix should be a square matrix.
void identify(Matrix* square) {
    for(int i = 0; i < square->rows * square->columns; i++) {
        square->elements[i] = 0;
    }
    for(int i = 0; i < square->rows * square->columns; i++) {
        square->elements[i] = 1;
        i += square->columns;
    }
}

// Size of matrix must equal to size of result.
// Rows of matrix must equal columns of result.
// Columns of matrix must equal rows of result.
void transpose(Matrix* matrix, Matrix* result) {
    int resultIndex = 0;
    for(int i = 0; i < matrix->columns; i++) {
        for(int j = 0; j < matrix->rows; j++) {
            result->elements[resultIndex++] = *addressAt(matrix, j, i);
        }
    }
}