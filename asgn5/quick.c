#include "quick.h"

#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

extern uint64_t quick_moves; // Global variable to keep track of quicksort's number of moves
extern uint64_t
    quick_comparisons; // Global variable to keep track of quicksort's number of comparisons

// This function serves as a helper function for quick sort
// Parameters: Pointer to an Array *A, index of first element, index of second element
// Swaps the elements in the array at specified indices
static inline void swap(uint32_t *A, uint64_t first, uint64_t second) {
    uint32_t temp = A
        [first]; // To swap variables, a temporary variable must be used to store the first element
    A[first] = A[second];
    A[second] = temp;
    quick_moves
        += 3; // Increments the number of moves since we need to keep track of it when testing
    return;
}

// This function serves as a helper function for quick sort
// Parameters: uint32_t first element in an array, uint32_t second element in an array
// Compares the values of two elements, and returns a boolean true if the first element is < the second element
static inline bool compare(uint32_t first, uint32_t second) {
    if (first < second) {
        quick_comparisons += 1;
        return true;
    } else {
        quick_comparisons += 1;
        return false;
    }
}

// This function serves as a helper function for quick sort
// Parameters: Pointer to array *A, lo represents the leftmost index, hi is the rightmost index of type int64_t
// Places elements less than a pivot onto the left side of the array, elements greater than or equal to the pivot onto the right side
// Returns the index of type uint64_t that is the division between the partitioned parts of the array
static inline uint64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
    uint32_t pivot = A[lo + ((hi - lo) / 2)];
    int64_t i
        = lo - 1; // These need to be of type int64_t to align with future stack calls in quick sort
    int64_t j = hi + 1;
    do {
        i += 1;
        while (compare(A[i], pivot)) {
            i += 1;
        }
        j -= 1;
        while (compare(pivot, A[j])) {
            j -= 1;
        }
        if (i < j) {
            swap(A, i, j);
        }
    } while (i < j);
    return j;
}

// This function serves as the implementation of quick sort
// Parameters: Pointer to array *A, n length of the array of type uint32_t
// Partitions arrays into two sub-arrays by designating an element from the array as a pivot
// Pushes elements < pivot on the left side of the pivot, and >= pivot on the right side until the array is sorted
void quick_sort(uint32_t *A, uint32_t n) {
    int64_t left = 0;
    int64_t right = n - 1;
    Stack *s = stack_create();
    stack_push(s, left); // Pushes two indices onto the stack at a time
    stack_push(s, right);
    while (!(stack_empty(s))) {
        int64_t hi;
        int64_t lo;
        stack_pop(s, &hi);
        stack_pop(s, &lo);
        int64_t p = partition(A, lo, hi);
        if (p + 1 < hi) {
            stack_push(s, p + 1); // Again, pushing two indices onto the stack at a time
            stack_push(s, hi);
        }
        if (lo < p) {
            stack_push(s, lo);
            stack_push(s, p);
        }
    }
    stack_delete(&s);
    return;
}
