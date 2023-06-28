#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "asctel"

int main(int argc, char **argv) {
    // All credit goes to TA Eugene for the following code during his lab section  1/19/2020
    // Changes that were made include initializing the booleans to be false
    // This is because scan-build would give a warning stating that the booleans contained a garbage value
    int opt = 0;
    bool get_sin = false;
    bool get_cos = false;
    bool get_tan = false;
    bool get_exp = false;
    bool get_log = false;
    // option 'a' stands for all
    // option 's' stands for sin
    // option 'c' stands for cos
    // option 't' stands for tan
    // option 'e' stands for exp
    // option 'l' stands for log
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            get_sin = true;
            get_cos = true;
            get_tan = true;
            get_exp = true;
            get_log = true;
            break;
        case 's': get_sin = true; break;
        case 'c': get_cos = true; break;
        case 't': get_tan = true; break;
        case 'e': get_exp = true; break;
        case 'l': get_log = true; break;
        // If invalid option
        default: fprintf(stderr, "Usage: %s -[asctel]\n", argv[0]);
        }
    }
    // In the lab document, the professor provided the print statements when printing out values
    // Thus, credit for the print statement goes to Professor Darrell Long in helping me build the print functions
    if (get_sin) {
        printf("  x            Sin              Library        Difference\n");
        printf("  -            ---              -------        ----------\n");
        for (double x = -M_PI * 2.0; x < M_PI * 2.0; x += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, Sin(x), sin(x), Sin(x) - sin(x));
        }
    }
    if (get_cos) {
        printf("  x            Cos              Library        Difference\n");
        printf("  -            ---              -------        ----------\n");
        for (double x = -M_PI * 2.0; x < M_PI * 2.0; x += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, Cos(x), cos(x), Cos(x) - cos(x));
        }
    }
    if (get_tan) {
        printf("  x            Tan              Library        Difference\n");
        printf("  -            ---              -------        ----------\n");
        for (double x = -M_PI / 3.0; x < M_PI / 3.0; x += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, Tan(x), tan(x), Tan(x) - tan(x));
        }
    }
    if (get_exp) {
        printf("  x            Exp              Library        Difference\n");
        printf("  -            ---              -------        ----------\n");
        for (double x = 1.0; x < 10.0; x += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, Exp(x), exp(x), Exp(x) - exp(x));
        }
    }
    if (get_log) {
        printf("  x            Log              Library        Difference\n");
        printf("  -            ---              -------        ----------\n");
        for (double x = 1.0; x < 10.0; x += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, Log(x), log(x), Log(x) - log(x));
        }
    }
    return 0;
}
