#include <stdio.h>
#include "../src/matrix.h"

int main() {
    double array1[] = {
        1.0, 2.0,
        2.0, 6.0,
        -9.0, 5.0
    };
    Matrix matrix1 = {
        3, 2, array1
    };
    
    double array2[] = {
        4.0, 5.0, 6.0,
        1.0, -1.0, 4.0,
    };
    Matrix matrix2 = {
        2, 3, array2
    };
    
    Matrix result = createMatrix(3, 3);
    mmProduct(&matrix1, &matrix2, &result);
    *addressAt(&result, 2, 0) = -30;

    double toInvertArray[] = {
        13, 8, 9, 0,
        0, 0, 14, 7,
        13, 8, 9, 1,
        66, -2, -2, 4
    };
    Matrix toInvert = {
        4, 4, toInvertArray
    };
    Matrix inverseResult = createMatrix(4, 4);
    inverse(&toInvert, &inverseResult);

    inverseResult.rows = 2;
    inverseResult.columns = 8;
    printMatrix(&inverseResult);
    
    Matrix transposeMatrix = createMatrix(8, 2);
    transpose(&inverseResult, &transposeMatrix);
    
    Matrix doubleTransposed = createMatrix(2, 8);
    transpose(&transposeMatrix, &doubleTransposed);
    printMatrix(&doubleTransposed);
    return 0;
}