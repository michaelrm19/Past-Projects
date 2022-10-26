# Assignment 5
## Michael Nguyen
## Description

stack.c showcases my implementation of the stack ADT while set.c showcased my implementation of the set ADT. The sorting algorithms were implemented
in bubble.c, quick.c, shell.c, and heap.c. sorting.c contains the main() function and serves as a test harness for these sorting algorithms. The program
accepts several different command line options, sorts an array with the specified sorting algorithms, and prints the array and the statistics regarding the sort.

## Build

$ make all

## Run

$ ./sorting -commandlineoptions
command line options: -a enables all sorting algorithms, -b enables bubble sort, -s enables shell sort, -q enables quicksort, -h enables heapsort, -r seed specifies
a random seed, -n size specifies the array size, and -p elements specifies the number of elements to be printed from the array

## Clean

$ make clean

## Other Notes
Program passed scan-build without any errors or bugs.
