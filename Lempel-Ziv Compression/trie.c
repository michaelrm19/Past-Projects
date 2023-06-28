#include "trie.h"

#include "code.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Note: The following code was created through the help of TA Eugene during his lab section along with TA Sahiti's lab section on 3/11/2021
// Credit goes to the TAs for their help

// Constructor function for a TrieNode where the node's code is set to node
// All children node pointers are set to NULL
// Parameters: code of type uint16_t (16-bit code for a word)
// Returns a pointer to a TrieNode
TrieNode *trie_node_create(uint16_t code) {
    TrieNode *t = (TrieNode *) calloc(1, sizeof(TrieNode));
    t->code = code;
    return t;
}

// Destructor function for a TrieNode
// Parameters: A single pointer to a TrieNode
void trie_node_delete(TrieNode *n) {
    free(n);
    n = NULL;
}

// This function initializes a trie where the root TrieNode is created with EMPTY_CODE
// Returns the root if successful, NULL otherwise
TrieNode *trie_create(void) {
    TrieNode *n = trie_node_create(EMPTY_CODE);
    return n;
}

// This function deletes a sub-trie starting from the trie rooted at node n
// Parameters: A pointer to a TrieNode n
void trie_delete(TrieNode *n) {
    for (int i = 0; i < ALPHABET; i += 1) {
        if (n->children != NULL) {
            trie_delete(n->children[i]);
            n->children = NULL;
        }
    }
    trie_node_delete(n);
}

// This function resets a trie to just the root TrieNode (in the case that we reach the end of available codes)
// Parameters: A pointer to the root of a trie
void trie_reset(TrieNode *root) {
    for (int i = 0; i < ALPHABET; i += 1) {
        if (root->children[i] != NULL) {
            trie_reset(root->children[i]);
            root->children = NULL;
        }
    }
}

// This function returns a pointer to a child node representing the symbol sym, otherwise, NULL is returned
// Parameters: A pointer to a TrieNode, symbol sym of type uint8_t
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    return n->children[sym];
}
