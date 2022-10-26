#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Struct definition for a BitVector ADT
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// Constructor function for a Bit Vector
// Parameters: uint32_t length specifies the number of bits that a vector should hold
// Returns NULL if memory allocation fails, otherwise, returning a pointer to a BitVector
BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) calloc(1, sizeof(BitVector));
    if (!bv) {
        return NULL;
    }
    bv->length = length;
    uint32_t num_bytes = (length / 8 == 0) ? length / 8 : length / 8 + 1;
    bv->vector = (uint8_t *) calloc(num_bytes, sizeof(uint8_t));
    return bv;
}

// Destructor function for a Bit Vector
// Parameters: Pointer to Pointer for a BitVector
// Frees all memory allocated for a bit vector
void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
}

// Accessor Function that returns a bit vector's length
// Parameters: A pointer to a Bit Vector
uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

// Manipulator Function that performs bitwise operations on bytes to set a specific bit
// Parameters: Pointer to a Bit Vector, index i
void bv_set_bit(BitVector *bv, uint32_t i) {
    uint8_t byte = bv->vector[i / 8];
    uint8_t temp = i % 8; // Restricts the index to [0-7]
    uint8_t mask
        = 1
          << temp; // To set a byte, left shift 1 to specified location for the mask, then bitwise operation OR
    bv->vector[i / 8] = byte | mask;
    return;
}

// Manipulator Function that clears a bit or element in a bit vector
// Parameters: Pointer to a Bit Vector, index i
void bv_clr_bit(BitVector *bv, uint32_t i) {
    uint8_t byte = bv->vector[i / 8];
    uint8_t temp = i % 8; // Restricts the index to [0-7]
    uint8_t mask = ~(
        1
        << temp); // NOT operation after left shifting 1 to specified location for the mask inverts all bits
    bv->vector[i / 8] = byte & mask;
    return;
}

// Helper function to obtain a specific bit from the Bloom filter to determine if a citizen is using oldspeak
// This function returns a bit
// Parameters: Pointer to a Bit Vector, index i
uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    uint8_t byte = bv->vector[i / 8];
    uint8_t temp = i % 8; // Restricts the index to [0-7]
    uint8_t mask = 1 << temp; // Shifts 1 to specified location
    bv->vector[i / 8] = byte & mask;
    return bv->vector[i / 8]
           >> temp; // Return the value of the bit by shifting right back to least significant bit location
}

// Debugger Function to print out a BitVector
// Parameters: Pointer to a BitVector
void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i += 1) {
        uint8_t temp = bv_get_bit(bv, i);
        printf("%" PRIu8 "\n", temp);
    }
    return;
}
