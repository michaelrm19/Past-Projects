# Assignment 7
## Michael Nguyen
## Description
The purpose of this program will be to implemennt data compression, specifically the LZ78 compression and decompression algorithms. Thus, the program
is split into two program, encode.c and decode.c. Encode will be able to compress any file, text or binary, while decode will be able to
decompress any file, text or binary (that was compressed with encode). Both programs will be able to operate on big and little endian systems. The programs will
compress and decompress given input and output files and print out statistics after each process (if specified). To do this, there are several ADTs, trie ADT and word ADT.
The program will also contain a source file for the I/O module.

## Build
$ make all

## Run
$ ./encode -i test.txt | ./decode -o test2.txt

## Command Line Options
-v enables the verbose option which enables the program to print out compression and decompression statistics,
-i input (specifies input to compress or decompress),
-o output (specifies output of compressed or decompressed input)

## Clean
$ make clean

## Other Notes
Credit goes to TA Eugene and TA Sahiti for their help during their lab sections for this programming assignment. A lot of my code is inspired
by their pseudocode and discussions during these lab sections.
