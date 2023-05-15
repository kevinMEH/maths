#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <stdio.h>
#include "polynomial.h"


// Power of both terms must be the same. If the first Term's power is 0,
// the second Term's power will be used. Why? When you create a Term,
// it's power will default to 0, which can cause undesirable behavior.
// Result is stored in result term.
// Result may be one of the operands.
void addTerms(Term* first, Term* second, Term* result) {
    if(first -> power != 0) {
        result -> power = first -> power;
    } else {
        result -> power = second -> power;
    }
    result -> coefficient = first -> coefficient + second -> coefficient;
}

// Multiplies the first and second terms. Operands must NOT be 0s.
// Result is stored in result term.
// Result may be one of the operands.
void multiplyTerms(Term* first, Term* second, Term* result) {
    result -> coefficient = first -> coefficient * second -> coefficient;
    result -> power = first -> power + second -> power;
}



// For debugging purposes only
void printPolynomial(Polynomial* polynomial) {
    for(int i = 0; i < polynomial->numTerms; i++) {
        printf("Power: %d    Coefficient: %lf \n", polynomial->terms[i].power, polynomial->terms[i].coefficient);
    }
}



// Size is number of terms. Degree of polynomial - 1.
// Use this function if you are lazy. It is recommended that you use initialize
// Polynomials using a stack based array.
Polynomial createPolynomial(int size) {
    Term* terms = (Term*) calloc(size, sizeof(Term));
    return (Polynomial) {
        terms,
        size
    };
}

void deletePolynomial(Polynomial* polynomial) {
    free(polynomial->terms);
}

// Fills the powers of the terms of the polynomial.
void fillPowers(Polynomial* polynomial) {
    for(int i = 0; i < polynomial->numTerms; i++) {
        polynomial->terms[i].power = i;
    }
}

// Sets all coefficients to 0, except for the constant term to 1.
// Size of polynomial must be at least 1.
void setToOne(Polynomial* polynomial) {
    polynomial->terms[0].coefficient = 1;
    for(int i = 1; i < polynomial->numTerms; i++) {
        polynomial->terms[i].coefficient = 0;
    }
}

// SEts all coefficients to 0.
void setToZero(Polynomial* polynomial) {
    for(int i = 0; i < polynomial->numTerms; i++) {
        polynomial->terms[i].coefficient = 0;
    }
}

// Copies the terms of the first polynomial to the second.
// Polynomials MUST be the same size!
void copyTerms(Polynomial* first, Polynomial* second) {
    memcpy(second->terms, first->terms, first->numTerms * sizeof(Term));
}



double polynomialEvaluate(Polynomial* polynomial, double x) {
    double result = 0.0;
    for(int i = 0; i < polynomial -> numTerms; i++) {
        Term* term = &(polynomial -> terms[i]);
        result += term->coefficient * pow(x, i);
    }
    return result;
}


Polynomial* storedPolynomial;
double storedPolynomialEvaluate(double x) {
    return polynomialEvaluate(storedPolynomial, x);
}


void addTermToPolynomial(Polynomial* polynomial, Term* term) {
    int index = term->power;
    Term* correspondingTerm = &(polynomial->terms[index]);
    addTerms(correspondingTerm, term, correspondingTerm);
}

// No memory will be allocated: size of result Polynomial must be equal to the
// maximum power of the two operating Polynomials.
// All powers and coefficients of operands' terms MUST BE SET.
// Result should be a new polynomial or be safe to be overwritten.
// Result may be one of the operands, but it will be overwritten.
// Result's terms' powers will be set up until the maximum power of the two
// operating Polynomials. Must preset result's powers if it is same as operands.
void addPolynomials(Polynomial* first, Polynomial* second, Polynomial* result) {
    int firstTerms = first -> numTerms;
    int secondTerms = second -> numTerms;
    // Operate on shorter polynomial first
    if(firstTerms <= secondTerms) { // First is smaller
        for(int i = 0; i < firstTerms; i++) {
            addTerms(&(first -> terms[i]), &(second -> terms[i]), &(result -> terms[i]));
        }
        for(int i = firstTerms; i < secondTerms; i++) {
            result -> terms[i] = second -> terms[i];
        }
    } else { // Second is smaller
        for(int i = 0; i < secondTerms; i++) {
            addTerms(&(first -> terms[i]), &(second -> terms[i]), &(result -> terms[i]));
        }
        for(int i = secondTerms; i < firstTerms; i++) {
            result -> terms[i] = first -> terms[i];
        }
    }
}

// No memory will be allocated: size of result Polynomial must be equal to the
// sum of the maximum powers of the two operating Polynomials. The numTerms is, in
// most cases, (first - 1) + (second - 1) + 1, or first + second - 1. Zeros in the
// operating polynomials are not computed, so the size of the result polynomial
// may be smaller than this size.
// If the size is too small, out of bounds array writing in the result's Terms
// array will occur.
// Result SHOULD BE A NEW Polynomial. Multiplied terms will be added to be result,
// so it will be added on, not overwritten.
// It is recommended that the results Polynomial HAS ITS POWER SET. This operation
// will NOT set powers.
// Result MAY NOT be one of the operands as it will be changed multiple times during
// the multiplication, which invalidates the initial state of the operand.
void multiplyPolynomials(Polynomial* first, Polynomial* second, Polynomial* result) {
    int firstTerms = first->numTerms;
    int secondTerms = second->numTerms;
    for(int i = 0; i < firstTerms; i++) {
        if(first->terms[i].coefficient == 0) continue;
        for(int j = 0; j < secondTerms; j++) {
            if(second->terms[j].coefficient == 0) continue;
            Term multipliedTerm;
            multiplyTerms(&(first->terms[i]), &(second->terms[j]), &multipliedTerm);
            addTermToPolynomial(result, &multipliedTerm);
        }
    }
}

// Multiplies each term of the polynomial by a constant.
// Result must be of the same size as the operating polynomial.
// Result is safe to be the polynomial itself.
// Only the coefficients of the terms of the resulting polynomial will be modified.
// Powers will remain the same as it was before
void multiplyPolynomialByConstant(Polynomial* polynomial, double constant, Polynomial* result) {
    for(int i = 0; i < polynomial->numTerms; i++) {
        result->terms[i].coefficient = constant * polynomial->terms[i].coefficient;
    }
}

// Divides each term of the polynomial by a constant. Constant cannot be 0.
// Result must be of the same size as the operating polynomial.
// Result is safe to be the polynomial itself.
// Only the coefficients of the terms of the resulting polynomial will be modified.
// Powers will remain the same as it was before
void dividePolynomialByConstant(Polynomial* polynomial, double constant, Polynomial* result) {
    for(int i = 0; i < polynomial->numTerms; i++) {
        result->terms[i].coefficient = polynomial->terms[i].coefficient / constant;
    }
}