#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define strdup(s) strcpy(malloc(strlen(s) + 1), s)

// Constructor function for a node given parameters, string oldspeak, newspeak
// Allocates memory for a Node and its fields
// If the newspeak field is NULL, then the oldspeak contained in the node is badspeak, NULL newspeak translation
// Returns a pointer to a Node
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (newspeak == NULL && oldspeak != NULL) {
        n->oldspeak = strdup(oldspeak);
        n->newspeak = NULL;
    } else if (newspeak != NULL) {
        n->oldspeak = strdup(oldspeak);
        n->newspeak = strdup(newspeak);
    } else {
        n->oldspeak = oldspeak;
        n->newspeak = newspeak;
    }
    n->next = NULL;
    n->prev = NULL;
    return n;
}

// Destructor function for a Node
// Parameters: Pointer to a Node
// Frees all memory allocated for a node, previous and next node are not deleted
void node_delete(Node **n) {
    free((*n)->oldspeak);
    if ((*n)->newspeak != NULL) {
        free((*n)->newspeak);
    }
    free(*n);
    *n = NULL;
}

// Debug function that prints out a Node's contents, oldspeak and newspeak
// Parameters: Pointer to a Node
void node_print(Node *n) {
    if ((n->oldspeak != NULL)
        && (n->newspeak
            != NULL)) { // print statement for when a node contains oldspeak & newspeak translation
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else if ((n->newspeak == NULL)
               && (n->oldspeak
                   != NULL)) { // print statement for when a node contains only oldspeak/badspeak
        printf("%s\n", n->oldspeak);
    }
}
