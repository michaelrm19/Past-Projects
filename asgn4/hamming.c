#include "hamming.h"

#include "bm.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//enum ham_rc{
//	HAM_ERR = -1,
//	HAM_OK = 0,
//	HAM_ERR_OK = 1
//} ham_rc;

// Both G and H are 4x8 bit matrices
static BitMatrix *generator;
static BitMatrix *parity;

// This function creates and initializes the G and H transposed matrix ADTs
// Returns HAM_ERR if creating either failed, HAM_OK otherwise
ham_rc ham_init(void) {
    generator = bm_create(4, 8);
    parity = bm_create(8, 4); // Parity is 8x4 since it is H transposed
    if (generator == NULL
        || parity == NULL) { // Failing to create either bit matrix will return HAM_ERR
        return HAM_ERR;
    }
    for (uint32_t r = 0; r < bm_rows(generator);
         r += 1) { // Sets the bits for the first half of the G matrix in a diagonal manner
        for (uint32_t c = 0; c < 4; c += 1) {
            if (r == c) {
                bm_set_bit(generator, r, c);
            }
        }
    }
    for (uint32_t r = 0; r < bm_rows(generator); r += 1) {
        for (uint32_t c = 4; c < bm_cols(generator); c += 1) {
            if (r != c) {
                bm_set_bit(generator, r, c);
            }
        }
    }
    for (uint32_t r = 0; r < 4;
         r += 1) { // Sets the bits for the top half of the H_transposed/parity matrix
        for (uint32_t c = 0; c < bm_cols(parity); c += 1) {
            if (r != c) {
                bm_set_bit(parity, r, c);
            }
        }
    }
    // Set the rest of the bits in the parity matrix
    bm_set_bit(parity, 4, 0);
    bm_set_bit(parity, 5, 1);
    bm_set_bit(parity, 6, 2);
    bm_set_bit(parity, 7, 3);
    return HAM_OK;
}

// This function frees all memory allocated for the Hamming module
void ham_destroy(void) {
    bm_delete(&generator);
    bm_delete(&parity);
}

// This function generates a Hamming code for a nibble of data
// Parameters: data represents a nibble, *code provides us with the ability to return a return code while updating code
/*ham_rc ham_encode(uint8_t data, uint8_t *code){
	// If A is n x m vector (data is 1 x 4)
	// B is m x p matrix (Generator matrix is 4 x 8 matrix)
	// then C is n x p matrix where C = A * B
	*code = data;
	// implements matrix multiplication
	for (int i = 0; i < 1; i += 1){
		for (int j = 0; j < 8; j += 1){
			for (int k = 0; k < 4; k += 1){
				code[i][j] += data[i][k] * generator[k][j];
				code[i][j] = code[i][j] % 2;
			}
		}
	}
	if(code == NULL){
		return HAM_ERR;
	}
	return HAM_OK;
		
}

// This function  decodes a Hamming code
// Parameters: data represents a nibble/decoded data, code stores the hamming code
// Returns a ham_rc depending on the error syndrome
ham_rc ham_decode(uint8_t code, uint8_t *data){
	return HAM_OK;
}
*/
