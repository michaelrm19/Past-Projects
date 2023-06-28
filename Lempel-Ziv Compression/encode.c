#include "code.h"
#include "endian.h"
#include "io.h"
#include "trie.h"
#include "word.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
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
    // The following code was inspired by TA Eugene's discussions during his most recent lab section
    // Credit goes to the TAs for the pseudocode
    // Default for infile should be stdin, outfile is stdout
    int infile = STDIN_FILENO; // 0
    int outfile = STDOUT_FILENO; // 1
    bool verbose = false;
    int opt = 0;
    // Please do note that the following loop() and error checking was heavily inspired by my own code in Assignment 3
    // Parse command-line options by looping through each call using getopt()
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'v': verbose = true; break;
        case 'i': infile = open(optarg, O_RDONLY); break;
        case 'o': outfile = open(optarg, O_WRONLY); break;
        default: fprintf(stderr, "Usage: %s -[vi:o:]\n", argv[0]); exit(EXIT_FAILURE);
        }
    }
    if (infile < 0) {
        fprintf(stderr, "Invalid infile");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    fstat(infile, &sb);
    FileHeader *h = { 0, 0 };
    h->magic = MAGIC;
    h->protection = sb.st_mode;
    fchmod(outfile, h->protection);
    write_header(outfile, h);

    // Encoding algorithm as defined in the lab document
    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *prev_node = NULL;
    uint8_t curr_sym = 0;
    uint8_t prev_sym = 0;
    uint16_t next_code = START_CODE;
    while (read_sym(infile, &curr_sym)) {
        TrieNode *next_node = trie_step(curr_node, curr_sym);
        if (next_node != NULL) {
            prev_node = curr_node;
            curr_node = next_node;
        } else {
            write_pair(outfile, curr_node->code, curr_sym, bit_length(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code = next_code + 1;
        }
        if (next_code == MAX_CODE) {
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }
        prev_sym = curr_sym;
    }

    if (curr_node != root) {
        write_pair(outfile, prev_node->code, prev_sym, bit_length(next_code));
        next_code = (next_code + 1) % MAX_CODE;
    }
    write_pair(outfile, STOP_CODE, 0, bit_length(next_code));
    flush_pairs(outfile);

    if (verbose) {
        // Print the statistics
    }
    // Close all files and free all memory
    trie_delete(root);
    close(infile);
    close(outfile);
    return 0;
}
