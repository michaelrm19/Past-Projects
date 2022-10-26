#include "hamming.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "i:o:"

// Helper Functions as provided in the lab document
// Returns the lower nibble of a value
//static inline uint8_t lower_nibble(uint8_t val){
//	return val & 0xF;
//}

// Returns the upper nibble of a value
//static inline uint8_t upper_nibble(uint8_t val){
//	return val >> 4;
//}

int main(int argc, char **argv) {
    // Default for infile should be stdin, outfile is stdout
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int opt = 0;
    // Parse command-line options by looping through each call using getopt()
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "rb"); break;
        case 'o': outfile = fopen(optarg, "wb"); break;
        default: fprintf(stderr, "Usage: %s -[i:o:]\n", argv[0]); exit(EXIT_FAILURE);
        }
    }
    // Error handling for invalid input file (does not exist)
    if (infile == NULL) {
        fprintf(stderr, "Invalid input file.\n");
        exit(EXIT_FAILURE);
    }
    // Initalize the Hamming Code module
    //	ham_init();
    // Read bytes from specified file stream or stdin
    //	while(fgetc(infile) != EOF){
    //		uint8_t byte = fgetc(infile);
    //		uint8_t low_nibble = lower_nibble(byte);
    //		uint8_t high_nibble = upper_nibble(byte);
    //		uint8_t low_code = ham_encode(low_nibble, &low_code);
    //		uint8_t high_code = ham_encode(high_nibble, &high_code);
    //		fputc(low_code, outfile);
    //		fputc(high_code, outfile);
    //	}

    // Free memory allocated by the Hamming Code module
    //	ham_destroy();
    // Close all files
    fclose(infile);
    fclose(outfile);
    return 0;
}
