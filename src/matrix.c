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

inline double valueAt(Matrix* matrix, int row, int column) {
    return matrix->elements[row * matrix->columns + column];
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
// Vectors may not refer to the same element. Use dotSelf if they are the same.
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
// Matrix and array should not overlap.
double dotProductColumnArray(Matrix* matrix, const int column, double* array) {
    double sum = 0.0;
    const int rows = matrix->rows, columns = matrix->columns;
    int j = column;
    const double* elements = matrix->elements;
    for(int i = 0; i < rows; i++) {
        sum += array[i] * elements[j];
        j += columns;
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
// Arrays may not overlap.
void copyArrays(double*__restrict array, double*__restrict result, int size) {
    for(int i = 0; i < size; i++) {
        result[i] = array[i];
    }
}



// Size of all should be the same.
// Result can be one of the operands.
// All elements of result will be replaced.
void vvAdd(Vector* first, Vector* second, Vector* result) {
    int size = result->size;
    double* firstArray = first->elements;
    double* secondArray = second->elements;
    double* resultArray = result->elements;
    for(int i = 0; i < size; i++) {
        resultArray[i] = firstArray[i] + secondArray[i];
    }
}

// Size of all should be the same.
// Result can be one of the operands.
// All elements of result will be replaced.
void vvSubtract(Vector* first, Vector* second, Vector* result) {
    int size = result->size;
    double* firstArray = first->elements;
    double* secondArray = second->elements;
    double* resultArray = result->elements;
    for(int i = 0; i < size; i++) {
        resultArray[i] = firstArray[i] - secondArray[i];
    }
}

// Single elementwise multiply.
// Size of all should be the same.
// Result is allowed to be one of the operands.
void vvMultiply(Vector* first, Vector* second, Vector* result) {
    int size = result->size;
    double* firstArray = first->elements;
    double* secondArray = second->elements;
    double* resultArray = result->elements;
    for(int i = 0; i < size; i++) {
        resultArray[i] = firstArray[i] * secondArray[i];
    }
}

// Size of vector must be equal to columns of matrix
// Size of result must be equal to rows of matrix
void mvProduct(Matrix* matrix, Vector* vector, Vector* result) {
    const int columns = matrix->columns;
    double* vectorArray = vector->elements;
    for(int i = 0; i < matrix->rows; i++) {
        result->elements[i] = dotProductArrays(rowAt(matrix, i), vectorArray, columns);
    }
}

// Multiply each element in vector with the corresponding diagonal element in matrix.
// Useful when multiplying with diagonal matrix.
// Matrix should be square, or at least rows bigger than column.
// Size of vector must be equal to column of matrix
// Size of result must be equal to size of input vector.
// Result is allowed to be the input vector.
void mvDiagMultiply(Matrix* matrix, Vector* vector, Vector* result) {
    int columns = matrix->columns;
    double* vectorArray = vector->elements;
    double* resultArray = result->elements;
    for(int i = 0; i < columns; i++) {
        resultArray[i] = matrix->elements[i * columns + i] * vectorArray[i];
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
// operands may not be the same. If they are, but are diagonal matrices, use mmDiagMultiply
// If they are not diagonal matrices, copy and multiply.
void mmProduct(Matrix* first, Matrix* second, Matrix* result) {
    const int rows = result->rows;
    const int columns = result->columns;
    const int size = rows * columns;
    const int firstColumns = first->columns;
    for(int i = 0; i < size; i++) {
        result->elements[i] = 0.0;
    }
    for(int i = 0; i < rows; i++) {
        double* row = &(first->elements[i * firstColumns]);
        for(int k = 0; k < firstColumns; k++) {
            for(int j = 0; j < columns; j++) {
                result->elements[i * columns + j] += row[k] * second->elements[k * columns + j];
            }
        }
    }
}

// Strassen matrix multiplication
// Matrices must be same size and square.
// Will keep using Strassen until depth is 0 or until size is less than limit, until
// which it will use regular matrix multiplication. Set to -1 to prevent it.
// However, it is recommended to set limit to something like 4 or else excessive
// callocs will be made.
// Width of first must equal height of second
// Height of result must equal height of first
// Width of result must equal width of second
// All in bound elements in result will be replaced. Operands will be untouched.
void mmStrassen(Matrix* first, Matrix* second, Matrix* result, int depth, int limit) {
    int size = first->columns;
    if(size == 1) {
        result->elements[0] = first->elements[0] * second->elements[0];
        return;
    }
    if(size < limit || depth == 0) { // Size less tham limit or depth 0, use regular multiplication
        mmProduct(first, second, result);
        return;
    }
    --depth;
    int half = size / 2;
    int odd = size % 2 == 1;
    if(odd) half += 1; // If odd, add 1 to half. The last row / column will be 0 padded.
    // TODO: Allocate single block, pass in block as param. 17 * half * half + 7 * 17 * half/2 * half/2 + 49 * 17 * half/2/2 * half/2/2 ...
    double* block = (double*) calloc(17 * half * half, sizeof(double));
    Matrix tempFirst = { half, half, block };
    Matrix tempSecond = { half, half, &(block[half * half]) };
    Matrix a11 = { half, half, &(block[2 * half * half]) };
    Matrix a12 = { half, half, &(block[3 * half * half]) };
    Matrix a21 = { half, half, &(block[4 * half * half]) };
    Matrix a22 = { half, half, &(block[5 * half * half]) };
    Matrix b11 = { half, half, &(block[6 * half * half]) };
    Matrix b12 = { half, half, &(block[7 * half * half]) };
    Matrix b21 = { half, half, &(block[8 * half * half]) };
    Matrix b22 = { half, half, &(block[9 * half * half]) };
    Matrix m1 = { half, half, &(block[10 * half * half]) };
    Matrix m2 = { half, half, &(block[11 * half * half]) };
    Matrix m3 = { half, half, &(block[12 * half * half]) };
    Matrix m4 = { half, half, &(block[13 * half * half]) };
    Matrix m5 = { half, half, &(block[14 * half * half]) };
    Matrix m6 = { half, half, &(block[15 * half * half]) };
    Matrix m7 = { half, half, &(block[16 * half * half]) };
    
    // If we padded split arrays, we must use a different algorithm for copying elements
    // over because half + half - 1 is out of bounds in the original arrays. So we will
    // only copy from 0 to half - 2 (so max half + half - 2, not oob for original arrays)
    // for the split arrays and then fill out the other elements in row half - 1 in a11,
    // a12 and elements in column half - 1 in a11, a21 separately.
    if(odd) {
        for(int i = 0; i < half - 1; i++) {
            for(int j = 0; j < half - 1; j++) { // Everything except cross
                *addressAt(&a11, i, j) = *addressAt(first, i, j);
                *addressAt(&a12, i, j) = *addressAt(first, i, j + half);
                *addressAt(&a21, i, j) = *addressAt(first, i + half, j);
                *addressAt(&a22, i, j) = *addressAt(first, i + half, j + half);

                *addressAt(&b11, i, j) = *addressAt(second, i, j);
                *addressAt(&b12, i, j) = *addressAt(second, i, j + half);
                *addressAt(&b21, i, j) = *addressAt(second, i + half, j);
                *addressAt(&b22, i, j) = *addressAt(second, i + half, j + half);
            }
            // Vertical
            *addressAt(&a11, i, half - 1) = *addressAt(first, i, half - 1);
            *addressAt(&a21, i, half - 1) = *addressAt(first, i + half, half - 1);

            *addressAt(&b11, i, half - 1) = *addressAt(second, i, half - 1);
            *addressAt(&b21, i, half - 1) = *addressAt(second, i + half, half - 1);

            // Horizontal
            *addressAt(&a11, half - 1, i) = *addressAt(first, half - 1, i);
            *addressAt(&a12, half - 1, i) = *addressAt(first, half - 1, i + half);

            *addressAt(&b11, half - 1, i) = *addressAt(second, half - 1, i);
            *addressAt(&b12, half - 1, i) = *addressAt(second, half - 1, i + half);
        }
        // Center
        *addressAt(&a11, half - 1, half - 1) = *addressAt(first, half - 1, half - 1);
        *addressAt(&b11, half - 1, half - 1) = *addressAt(second, half - 1, half - 1);
    } else {
        for(int i = 0; i < half; i++) {
            for(int j = 0; j < half; j++) {
                *addressAt(&a11, i, j) = *addressAt(first, i, j);
                *addressAt(&a12, i, j) = *addressAt(first, i, j + half);
                *addressAt(&a21, i, j) = *addressAt(first, i + half, j);
                *addressAt(&a22, i, j) = *addressAt(first, i + half, j + half);

                *addressAt(&b11, i, j) = *addressAt(second, i, j);
                *addressAt(&b12, i, j) = *addressAt(second, i, j + half);
                *addressAt(&b21, i, j) = *addressAt(second, i + half, j);
                *addressAt(&b22, i, j) = *addressAt(second, i + half, j + half);
            }
        }
    }

    mmAdd(&a11, &a22, &tempFirst);
    mmAdd(&b11, &b22, &tempSecond);
    mmStrassen(&tempFirst, &tempSecond, &m1, depth, limit);

    mmAdd(&a21, &a22, &tempFirst);
    mmStrassen(&tempFirst, &b11, &m2, depth, limit);

    mmSubtract(&b12, &b22, &tempFirst);
    mmStrassen(&a11, &tempFirst, &m3, depth, limit);
    
    mmSubtract(&b21, &b11, &tempFirst);
    mmStrassen(&a22, &tempFirst, &m4, depth, limit);
    
    mmAdd(&a11, &a12, &tempFirst);
    mmStrassen(&tempFirst, &b22, &m5, depth, limit);
    
    mmSubtract(&a21, &a11, &tempFirst);
    mmAdd(&b11, &b12, &tempSecond);
    mmStrassen(&tempFirst, &tempSecond, &m6, depth, limit);
    
    mmSubtract(&a12, &a22, &tempFirst);
    mmAdd(&b21, &b22, &tempSecond);
    mmStrassen(&tempFirst, &tempSecond, &m7, depth, limit);
    
    // Recombine, a is useless so a = c
    mmAdd(&m1, &m4, &a11);
    mmSubtract(&a11, &m5, &a11);
    mmAdd(&a11, &m7, &a11);
    
    mmAdd(&m3, &m5, &a12);

    mmAdd(&m2, &m4, &a21);
    
    mmSubtract(&m1, &m2, &a22);
    mmAdd(&a22, &m3, &a22);
    mmAdd(&a22, &m6, &a22);
    
    // Copy
    if(odd) {
        for(int i = 0; i < half - 1; i++) {
            for(int j = 0; j < half - 1; j++) { // Everything except cross
                *addressAt(result, i, j) = *addressAt(&a11, i, j);
                *addressAt(result, i, j + half) = *addressAt(&a12, i, j);
                *addressAt(result, i + half, j) = *addressAt(&a21, i, j);
                *addressAt(result, i + half, j + half) = *addressAt(&a22, i, j);
            }
            // Vertical
            *addressAt(result, i, half - 1) = *addressAt(&a11, i, half - 1);
            *addressAt(result, i + half, half - 1) = *addressAt(&a21, i, half - 1);
            // Horizontal
            *addressAt(result, half - 1, i) = *addressAt(&a11, half - 1, i);
            *addressAt(result, half - 1, i + half) = *addressAt(&a12, half - 1, i);
        }
        // Center
        *addressAt(result, half - 1, half - 1) = *addressAt(&a11, half - 1, half - 1);
    } else {
        for(int i = 0; i < half; i++) {
            for(int j = 0; j < half; j++) {
                *addressAt(result, i, j) = *addressAt(&a11, i, j);
                *addressAt(result, i, j + half) = *addressAt(&a12, i, j);
                *addressAt(result, i + half, j) = *addressAt(&a21, i, j);
                *addressAt(result, i + half, j + half) = *addressAt(&a22, i, j);
            }
        }
    }
    free(block);
}

// All matrices should be square and the same size.
// Multiplies each element in the diagonal of the first with the corresponding element
// in the diagonal of the second, and stores in the corresponding diagonal in result.
// Useful for multiplying diagonalized matrices.
// Result is allowed to be one of the operands.
// Only diagonal elements of result will be filled.
void mmDiagMultiply(Matrix* first, Matrix* second, Matrix* result) {
    int columns = result->columns;
    double* firstElements = first->elements;
    double* secondElements = second->elements;
    double* resultElements = result->elements;
    for(int i = 0; i < columns; i++) {
        resultElements[i * columns + i] = firstElements[i * columns + i] + secondElements[i * columns + i];
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
        if(currentRow[i] == 0) { // TODO: Can we do this to check for 0s?
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

// Solves a matrix using the output values for the input values.
// Turns the input square matrix into identity!!!
// Matrix must be invertible or else it may not be solved properly.
// Output will contain the inputs after the operation.
void gaussEliminate(Matrix* square, Vector* outputs) {
    int width = square->columns;
    double temp[width];
    
    double* outputArray = outputs->elements;
    
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
                // Copy selected upper row into temp array and multiply by factor.
                // Upper row will already be triangular matrix, so only need to copy from j till end
                for(int k = j; k < width; k++) {
                    temp[k] = factor * upperRow[k];
                }
                subtractArrays(&currentRow[j], &temp[j], width - j);
                
                // Subtract corresponding element from output
                outputArray[i] -= factor * outputArray[j];
            }
            temp[j] = 0; // Only set current first element to 0. During the next iteration others behind will be overwritten.
        }
        // For diagonal element, check if zero. If zero, oversimplified, move to appropriate row and redo.
        // Since we know the matrix is invertible, we are guaranteed to find/compute a non zero eventually.
        if(currentRow[i] == 0) { // TODO: Can we do this to check for 0s?
            int j = i;
            while(currentRow[++j] == 0); // Find proper location, keep searching until nonzero.
            swapArrays(currentRow, rowAt(square, j), width);
            double temp = outputArray[i];
            outputArray[i] = outputArray[j];
            outputArray[j] = temp;
            goto reduce;
        }
        // Else, if not zero, normalize current row
        double factor = currentRow[i];
        scalarDivideArray(factor, &currentRow[i], width - i);
        outputArray[i] = outputArray[i] / factor;
    }
    // Reduce triangular matrix from bottom right
    for(int i = width - 2; i >= 0; i--) { // Start from second to last row
        double* currentRow = rowAt(square, i);
        for(int j = width - 1; j > i; j--) { // Start from last column to before diagonal element
            double factor = currentRow[j];
            currentRow[j] = 0;
            
            outputArray[i] -= factor * outputArray[j];
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

// Copies the diagonals from target into result, and set to 0.
// Both matrices should be square matrices of the same size.
// Only the diagonal elements of result will be replaced.
void extractDiagonals(Matrix* target, Matrix* result) {
    int columns = result->columns;
    double* targetElements = target->elements;
    double* resultElements = result->elements;
    for(int i = 0; i < columns; i++) {
        resultElements[i * columns + i] = targetElements[i * columns + i];
        targetElements[i * columns + i] = 0;
    }
}

// Copies the diagonals from target into result, and set to 0.
// Target should be a square matrix with width and height same as result's size
// All elements in result replaced
void extractDiagonalsToVector(Matrix* target, Vector* result) {
    int columns = result->size;
    double* targetElements = target->elements;
    double* resultElements = result->elements;
    for(int i = 0; i < columns; i++) {
        resultElements[i] = targetElements[i * columns + i];
        targetElements[i * columns + i] = 0;
    }
}

// Copies the diagonals from target into result, and set to 0.
// Target should be a square matrix with width equal to result's length
// All elements in result replaced
void extractDiagonalsToArray(Matrix* target, double* result) {
    int columns = target->columns;
    double* targetElements = target->elements;
    for(int i = 0; i < columns; i++) {
        result[i] = targetElements[i + i * columns];
        targetElements[i + i * columns] = 0;
    }
}