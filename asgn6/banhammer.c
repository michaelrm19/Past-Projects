#include "bf.h"
#include "hash.h"
#include "ll.h"
#include "node.h"
#include "parser.h"

#include <inttypes.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WORD    "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]+)*"
#define HT_SIZE 10000
#define BF_SIZE 1 << 20
#define OPTIONS "h:f:m"

// To lower case function, takes in a string, and makes it all lower case
// Credit goes to Professor Long for the inspiration of his code on piazza
void lower_case(char *s) {
    while (*s) {
        *s = *s >= 'A' && *s <= 'Z' ? *s | 0x60 : *s;
        s += 1;
    }
    return;
}

int main(int argc, char **argv) {
    int opt = 0;
    uint32_t hash_size = HT_SIZE; // Default is 10000
    uint32_t bf_size = BF_SIZE; // Default is 2^20
    bool mtf = false; // Default is false unless enabled
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': hash_size = atoi(optarg); break;
        case 'f': bf_size = atoi(optarg); break;
        case 'm': mtf = true; break;
        default: fprintf(stderr, "Usage: %s - [h:f:m]\n", argv[0]); exit(EXIT_FAILURE);
        }
    }

    // Initialize the Bloom Filter and Hash Table
    BloomFilter *bf = bf_create(bf_size);
    HashTable *ht = ht_create(hash_size, mtf);

    // Check that both were properly initialized
    if (!bf) {
        fprintf(stderr, "Bloom Filter not initialized\n");
        exit(EXIT_FAILURE);
    }
    if (!ht) {
        fprintf(stderr, "HashTable not initialized\n");
        exit(EXIT_FAILURE);
    }

    // Read in a list of badspeak words with fscanf(), adding it to the Bloom Filter and Hash Table
    // Credit goes to TA Sahiti for her following code on how to read in from the two text files during her lab section on 2/25/2021
    char badspeak[4000];
    FILE *infile = fopen("badspeak.txt", "r");
    while (fscanf(infile, "%s\n", badspeak) != EOF) {
        bf_insert(bf, badspeak);
        ht_insert(ht, badspeak, NULL);
    }
    fclose(infile);

    // Read in a list of oldspeak and newspeak pairs with fscanf()
    // Oldspeak will be added to the Bloom filter, both oldspeak and newspeak are added to the Hash Table
    char oldspeak[4000];
    char newspeak[4000];
    FILE *nextfile = fopen("newspeak.txt", "r");
    while (fscanf(nextfile, "%s %s\n", oldspeak, newspeak) != EOF) {
        bf_insert(bf, oldspeak);
        ht_insert(ht, oldspeak, newspeak);
    }
    fclose(nextfile);

    // Filter out words by reading words from stdin using supplied parsing module
    // Credit goes to the TAs and Professor Long for the following code provided on the lab document
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;
    LinkedList *bad = ll_create(mtf);
    LinkedList *old = ll_create(mtf);
    bool thoughtcrime = false;
    bool counseling = false;
    while ((word = next_word(stdin, &re)) != NULL) {
        lower_case(word);
        // For each word that is read, check if added to Bloom Filter
        if (bf_probe(bf, word)) {
            // If the hash table contains a word and the word does not have a newspeak translation, guilty of throughtcrime
            if (ht_lookup(ht, word) != NULL && (ht_lookup(ht, word)->newspeak == NULL)) {
                ll_insert(bad, word, NULL);
                thoughtcrime = true;
            }
            // If the hash table contains a word and the word does have a newspeak translation, requires counseling
            else if (ht_lookup(ht, word) != NULL && (ht_lookup(ht, word)->newspeak != NULL)) {
                char *temp = "";
                strcpy(temp, ht_lookup(ht, word)->newspeak);
                ll_insert(old, word, temp);
                counseling = true;
            }
            // If the hash table does not contain the word, false positive
        }
    }

    if (thoughtcrime && counseling) {
        printf("Dear Comrade,\n\n");
        printf("You have chosen to use degenerate words that may cause hurt feelings or cause your "
               "comrads to think unpleasant thoughts. This is doubleplus bad. To correct your "
               "wrongthink and preserve community consensus we will be sending you to joycamp "
               "administered by Medellin's Miniluv. Beware of the hippos.\n\n");
        printf("Your errors:\n\n");
        ll_print(bad);
        printf("\n");
        printf("Think of these words on your vacation!\n\n");
        ll_print(old);
    }

    else if (thoughtcrime) {
        printf("Dear Comrade,\n\n");
        printf("You have chosen to use degenerate words that may cause hurt feelings or cause your "
               "comrades to think unpleasant thoughts. This is doubleplus bad. To correct your "
               "wrongthink and preserve community consensus we will be sending you to joycamp "
               "administered by Medellin's Miniluv. Beware of the hippos.\n\n");
        printf("Your errors:\n\n");
        ll_print(bad);
    } else if (counseling) {
        printf("Dear Comrade,\n\n");
        printf("Submitting your text helps to preserve feelings and prevent badthink. Some of the "
               "words that you used are not goodspeak. The list shows how to turn the oldspeak "
               "words into newspeak.\n\n");
        ll_print(old);
    }

    ll_delete(&bad);
    ll_delete(&old);
    bf_delete(&bf);
    ht_delete(&ht);
    clear_words();
    regfree(&re);
    return 0;
}
