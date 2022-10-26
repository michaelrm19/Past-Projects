#include "universe.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// struct definition for a Universe with specified fields from lab document
struct Universe {
    int rows;
    int cols;
    bool **grid;
    bool toroidal;
};

// This function is a constructor function that creates a Universe
// Parameters: rows and cols are of type int and specify the dimensions of the boolean grid
// toroidal is of type boolean and specifies if the Universe is toroidal (true) or flat (false)
// Returns a pointer to a Universe
Universe *uv_create(int rows, int cols, bool toroidal) {
    // Dynamically allocate memory for the Universe
    Universe *u = (Universe *) calloc(1, sizeof(Universe));
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    // Dynamically allocate memory for each row and column for the grid
    u->grid = (bool **) calloc(rows, sizeof(bool *));
    for (int i = 0; i < rows; i++) {
        u->grid[i] = (bool *) calloc(cols, sizeof(bool));
    }
    return u;
}

// This function serves as a helper function that checks if the specified cell is in the bounds of the Universe's grid
// Parameters: Pointer to the specified Universe, r and c are of type int and specify the location of a cell
// Returns a boolean true if the cell is in bounds, false otherwise
static inline bool inbounds(Universe *u, int r, int c) {
    if (r < 0 || c < 0 || r >= u->rows || c >= u->cols) {
        return false;
    } else {
        return true;
    }
}

// This function serves as a destructor function for a Universe
// Parameters: Pointer to the specified Universe
// Frees all memory allocated for the Universe, from the inside to the outside
void uv_delete(Universe *u) {
    for (int r = 0; r < u->rows; r++) {
        free(u->grid[r]);
    }
    free(u->grid);
    free(u);
    return;
}

// This function serves as an accessor function
// Returns the number of rows in a specified Universe
int uv_rows(Universe *u) {
    return u->rows;
}

// This function serves as an accessor function
// Returns the number of cols in a specified Universe
int uv_cols(Universe *u) {
    return u->cols;
}

// This function serves as a manipulator function
// Marks a cell at row r and column c as live (true)
// If the specified r and c are out of bounds, nothing happens
void uv_live_cell(Universe *u, int r, int c) {
    if (inbounds(u, r, c)) {
        u->grid[r][c] = true;
    }
    return;
}

// This function serves as a manipulator functions
// Marks a cell at row r and column c as dead (false)
// If the specified r and c are out of bounds, nothing happens
void uv_dead_cell(Universe *u, int r, int c) {
    if (inbounds(u, r, c)) {
        u->grid[r][c] = false;
    }
    return;
}

// This function serves as an accessor function
// Returns the boolean value of a specified cell at row r and column c
// Returns false if row r and column c are out of bounds
bool uv_get_cell(Universe *u, int r, int c) {
    if (inbounds(u, r, c)) {
        return u->grid[r][c];
    } else {
        return false;
    }
}

// This function populates the Universe with row-column pairs read in from infile
// Returns true if the universe was successfully populated
// Returns false if a row-column pair is out of bounds or is considered invalid input
bool uv_populate(Universe *u, FILE *infile) {
    int r, c = 0;
    while (fscanf(infile, "%d %d \n", &r, &c) != -1) {
        if (inbounds(u, r, c)) {
            u->grid[r][c] = true;
        } else {
            return false;
        }
    }
    return true;
}

// This function returns the number of live neighbors adjacent to a cell at row r and column c
// If the universe is flat, only valid neighbors (in bounds) will be counted
// If the universe is toroidal, all neighbors are valid (simply wrap to the other side of the grid)
int uv_census(Universe *u, int r, int c) {
    int count = 0;
    int neighbor_row = 0;
    int neighbor_col = 0;
    // There will be two cases: toroidal or flat
    if (u->toroidal) {
        // Loop from r-1 to r+1, iterating through each column
        for (int i = r - 1; i <= r + 1; i++) {
            for (int j = c - 1; j <= c + 1; j++) {
                // If row r and column c is the location of the specified cell, don't count its boolean value
                if (i == r && j == c) {

                } else {
                    // If a neighbor is out of bounds in a toroidal universe, implement formula to wrap to the other side of the grid
                    if (inbounds(u, i, j) == false) {
                        neighbor_row = (i + u->rows) % u->rows;
                        neighbor_col = (j + u->cols) % u->cols;
                        if (uv_get_cell(u, neighbor_row, neighbor_col)) {
                            count++;
                        }
                    } else {
                        if (uv_get_cell(u, i, j)) {
                            count++;
                        }
                    }
                }
            }
        }
    } else {
        for (int i = r - 1; i <= r + 1; i++) {
            for (int j = c - 1; j <= c + 1; j++) {
                // If row r and column c is the location of the specified cell, don't count its boolean value (do nothing)
                if (i == r && j == c) {

                } else {
                    // If the universe is flat and a neighbor is out of bounds, don't count its boolean value (invalid neighbor)
                    if (inbounds(u, i, j) == false) {

                    } else {
                        if (uv_get_cell(u, i, j)) {
                            count++;
                        }
                    }
                }
            }
        }
    }
    return count;
}

// This function prints out the universe to outfile
// Live cells will be indicated by an 'o'
// Dead cells will be indicated by a '.'
// Always print out the flattened universe even if the universe is toroidal
void uv_print(Universe *u, FILE *outfile) {
    for (int i = 0; i < u->rows; i++) {
        for (int j = 0; j < u->cols; j++) {
            if (u->grid[i][j] == true) {
                fputc('o', outfile);
            } else {
                fputc('.', outfile);
            }
        }
        // Print a new line after each row is finished
        fputc('\n', outfile);
    }
}
