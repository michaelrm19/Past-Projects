# Assignment 4
## Professor Darrell Long CSEE13s Winter 2021
## Michael  Nguyen mnguy181@ucsc.edu
## Description
bm.c showcases my implementation of the BitMatrix ADT while hamming.c showcases my implementation of the Hamming Module. For this assignment, two programs will be used.
One program, generator.c, will generate Hamming codes while decoder.c will decode Hamming codes. Each program will read from stdin or a file, and write to
stdout or a file. The programs will support command-line arguments used to specify input or output files. The decoder will also print statistics about the 
errors.

## Build

$ make all

## Run

$ ./gen -i inputfile -o outputfile | ./dec

command-line arguments:
-i inputfile: select a valid inputfile and specify it
-o outputfile: select a valid outputfile and specify it
-e: specifies that errors in the hamming code will be put in
-s: specifies the random seed for error.c

## Other Notes:
Unfortunately, I was not able to finish this lab assignment due to an unforeseen family emergency this weekend. I've learned my lesson regardless, and this assignment is not a true representation of who I am as a student and how I'll behave in the future for future programming assignments. Scan-build make returned no bugs or errors. Credit goes to
Eugene Chou (TA) for his pseudocode in which my code for the BitMatrix ADT was inspired from during his lab sections last week.
