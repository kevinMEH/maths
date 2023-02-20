#include "interpolate.h"

// numPoints = number of points in points array
// Result will be stored in the result Polynomial. size must be numPoints - 1.
// results polynomial should have its powers filled and coefficients set to 0s.
void lagrange(Point* points, int numPoints, Polynomial* result) {
    Term topTerms[result->numTerms];
    Polynomial top = {
        topTerms, result->numTerms
    };
    fillPowers(&top);
    
    // We need a placeholder to hold the results from multiplyPolynomials
    // because the result variable may not be one of the operands.
    Term topResultPlaceholderTerms[result->numTerms];
    Polynomial topResultPlaceholder = {
        topResultPlaceholderTerms, result->numTerms
    };
    fillPowers(&topResultPlaceholder);

    Term binomialTerms[2];
    Polynomial binomial = {
        binomialTerms, 2
    };
    binomial.terms[1] = (Term) { 1, 1 }; // Binomial always in the form of x - ?

    for(int i = 0; i < numPoints; i++) {
        setToOne(&top); // Set to 1 for multiplying polynomials

        Point mainPoint = points[i];
        double bottom = 1.0;

        for(int j = 0; j < i; j++) {
            Point otherPoint = points[j];
            binomial.terms[0] = (Term) { -otherPoint.x, 0 };
            setToZero(&topResultPlaceholder);
            // Safe to multiply top with a binomial, as the degree of the top 
            // polynomial + 1 will always be less than or equal to the degree of the
            // placeholder.
            multiplyPolynomials(&top, &binomial, &topResultPlaceholder);
            copyTerms(&topResultPlaceholder, &top);
            bottom = bottom * (mainPoint.x - otherPoint.x);
        }
        for(int j = i + 1; j < numPoints; j++) {
            Point otherPoint = points[j];
            binomial.terms[0] = (Term) { -otherPoint.x, 0 };
            setToZero(&topResultPlaceholder);
            multiplyPolynomials(&top, &binomial, &topResultPlaceholder);
            copyTerms(&topResultPlaceholder, &top);
            bottom = bottom * (mainPoint.x - otherPoint.x);
        }

        multiplyPolynomialByConstant(&top, mainPoint.y, &top);
        dividePolynomialByConstant(&top, bottom, &top);
        
        addPolynomials(result, &top, result);
    }
}
