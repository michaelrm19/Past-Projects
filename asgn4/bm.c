#include "bm.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// struct definition for a BitMatrix ADT
struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    uint8_t **mat;
};

// This function is a constructor function, creating a BitMatrix, dynamically allocating memory for the BitMatrix
// Parameters: rows and cols are of type uint32_t, specifying dimensions of the matrix
// Returns a pointer to a BitMatrix
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    m->rows = rows;
    m->cols = cols;
    m->mat = (uint8_t **) calloc(rows, sizeof(uint8_t *));
    uint32_t num_bytes
        = (cols / 8 == 0)
              ? cols / 8
              : cols / 8
                    + 1; // used for determining the number of bytes to allocate for each column, exception being zero
    for (uint32_t r = 0; r < rows; r += 1) {
        m->mat[r] = (uint8_t *) calloc(num_bytes, sizeof(uint8_t));
    }
    return m;
}

// This function is a destructor function for a BitMatrix, freeing all dynamically allocated memory
// Parameters: Pointer to a specified BitMatrix
void bm_delete(BitMatrix **m) {
    for (uint32_t r = 0; r < (*m)->rows; r += 1) {
        free((*m)->mat[r]);
    }
    free((*m)->mat);
    free(*m);
    *m = NULL;
}

// The following two functions serve as accessor functions
// Returns the number of rows or columns for a BitMatrix
uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

// This function is a manipulator function, setting a certain element of the matrix at the specified row and col location
// Paramaters: BitMatrix m, r (row), and c (col) to find and set location of the bit
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint8_t byte = m->mat[r][c / 8];
    uint8_t temp = c % 8; // restricts the index to [0-7]
    uint8_t mask
        = 1
          << temp; // To set a byte, we need to left shift 1 to the specified location for the mask, then OR
    m->mat[r][c / 8] = byte | mask;
    return;
}

// This function is a manipulator function, clearing a bit at the specified row and column location
// Parameters: BitMatrix m, r rows, and c cols to find and clear location of the bit
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint8_t byte = m->mat[r][c / 8];
    uint8_t temp = c % 8; // restricts the index to [0-7]
    uint8_t mask = ~(
        1
        << temp); // By using NOT after left shifting 1 to the specified location for the mask, we invert all bits in the mask
    m->mat[r][c / 8] = byte & mask;
    return;
}

// This function serves as a helper function for performing vector-matrix multiplication
// Parameters: BitMatrix m, r rows, and c cols to find the value of the specified bit
// Returns the value of a bit at a specified location
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint8_t byte = m->mat[r][c / 8];
    uint8_t temp = c % 8; // restricts the index to [0-7]
    uint8_t mask = 1 << temp; // Shifts 1 to specified location
    m->mat[r][c / 8]
        = byte
          & mask; // 1 is only returned if the value at specified location was a 1, 0 otherwise when using AND
    return m->mat[r][c / 8]
           >> temp; // Return the value of the bit by shifting right back to least significant bit location
}

// For debugging purposes, this function prints out a BitMatrix
void bm_print(BitMatrix *m) {
    for (uint8_t r = 0; r < m->rows; r += 1) {
        for (uint8_t c = 0; c < m->cols; c += 1) {
            printf("%d", bm_get_bit(m, r, c));
        }
        printf("\n"); // Prints a new line after each row is finished
    }
    return;
}
