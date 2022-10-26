#include "universe.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "tsn:i:o:"
#define DELAY   50000 // sleep for 50000 microseconds for ncurses

int main(int argc, char **argv) {
    // Set up the ncurses screen as shown in the lab document
    initscr();
    curs_set(FALSE);
    // Default for infile should be stdin, outfile is stdout
    // Default number of generations is 100
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int generations = 100;
    bool toroidal = false;
    bool silence = false;
    int opt = 0;
    // Parse command-line options by looping through each call using getopt()
    // Please note that the following while loop() for parsing command-line options was inspired by my code for assignment 2
    // In Assignment 2, TA Eugene discussed and showed how to parse command-line options
    // Credit goes to TA Eugene during his lab section for the inspiration
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': toroidal = true; break;
        case 's': silence = true; break;
        case 'n': generations = atoi(optarg); break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        default: fprintf(stderr, "Usage: %s -[tsn:i:o:]\n", argv[0]); exit(EXIT_FAILURE);
        }
    }
    // Error handling for invalid input file (does not exist)
    if (infile == NULL) {
        fprintf(stderr, "Invalid input file.\n");
        return 0;
    }
    // Error handling for an invalid number of generations
    if (generations < 0) {
        fprintf(stderr, "Invalid number of generations.\n");
        return 0;
    }
    int rows = 0;
    int cols = 0;
    // Initial call for fscanf() to read number of rows and columns of the universe
    // Populate universe a and b with specified dimensions
    fscanf(infile, "%d %d\n", &rows, &cols);
    Universe *a = uv_create(rows, cols, toroidal);
    Universe *b = uv_create(rows, cols, toroidal);
    // If uv_populate() was not a success, then throw an error message, exiting the program
    if (uv_populate(a, infile) == false) {
        fprintf(stderr, "Malformed Input.\n");
        return 0;
    }
    uv_populate(a, infile);
    // Close the infile to prevent any memory leaks or errors
    fclose(infile);
    int count = 0;
    // Implementation of the 3 rules of the game of life
    // Iterate for each generation up to the set number of generations
    for (int current_gen = 0; current_gen < generations; current_gen++) {
        if (silence) {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    count = uv_census(a, r, c);
                    if (count == 2 || count == 3) {
                        if (uv_get_cell(a, r, c) == true) {
                            uv_live_cell(b, r, c);
                        } else {
                            uv_dead_cell(b, r, c);
                        }
                    }
                    if (uv_get_cell(a, r, c) == false && count == 3) {
                        uv_live_cell(b, r, c);
                    }
                    if (count < 2 || count > 3) {
                        uv_dead_cell(b, r, c);
                    }
                }
            }
            // Swaps the universes, Universe A representing the current state of the universe, and B represents the next state of the universe
            Universe *temp = a;
            a = b;
            b = temp;
        } else {
            // If ncurses isn't silenced, clear screen, display universe a, refresh screen, sleep for 50000 microseconds
            clear();
            // The following loops and conditionals implement one full generation, based on the three rules of the game for a flat universe
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    count = uv_census(a, r, c);
                    if (count == 2 || count == 3) {
                        if (uv_get_cell(a, r, c) == true) {
                            uv_live_cell(b, r, c);
                            mvprintw(r, c, "o"); // Displays 'o' on ncurses
                        } else {
                            uv_dead_cell(b, r, c);
                        }
                    }
                    if (uv_get_cell(a, r, c) == false && count == 3) {
                        uv_live_cell(b, r, c);
                        mvprintw(r, c, "o");
                    }
                    if (count < 2 || count > 3) {
                        uv_dead_cell(b, r, c);
                    }
                }
            }
            // Swap the universes where universe A represents the current state of the universe
            // Universe B represents the next state of the universe
            Universe *temp = a;
            a = b;
            b = temp;
            refresh();
            usleep(DELAY);
        }
    }
    // Closes the screen
    endwin();
    // Print the final state of the Universe to the specified outfile
    uv_print(a, outfile);
    // Close the outfile and free the dynamically allocated memory for each universe
    fclose(outfile);
    uv_delete(a);
    uv_delete(b);
    return 0;
}
