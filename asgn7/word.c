#include "word.h"

#include "code.h"

#include <stdint.h>
#include <stdlib.h>

// Note: The following code was heavily inspired by code and topic discussions led by TA Sahiti during her lab section on 3/11/2021. Credit goes to TA Sahiti for her help
// But not all the code was provided by her during this lab section. She provided tips and advice on how to approach each function.

// Constructor function for a word
// Parameters: An array of symbols syms, the length of the array of symbols len of type uint32_t
// Returns a pointer to a Word or NULL otherwise
Word *word_create(uint8_t *syms, uint32_t len) {
    Word *w = (Word *) calloc(1, sizeof(Word));
    if (w == NULL) {
        return NULL;
    }
    w->len = len;
    w->syms = (uint8_t *) calloc(len, sizeof(uint8_t));
    if (w->syms == NULL) {
        return NULL;
    }
    for (uint32_t i = 0; i < w->len; i += 1) {
        w->syms[i] = syms[i];
    }
    return w;
}

// This function constructs a new word from the specified Word, w, appended with a symbol, sym
// Parameters: A pointer to the word w, a symbol sym of type uint8_t
// Returns a new word
Word *word_append_sym(Word *w, uint8_t sym) {
    Word *new = (Word *) calloc(1, sizeof(Word));
    new->len = w->len + 1;
    new->syms = (uint8_t *) calloc(len + 1, sizeof(uint8_t));
    // Copy the contents of the word's symbols array into the new words symbols array
    for (uint32_t i = 0; i < w->len; i += 1) {
        new->syms[i] = w->syms[i];
    }
    new->syms[w->len] = sym;
    return new;
}

// Destructor function for a Word, w
// Parameters: A single pointer to a Word
void word_delete(Word *w) {
    free(w->syms);
    w->syms = NULL;
    free(w);
    w = NULL;
}

// This function creates a new WordTable (an array of Words)
// Returns a pointer to a WordTable
WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) calloc(
        MAX_CODE, sizeof(Word *)); // Pre-defined size of MAX_CODE, value is UINT16_MAX
    wt[EMPTY_CODE] = (Word *) calloc(1, sizeof(Word));
    return wt;
}

// This function is a destructor function for a WordTable
// Parameters: A pointer to a WordTable, *wt
void wt_delete(WordTable *wt) {
    for (int i = EMPTY_CODE; i < MAX_CODE; i += 1) {
        word_delete(wt[i]);
        wt[i] = NULL;
    }
    free(wt);
}

// This function resets a WordTable to contain just an empty Word, setting all other words to NULL
// Parameters: A single pointer to a WordTable, *wt
void wt_reset(WordTable *wt) {
    for (int i = START_CODE; i < MAX_CODE; i += 1) {
        word_delete(wt[i]);
        wt[i] = NULL;
    }
}
