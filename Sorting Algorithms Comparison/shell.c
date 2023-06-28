#include "shell.h"

#include "gaps.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

extern uint64_t shell_moves; // Global variable to keep track of shell sort's number of movess
extern uint64_t
    shell_comparisons; // Global variable to keep track of shell sort's number of comparisons

// This function serves as a helper function for shell_sort
// Parameters: Pointer to an array *A, index of first element, index of second element
// Swaps the elements in the array at specified indices
static inline void swap(uint32_t *A, uint32_t first, uint32_t second) {
    uint32_t temp = A
        [first]; // To swap variables, a temporary variable must be used to store the first element
    A[first] = A[second];
    A[second] = temp;
    shell_moves
        += 3; // Increments the number of moves since we need to keep track of it when testing
    return;
}

// This function serves as a helper function for shell_sort
// Parameters: uint32_t first element in array, uint32_t second element in array
// Compares the values of the two elements, returning a boolean true if the first element is less than the second element
static inline bool compare(uint32_t first, uint32_t second) {
    if (first < second) {
        shell_comparisons += 1;
        return true;
    } else {
        shell_comparisons += 1;
        return false;
    }
}

// This function serves as the implementation of shell_sort
// Parameters: Pointer to an Array *A, length of array n
// Iterates through an array, comparing pairs of elements that are gaps apart, swapping if an element of a previous index is greater than the element at the current index
// Gap sequence is provided in gaps.h
void shell_sort(uint32_t *A, uint32_t n) {
    for (uint32_t k = 0; k < GAPS; k += 1) {
        for (uint32_t i = gaps[k]; i < n; i += 1) {
            uint32_t j = i;
            uint32_t temp = A[i];
            while (j >= gaps[k] && compare(temp, A[j - gaps[k]])) {
                swap(A, j, j - gaps[k]);
                j -= gaps[k];
            }
            A[j] = temp;
        }
    }
}
