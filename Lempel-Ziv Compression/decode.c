#include "code.h"
#include "endian.h"
#include "io.h"
#include "trie.h"
#include "word.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "vi:o:"

// This function is used to find the bitlength of a code
static inline int bit_length(uint16_t code) {
    int bit_count = 0;
    while (code) {
        code >>= 1;
        bit_count += 1;
    }
    return bit_count;
}

int main(int argc, char **argv) {
    // The following code was inspired by TA Eugene's discussions and pseudocode during his most recent lab section
    // Credit goes to the TAs for the pseudocode
    // Default for infile should be stdin, outfile is stdout
    int infile = STDIN_FILENO; // 0
    int outfile = STDOUT_FILENO; // 1
    //    bool verbose = false;
    int opt = 0;
    // Parse command-line options by looping through each call using getopt()
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'v': verbose = true; break;
        case 'i': infile = open(optarg, O_RDONLY); break;
        case 'o': outfile = open(optarg, O_WRONLY); break;
        default: fprintf(stderr, "Usage: %s -[vi:o:]\n", argv[0]); exit(EXIT_FAILURE);
        }
    }
    if (infile < 0) { // Checks the validity of the infile
        fprintf(stderr, "Invalid infile");
        exit(EXIT_FAILURE);
    }
    FileHeader *h;
    read_header(infile, &h);
    if (h.magic != MAGIC) { // Checks the magic number read in
        fprintf(stderr, "Invalid header");
        exit(EXIT_FAILURE);
    }
    fchmod(outfile, h.protection);

    // Decompression algorithm as provided in the lab document's pseudocode
    WordTable *table = wt_create();
    uint8_t *curr_sym = 0;
    uint16_t *curr_code = 0;
    uint16_t next_code = START_CODE;
    while (read_pair(infile, &curr_code, &curr_sym, bit_length(next_code))) {
        table[next_code] = word_append_sym(table[curr_code], curr_sym);
        write_word(outfile, table[next_code]);
        next_code = next_code + 1;
        if (next_code == MAX_CODE) {
            wt_reset(table);
            next_code = START_CODE;
        }
    }
    flush_words(outfile);

    // Print statistics if verbose option is enabled
    if (verbose) {
        // print out statistics
    }
    // free all memory and close all files
    wt_delete(table);
    close(infile);
    close(outfile);
    return 0;
}
