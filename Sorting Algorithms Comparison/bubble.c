#include "bubble.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

extern uint64_t bubble_moves; // Global variable to keep track of bubble sort's number of moves
extern uint64_t
    bubble_comparisons; // Global variable to keep track of bubble sort's number of comparisons

// This functions serves as a helper function for bubble_sort
// Parameters: Pointer to an Array *A, index of first element, index of second element
// Swaps the elements in the array at specified indices
static inline void swap(uint32_t *A, uint32_t first, uint32_t second) {
    uint32_t temp = A[first]; // To swap variables, temp must be used to store the first element
    A[first] = A[second];
    A[second] = temp;
    bubble_moves += 3; // Increments the number of moves since we need to keep track of it
    return;
}

// This function serves as a helper function for bubble_sort
// Parameters: uint32_t first element in array, uint32_t second element in array
// Compares the values of the two elements, and returns a boolean true if the first element is < the second element
static inline bool compare(uint32_t first, uint32_t second) {
    if (first < second) {
        bubble_comparisons += 1;
        return true;
    } else {
        bubble_comparisons += 1;
        return false;
    }
}

// This function implements bubble_sort
// Parameters: Pointer to an Array *A, n is the length of the array
// Iterates through the array, comparing pairs of neighboring elements, swapping them if current element is less than the previous element
void bubble_sort(uint32_t *A, uint32_t n) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (uint32_t i = 1; i < n; i += 1) {
            if (compare(A[i], A[i - 1])) {
                swap(A, i, i - 1);
                swapped = true;
            }
        }
        n -= 1; // After each iteration, we only need to compare n pairs
    }
    return;
}
