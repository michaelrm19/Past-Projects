#include "ll.h"

#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// struct definition of a linked list
// Credit goes to TA Eugene and TA Sahiti for their help on how to approach the Linked List ADT with pseudocode during their lab sections
struct LinkedList {
    uint32_t length;
    Node *head; // Head sentinel node
    Node *tail; // Tail sentinel node
    bool mtf; // Move to Front
};

// Constructor function for a linked list
// Parameters: boolean mtf (Move to Front)
// Allocates memory for a linked list and sets the fields for a linked list
// Returns a pointer to the linked list
LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    ll->length = 0;
    ll->head = node_create(NULL, NULL);
    ll->tail = node_create(NULL, NULL);
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    ll->mtf = mtf;
    return ll;
}

// Destructor function for a linked list
// Parameters: Point to Pointer of a Linked List
// Frees all memory allocated for a linked list, freeing all nodes, and the pointer to the Linked List
void ll_delete(LinkedList **ll) {
    for (Node *i = (*ll)->head; i != (*ll)->tail; i = i->next) {
        node_delete(&i);
    }
    node_delete(&(*ll)->tail);
    free(*ll);
    *ll = NULL;
}

// Accessor function for a linked list
// Parameters: Pointer to a Linked List
// Returns the length of a Linked List
uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

// Accessor function for a Linked List
// Parameters: Pointer to a Linked List, string oldspeak
// Searches for a node containing oldspeak, returning a pointer to the node if found, otherwise, NULL pointer is returned
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        if (n->oldspeak == oldspeak) {
            if (ll->mtf) { // If move to front is enabled for the linked list, we want to optimize searching by moving a searched node to the front
                n->prev->next = n->next;
                n->next->prev = n->prev;
                n->next = ll->head->next;
                n->prev = ll->head;
                ll->head->next->prev = n;
                ll->head->next = n;
            }
            return n;
        }
    }
    return NULL;
}

// Manipulator function for a Linked List
// Parameters: Pointer to a Linked List, string oldspeak, string newspeak
// Inserts a new node containing the specified oldspeak and newspeak at the head of the linked list
// Checks to make sure no duplicates are inserted into the Linked List
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    // If lookup() returns a Node, then we do not insert a new node
    for (Node *i = ll->head->next; i != ll->tail; i = i->next) {
        if (i->oldspeak == oldspeak) {
            return;
        }
    }
    Node *n = node_create(oldspeak, newspeak);
    n->prev = ll->head;
    n->next = ll->head->next;
    ll->head->next->prev = n;
    ll->head->next = n;
    ll->length += 1; // Increase the length of the linked list after every insertion
}

// Prints out each node in a linked list except for the head and tail sentinel nodes utilizing node_print()
void ll_print(LinkedList *ll) {
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        node_print(n);
    }
}
