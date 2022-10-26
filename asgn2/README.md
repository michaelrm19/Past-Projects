# Assignment 2
## Professor Darrell Long CSE13s Winter 2021
## Michael Nguyen mnguy181@ucsc.edu

## Description
mathlib.c file showcases my implementation for the functions Sin(x), Cos(x), Tan(x), Exp(x), and Log(x).
mathlib-test.c serves as a test harness for mathlib.c, and outputs the value of x, the approximation computed
from mathlib.c, the expected value from the math.h library, and the difference in values when run.

## Build
$ make all

## Run
$ ./mathlib-test -a

Note: -a tests all functions. -s tests sin. -c test cos. -t tests tan. -e tests exp. -l tests log.

## Clean
$ make clean

## Other Notes:
Credit goes to Professor Darrell Long for his function of Log(x) from his lecture slides. Credit also goes to
TA Eugene from lab section on 1/19/2021 for his test harness mathlib-test.c and his ideas on how to implement
the other functions in mathlib.c Specifically, Eugene helped me create Pseudocode for the functions in mathlib.c.
In addition, credit goes to Professor Darrell Long on the lab document for helping me with how to format
the print statements for the values when running the test harness. You guys are the real MVP and my heroes. Also,
no bugs or warnings were found when running scan-build make.
