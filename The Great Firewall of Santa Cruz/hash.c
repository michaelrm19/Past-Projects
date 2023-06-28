#include "hash.h"

#include "ll.h"
#include "node.h"
#include "speck.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Struct definition for a HashTable
struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

// Constructor function for a hash table
// Parameters: uint32_t size indicates the number of indices/linked lists that the hash table can index to, bool mtf (move to front)
// Credit goes to Professor Long and the TAs for the following function (supplied in the lab document)
HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x85ae998311115ae3;
        ht->salt[1] = 0xb6fac2ae33a40089;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

// Destructor function for a hash table
// Parameters: Pointer to Pointer of a HashTable
// Frees each of the linked lists, the underlying array of linked lists, pointer is freed and set to NULL
void ht_delete(HashTable **ht) {
    for (uint32_t i = 0; i < (*ht)->size; i += 1) {
        if ((*ht)->lists[i] != NULL) {
            ll_delete(&(*ht)->lists[i]);
        }
    }
    free((*ht)->lists);
    free(*ht);
    *ht = NULL;
}

// Accessor Function for a hash table
// Parameters: Pointer to a Hashtable
// Returns the hash table's size
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// This function searches for a node in the hash table that contains oldspeak
// The index of the linked list to perform a look-up on is calculated by hashing the oldspeak.
// Returns a pointer to the node if found, otherwise, NULL
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t index = hash(ht->salt, oldspeak);
    Node *temp = ll_lookup(ht->lists[index], oldspeak);
    if (temp != NULL) {
        return temp;
    } else {
        return NULL;
    }
}

// Manipulator function that inserts the specified oldspeak and its corresponding newspeak translation into the hash table
// Index of the linked list to insert into is calculated by hashing the oldspeak
// If the linked list hasn't been initialized yet, create the linked list first before inserting
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak);
    if (ht->lists[index] == NULL) {
        ht->lists[index] = ll_create(
            ht->mtf); // Initializes a linked list if it hasn't been initialized yet before inserting
    }
    ll_insert(ht->lists[index], oldspeak, newspeak);
    return;
}

// Debug function to print out the contents of a hash table
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i += 1) {
        if (ht->lists[i] != NULL) {
            ll_print(ht->lists[i]);
            printf("\n");
        }
    }
}
