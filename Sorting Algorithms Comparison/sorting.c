#include "bubble.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MASK    ((1 << 30) - 1)
#define OPTIONS "absqhr:n:p:"

typedef enum Sorts { BubbleSort = 0, ShellSort, QuickSort, HeapSort } Sorts;

#define SEED 7092016
uint64_t bubble_moves = 0;
uint64_t bubble_comparisons = 0;
uint64_t shell_moves = 0;
uint64_t shell_comparisons = 0;
uint64_t quick_moves = 0;
uint64_t quick_comparisons = 0;
uint64_t heap_moves = 0;
uint64_t heap_comparisons = 0;

int main(int argc, char **argv) {
    int opt = 0;
    int seed = SEED; // Default of random seed is 7092016
    uint32_t size = 100; // Default of array size
    uint32_t elements = 100; // Default number of elements to print
    uint32_t *a; // Initialize array that will be sorted
    Set sort_set = set_empty();

    // Parse command-line options by looping through each call using getopt()
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            for (Sorts s = BubbleSort; s <= HeapSort; s += 1) {
                sort_set = set_insert(sort_set, s);
            }
            break;
        case 'b': sort_set = set_insert(sort_set, BubbleSort); break;
        case 's': sort_set = set_insert(sort_set, ShellSort); break;
        case 'q': sort_set = set_insert(sort_set, QuickSort); break;
        case 'h': sort_set = set_insert(sort_set, HeapSort); break;
        case 'r': seed = atoi(optarg); break;
        case 'n': size = atoi(optarg); break;
        case 'p': elements = atoi(optarg); break;
        default: fprintf(stderr, "Usage: %s -[absqhr:n:p:]\n", argv[0]); exit(EXIT_FAILURE);
        }
    }

    // Error Checking in case invalid seed, size of array, and number of elements
    if (seed <= 0) {
        fprintf(stderr, "Invalid random seed.\n");
        return 0;
    }
    if (size <= 0) {
        fprintf(stderr, "Invalid array size.\n");
        return 0;
    }
    if (elements > size) {
        elements = size;
    }
    // Dynamically allocate the array
    a = calloc(size, sizeof(uint32_t));

    // Conduct the specified sort using the switch() command
    for (Sorts s = BubbleSort; s <= HeapSort; s += 1) {
        if (set_member(sort_set, s)) {
            switch (s) {
            case BubbleSort:
                srandom(seed); // Starting position
                for (uint32_t i = 0; i < size; i += 1) {
                    a[i] = random() & MASK;
                } // Fill the array
                bubble_sort(a, size);
                printf("Bubble Sort\n");
                printf("%" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
                    bubble_moves, bubble_comparisons);
                for (uint32_t j = 0; j < elements; j += 1) {
                    if ((j % 5) == 0 && j != 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, a[j]); // Prints the elements in the array
                }
                printf("\n");
                break;
            case ShellSort:
                srandom(seed);
                for (uint32_t i = 0; i < size; i += 1) {
                    a[i] = random() & MASK;
                }
                shell_sort(a, size);
                printf("Shell Sort\n");
                printf("%" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
                    shell_moves, shell_comparisons);
                for (uint32_t j = 0; j < elements; j += 1) {
                    if ((j % 5) == 0 && j != 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, a[j]);
                }
                printf("\n");
                break;
            case QuickSort:
                srandom(seed);
                for (uint32_t i = 0; i < size; i += 1) {
                    a[i] = random() & MASK;
                }
                quick_sort(a, size);
                printf("Quick Sort\n");
                printf("%" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
                    quick_moves, quick_comparisons);
                for (uint32_t j = 0; j < elements; j += 1) {
                    if ((j % 5) == 0 && j != 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, a[j]);
                }
                printf("\n");
                break;
            case HeapSort:
                srandom(seed);
                for (uint32_t i = 0; i < size; i += 1) {
                    a[i] = random() & MASK;
                }
                heap_sort(a, size);
                printf("Heap Sort\n");
                printf("%" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
                    heap_moves, heap_comparisons);
                for (uint32_t j = 0; j < elements; j += 1) {
                    if ((j % 5) == 0 && j != 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, a[j]);
                }
                printf("\n");
                break;
            }
        }
    }
    free(a);
    return 0;
}
