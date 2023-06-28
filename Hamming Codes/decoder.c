#include "hamming.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:"

// Helper functions as defined in the lab document
// Returns the lower nibble of a value
//static inline uint8_t lower_nibble(uint8_t val){
//	return val & 0xF;
//}

// Returns the upper nibble of a value
//static inline uint8_t upper_nibble(uint8_t val){
//	return val >> 4;
//}

// Packs two nibbles into a byte
//uint8_t pack_byte(uint8_t upper, uint8_t lower){
//	return (upper << 4) | (lower & 0xF);
//}

int main(int argc, char **argv) {
    // default for infile should be stdin, outfile is stdout
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int opt = 0;
    // Parses the command-line options by looping through each call using getopt()
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "rb"); break;
        case 'o': outfile = fopen(optarg, "wb"); break;
        default: fprintf(stderr, "Usage: %s -[i:o:]\n", argv[0]); exit(EXIT_FAILURE);
        }
    }
    // Error Handling for invalid input file (does not exist)
    if (infile == NULL) {
        fprintf(stderr, "Invalid input file.\n");
        exit(EXIT_FAILURE);
    }

    fclose(infile);
    fclose(outfile);
    return 0;
}
