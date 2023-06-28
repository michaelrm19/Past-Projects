#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Struct definition of a BloomFilter ADT
struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

// Constructor function for a Bloom Filter
// Parameters: uint32_t size indicates the size of the underlying BitVector
// Credit goes to Professor Long and the TAs for the following function (supplied on the lab document)
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = 0x02d232593fbe42ff;
        bf->primary[1] = 0x3775cfbf0794f152;
        bf->secondary[0] = 0xc1706bc17ececc04;
        bf->secondary[1] = 0xe9820aa4d2b8261a;
        bf->tertiary[0] = 0xd37b01df0ae8f8d0;
        bf->tertiary[1] = 0x911d454886ca7cf7;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

// Destructor function for a Bloom Filter
// Parameters: Double Pointer to a Bloom Filter
// Frees any memory allocated by the constructor and nulls out the pointer that was passed in
void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter);
    free(*bf);
    *bf = NULL;
}

// Getter Function that returns the Bloom Filter's size
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// Takes the oldspeak and inserts it into the Bloom Filter
// Sets the bits at those indices in the underlying bit vector
void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t primary_index = hash(bf->primary, oldspeak);
    uint32_t secondary_index = hash(bf->secondary, oldspeak);
    uint32_t tertiary_index = hash(bf->tertiary, oldspeak);
    bv_set_bit(bf->filter, primary_index);
    bv_set_bit(bf->filter, secondary_index);
    bv_set_bit(bf->filter, tertiary_index);
    return;
}

// This function probes the Bloom Filter for oldspeak
// Parameters: Pointer to Bloom Filter, a string oldspeak
// Returns true to signify that oldspeak was most likely added to the Bloom Filter, false otherwise
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t primary_index = hash(bf->primary, oldspeak);
    uint32_t secondary_index = hash(bf->secondary, oldspeak);
    uint32_t tertiary_index = hash(bf->tertiary, oldspeak);
    uint8_t prim
        = bv_get_bit(bf->filter, primary_index); // Gets the bits at the 3 different indices
    uint8_t sec = bv_get_bit(bf->filter, secondary_index);
    uint8_t tert = bv_get_bit(bf->filter, tertiary_index);
    if (prim && sec && tert) {
        return true;
    }
    return false;
}

// This function serves as a debugger function to print out the Bloom Filter
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
