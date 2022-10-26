#include "mathlib.h"

#include <math.h>

#define EPSILON 1e-14 // 1 * 10^(-14)

// This function returns the absolute value of x given a valid double x
static inline double Abs(double x) {
    // If x is less than 0, multiply x by -1.0
    // return the value
    return x < 0 ? -x : x;
}

// This function will return the sin(x) given a valid double x
// It will be implemented using the Taylor Series Expansion method
// Returns an approximation of sin(x)
double Sin(double x) {
    // Normalize the input values to be in the range [-2pi, 2pi]
    x = fmod(x, 2.0 * M_PI);
    // Initialize variables, ensuring that each are double (don't want rounded answers)
    double numerator = x;
    double denominator = 1.0;
    double term = numerator / denominator;
    double sign = -1.0;
    double sum = term;
    double prev_sum = 0.0;
    // The following loop computes each term, ending when the term is less than Epsilon
    // Start with k = 3 in accordance to the lab document, incrementing k by 2 each time
    // Alternate the sign by multiplying by -1.0 during each iteration
    // Sum represents the sum of all terms
    for (double k = 3.0; Abs(sum - prev_sum) > EPSILON; k += 2.0, sign *= -1.0) {
        numerator = numerator * x * x;
        denominator = denominator * (k - 1.0) * k;
        term = numerator / denominator;
        term = term * sign;
        prev_sum = sum;
        sum += term;
    }
    return sum;
}

// This function will return the cos(x) given a valid double x
// It will be implemented using the Taylor Series Expansion method
// Returns an approximation of cos(x)
double Cos(double x) {
    // Normalize the input values to be in the range [-2pi, 2pi]
    // Implementation is roughly the exact same as Sin(x)
    x = fmod(x, 2.0 * M_PI);
    // Initialize variables, ensuring that each are double (don't want rounded answers)
    double numerator = 1.0;
    double denominator = 1.0;
    double term = numerator / denominator;
    double sign = -1.0;
    double sum = term;
    double prev_sum = 0.0;
    // The following loop computes each term, ending when the term is less than Epsilon
    // Start with k = 2 in accordance to the expansion on the lab document, incrementing k by 2 each time
    // Alternate the sign by multiplying by -1.0 during each iteration
    // Sum represents the sum of all terms
    for (double k = 2.0; Abs(sum - prev_sum) > EPSILON; k += 2.0, sign *= -1.0) {
        numerator = numerator * x * x;
        denominator = denominator * (k - 1.0) * k;
        term = numerator / denominator;
        term = term * sign;
        prev_sum = sum;
        sum += term;
    }
    return sum;
}

// This function will return the tan(x) given a valid double
// In essence, the logic behind this function is to return sin(x)/cos(x)
// Tan(x) will be implemented using the Taylor Series Expansion method
// Returns an approximation of tan(x)
double Tan(double x) {
    // Normalize the input value to be in the range [-2pi, 2pi]
    x = fmod(x, M_PI / 2.0);
    // Declare variables, implementing sin(x)/cos(x) and return resulting value
    double numerator = sin(x);
    double denominator = cos(x);
    double term = numerator / denominator;
    return term;
}

// This function will return the exp(x) given a valid double
// It will be implemented using the Taylor Series Expansion method
// Returns an approximation of exp(x)
double Exp(double x) {
    // Declare variables, specifically, I need to keep track of numerator, denominator, terms, and sum
    double numerator = 1.0;
    double denominator = 1.0;
    double term = numerator / denominator;
    double sum = term;
    // The following for loop computes the value of each term, adding it to the sum
    // The loop ends when the computed value is less than Epsilon
    // Start at k = 1.0, incrementing k by 1.0 each time
    for (double k = 1.0; Abs(term) > EPSILON; k += 1.0) {
        double temp = x / k;
        term *= temp;
        sum += term;
    }
    return sum;
}

// This function will compute an approximation and return the log(x) given a valid double x
// It will be implemented using Newton's method
// Note: Credit goes to Professor Darrell Long during lecture
double Log(double x) {
    double x_n = 1.0;
    // Initial term
    double prev = Exp(x_n);
    while (Abs(prev - x) > EPSILON) {
        x_n += (x - prev) / prev;
        prev = Exp(x_n);
    }
    return x_n;
}
