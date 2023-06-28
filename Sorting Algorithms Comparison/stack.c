#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MIN_CAPACITY 16

// struct definition for a stack ADT with specified fields from the Lab Document
// The following code credit goes to TA Sahiti for her help on the pseudocode for the stack ADT
struct Stack {
    uint32_t top; // Points to the next empty slot for the stack
    uint32_t capacity; // Number of items that can be pushed
    int64_t *items; // Holds the items in the stack
};

// This function is a constructor function that creates a stack
// Dynamically allocates memory for the stack, specified by the capacity
// Returns a pointer to a Stack
Stack *stack_create(void) {
    Stack *s = (Stack *) calloc(1, sizeof(Stack));
    s->top = 0; // Top of the stack should start at 0
    s->capacity = MIN_CAPACITY; // 16, the capacity of the stack is dynamically growing
    s->items = (int64_t *) calloc(s->capacity, sizeof(int64_t));
    return s;
}

// This function is a destructor function that frees all memory allocated for a Stack
void stack_delete(Stack **s) {
    free((*s)->items);
    free(*s);
    *s = NULL;
}

// This function checks if the specified stack is empty or not
// Parameters: Pointer to a stack s
// Returns a boolean true if the stack is empty, false otherwise
bool stack_empty(Stack *s) {
    return s->top == 0;
}

// This function adds an item to the stack
// Parameters: Pointer to a Stack s, in64_t x which is the item to be added to the stack
// Checks if the specified stack is full or not, implements a dynamically growing stack & doubles capacity if the top of the stack matches the Stack's capacity
// Returns a Boolean true to indicate success, false otherwise
bool stack_push(Stack *s, int64_t x) {
    if (s->top == s->capacity) {
        s->capacity = 2 * s->capacity;
        s->items = (int64_t *) realloc(s->items,
            s->capacity
                * sizeof(
                    int64_t)); // Reallocates memory for the Stack since it is dynamically growing
        if (s->items == NULL) { // In the case that realloc() fails
            return false;
        }
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

// This function pops an item off the specified Stack & passes the value of the item back through a pointer x
// Parameters: Pointer to Stack s, Pointer to an item x
// Checks if the stack is empty before popping, returning a boolean true to indicate success, false otherwise
bool stack_pop(Stack *s, int64_t *x) {
    if (s->top == 0) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

// This function serves as a debugging function
// Parameters: Pointer to Stack s
// Prints out a stack to help determine if implementation of stack is working as intended
void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        printf("%" PRId64, s->items[i]);
    }
    return;
}
