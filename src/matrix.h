#ifndef MATRIX
#define MATRIX

typedef struct Vector {
    int size;
    double* elements;
} Vector;

// [ 1, 2 ]
// [ 3, 4 ] => double[ 1, 2, 3, 4 ]
typedef struct Matrix {
    int rows;
    int columns;
    double* elements;
} Matrix;

void printVector(Vector* vector);
void printMatrix(Matrix* matrix);

Vector createVector(int size);
Matrix createMatrix(int rows, int columns);
void deleteVector(Vector* vector);
void deleteMatrix(Matrix* matrix);

double* addressAt(Matrix* matrix, int row, int column);
double* rowAt(Matrix* matrix, int row);

void scalarProduct(double multiply, Vector* vector);
void scalarDivide(double divide,  Vector* vector);
void scalarProductArray(double multiply, double* array, int count);
void scalarProductArray(double divide, double* array, int count);
double length(Vector* vector);
double dotProduct(Vector* first, Vector* second);
double dotProductArrays(double* first, double* second, int size);
double dotProductColumn(Matrix* matrix, int column, Vector* vector);
double dotProductColumnArray(Matrix* matrix, int column, double* array);
void addArrays(double* array1, double* array2, int size);
void subtractArrays(double* array1, double* array2, int size);
void swapArrays(double* array1, double* array2, int size);
void copyArrays(double* array, double* result, int size);

void mvProduct(Matrix* matrix, Vector* vector, Vector* result);
void mmProduct(Matrix* first, Matrix* second, Matrix* result);

void inverse(Matrix* square, Matrix* result);
void identify(Matrix* square);
void transpose(Matrix* matrix, Matrix* result);

#endif