#ifndef POLYNOMIAL
#define POLYNOMIAL

#include "./basic_structures.h"

// Variables like x, or constants if the power is 0.
// For simplicity only integer powers are allowed. Sorry.
// 0000000000000... = coefficient = 0.0, power = 0
typedef struct Term {
    double coefficient;
    int power;
} Term;

typedef struct Polynomial {
    Term* terms;
    int numTerms;
} Polynomial;

void addTerms(Term* first, Term* second, Term* result);
void multiplyTerms(Term* first, Term* second, Term* result);

void printPolynomial(Polynomial* polynomial);

Polynomial createPolynomial(int size);
void deletePolynomial(Polynomial* polynomial);

void fillPowers(Polynomial* polynomial);
void setToOne(Polynomial* polynomial);
void setToZero(Polynomial* polynomial);

void copyTerms(Polynomial* first, Polynomial* second);

double polynomialEvaluate(Polynomial* polynomial, double x);
double storedPolynomialEvaluate(double x);

void addTermToPolynomial(Polynomial* polynomial, Term* term);
void addPolynomials(Polynomial* first, Polynomial* second, Polynomial* result);
void multiplyPolynomials(Polynomial* first, Polynomial* second, Polynomial* result);
void multiplyPolynomialByConstant(Polynomial* polynomial, double constant, Polynomial* result);
void dividePolynomialByConstant(Polynomial* polynomial, double constant, Polynomial* result);

#endif