#include "heap.h"

#include <stdbool.h>
#include <stdint.h>

extern uint64_t heap_moves; // Global variable to keep track of heapsort's number of moves
extern uint64_t
    heap_comparisons; // Global variable to keep track of heapsort's number of comparisons

// This function serves as a helper function for heap sort
// Parameters: Pointer to an Array *A, index of first element, index of second element
// Swaps the elements in the array at specified indices
static inline void swap(uint32_t *A, uint32_t first, uint32_t second) {
    uint32_t temp = A
        [first]; // To swap variables, a temporary variable must be used to store the first element
    A[first] = A[second];
    A[second] = temp;
    heap_moves
        += 3; // Increments the number of moves since we need to keep track of it when testing
    return;
}

// This function serves as a helper function for heap sort
// Parameters: uint32_t first element in an array, uint32_t second element in an array
// Compares the values of two elements, returning a boolean true if the first element is < the second element
static inline bool compare(uint32_t first, uint32_t second) {
    if (first < second) {
        heap_comparisons += 1;
        return true;
    } else {
        heap_comparisons += 1;
        return false;
    }
}

// This function serves as a helper function for heap sort to find the largest element for the max heap implementation
// Parameters: Pointer to Array *A, index of first element, index of last element in the array
// Returns the index of the max child to the parent node
static inline uint32_t max_child(uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if (right <= last && compare(A[left - 1], A[right - 1])) {
        return right;
    }
    return left;
}

// This function serves as a helper function for heap sort, fixing the heap after the max_child is "removed" to obey the constraints of a max heap
// Parameters: Pointer to Array *A, index of first element, index of last element in the array
static inline void fix_heap(uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t parent = first;
    uint32_t great = max_child(A, parent, last);
    while (parent <= (last / 2) && !(found)) {
        if (compare(A[parent - 1], A[great - 1])) {
            swap(A, parent - 1, great - 1);
            parent = great;
            great = max_child(A, parent, last);
        } else {
            found = true;
        }
    }
    return;
}

// This function serves as a helper function for heap sort, creating the heap
// Parameters: Pointer to Array *A, index of first element, index of last element in the array
static inline void build_heap(uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t parent = last / 2; parent > first - 1; parent -= 1) {
        fix_heap(A, parent, last);
    }
    return;
}

// This function serves as the implementation for heap sort, sorting until array is in ascending order
// Parameters: Pointer to Array *A, n length of the array
void heap_sort(uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(A, first, last);
    for (uint32_t leaf = last; leaf > first; leaf -= 1) {
        swap(A, first - 1, leaf - 1);
        fix_heap(A, first,
            leaf - 1); // After removing the largest element, we must fix the heap each time
    }
    return;
}
