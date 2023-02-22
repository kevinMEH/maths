#include <stdio.h>
#include "../src/interpolate.h"

int main() {
    Point points[] = {
        { 1, 119.77 },
        { 2, 118.85 },
        { 3, 123.22 },
        { 4, 123.45 },
        { 5, 122.44 },
        { 6, 131.49 },
        { 7, 128.78 },
        { 8, 127.17 },
        { 9, 133.42 },
        { 10, 143.75 },
        { 11, 143.89 },
        { 12, 144.43 },
        { 13, 160.27 },
        { 14, 177.90 },
        { 15, 166.66 },
        { 16, 173.22 },
        { 17, 181.41 },
        { 18, 188.27 },
        { 19, 189.98 },
        { 20, 194.76 },
        { 21, 196.81 },
        { 22, 201.29 },
        { 23, 207.32 },
        { 24, 196.89 },
        { 25, 194.64 },
        { 26, 209.25 }
    };
    
    int numPoints = sizeof(points) / sizeof(Point);
    Term interpolatedTerms[numPoints];
    Polynomial interpolated = { interpolatedTerms, numPoints };
    fillPowers(&interpolated);
    setToZero(&interpolated);
    lagrange(points, numPoints, &interpolated);
    
    printf("Equation found: f(x) = ");
    for(int i = numPoints - 1; i >= 0; i--) {
        printf("%lfx^%d + ", interpolated.terms[i].coefficient, i);
    }
    printf("\n");

    printf("Day 1: %lf \n", computeValue(&interpolated, 1));
    printf("Day 9: %lf \n", computeValue(&interpolated, 9));
    printf("Day 12: %lf \n", computeValue(&interpolated, 12));
    printf("Day 14: %lf \n", computeValue(&interpolated, 14));
    printf("Day 25: %lf \n", computeValue(&interpolated, 25));
    return 0;
}