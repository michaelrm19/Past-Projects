# Assignment 3
## Professor Darrell Long CSE13s Winter 2021
## Michael Nguyen mnguy181@ucsc.edu
## Description
universe.c showcases my implementation of the Universe ADT. life.c showcases my implementation for the Game of Life utilizing the Universe ADT. For this assignment, the program will need to be run with some command line options. The program will read from a specified input file and portray each generation of the Game of Life based on the input from the infile by utilizing ncurses. The final state of the universe will be printed on a specified outfile.

## Build
$ make all

## Run
$ ./life -command-line options

Command Line Options:
-t: specifies that the Game of Life will be played on a toroidal universe
-s: silences ncurses, meaning that nothing will be displayed by ncurses
-n generations: specifies the number of generations that the universe will go through, default being 100
-i input: specifies the input file to read to populate the universe, default being stdin
-o output: specifies the output file to print the final state of the universe to, default being stdout

## Format
$ make format

## Clean
$ make clean

## Other Notes:
The program conducts some error handling (for invalid input file, invalid number of generations, and an unsuccessful universe populating).
Much of the code was inspired by TA Eugene who went over pseudocode on how to approach the universe.c file, and so credit goes to 
TA Eugene for his help during his lab section on 1/26/2021.
My program passed scan-build make with no bugs or errors.
My program, however, did not pass valgrind, meaning that there will be memory leaks when running this program.
Unfortunately, I wasn't able to figure out how to clean up the memory leaks.
