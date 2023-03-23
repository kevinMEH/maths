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
double dotProduct(Vector*__restrict first, Vector*__restrict second);
double dotProductArrays(double* first, double* second, int size);
double dotProductColumn(Matrix*__restrict matrix, int column, Vector*__restrict vector);
double dotProductColumnArray(Matrix*__restrict matrix, const int column, double*__restrict array);
void addArrays(double* array1, double* array2, int size);
void subtractArrays(double* array1, double* array2, int size);
void swapArrays(double* array1, double* array2, int size);
void copyArrays(double*__restrict array, double*__restrict result, int size);

void vvAdd(Vector* first, Vector* second, Vector* result);
void vvSubtract(Vector* first, Vector* second, Vector* result);
void vvMultiply(Vector* first, Vector* second, Vector* result);
void mvProduct(Matrix*__restrict matrix, Vector*__restrict vector, Vector*__restrict result);
void mvDiagMultiply(Matrix* matrix, Vector* vector, Vector* result);
void mmAdd(Matrix* first, Matrix* second, Matrix* result);
void mmSubtract(Matrix* first, Matrix* second, Matrix* result);
void mmProduct(Matrix*__restrict first, Matrix*__restrict second, Matrix*__restrict result);
void mmStrassen(Matrix* first, Matrix* second, Matrix* result, int depth, int limit);
void mmDiagMultiply(Matrix* first, Matrix* second, Matrix* result);

void inverse(Matrix*__restrict square, Matrix*__restrict result);
void identify(Matrix* square);
void transpose(Matrix*__restrict matrix, Matrix*__restrict result);
void extractDiagonals(Matrix*__restrict target, Matrix*__restrict result);
void extractDiagonalsToVector(Matrix*__restrict target, Vector*__restrict result);

#endif