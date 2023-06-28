#include "set.h"

#include <stdbool.h>
#include <stdint.h>

// The following functions implement simple sets using bits to track command-line options
// Note: Credit goes to TA Sahiti and TA Eugene on the following code and how to implement sets during lab section
typedef uint32_t Set;

// This function returns an empty set, setting all bits to 0
Set set_empty(void) {
    return 0;
}

// This function returns a boolean if a given value x is in the set s
// Parameters: Set s, uint8_t x
bool set_member(Set s, uint8_t x) {
    uint8_t mask = 1 << x;
    uint8_t result = s & mask;
    return result >> x;
}

// This function returns a set with a bit corresponding to x equal to 1
// Parameters: A Set s, x set member of type uint8_t
Set set_insert(Set s, uint8_t x) {
    uint8_t mask = 1 << x;
    return s | mask;
}

// This function removes a member from a set, clearing the corresponding bit of x
Set set_remove(Set s, uint8_t x) {
    uint8_t mask = ~(1 << x);
    return s & mask;
}

// This function finds a collection of elements that are common to both sets, finding the intersection
// Parameters: two Sets s and t
// Returns a pointer to a set containing the intersection of Sets s and t
Set set_intersect(Set s, Set t) {
    return s & t;
}

// This function finds a collection of all elements in both sets, the union of two sets
// Parameters: two Sets s and t
// Returns a pointer to a new set containing the union of Sets s and t
Set set_union(Set s, Set t) {
    return s | t;
}

//This function returns the complement of a given Set s
Set set_complement(Set s) {
    return ~s;
}

// This function finds the difference between two Sets s and t
// Parameters: two Sets s and t
// Returns a pointer to a new set that contains elements of Set s that are not in Set t
Set set_difference(Set s, Set t) {
    return s & ~(t);
}
