#include "io.h"

#include "code.h"
#include "endian.h"
#include "word.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Note: The following code was inspired by topics and pseudocode discussed during TA Eugene and TA Sahiti's lab sections. Credit goes to the TAs for their help.
// We will want to use two static 4KB or BLOCK uint8_t arrays to serve as buffers (one to store binary pairs, other to store characters)

static uint8_t *binary_buffer[BLOCK]; // used in read_pairs() and write_pairs()
static int bit_index = 0; // used to locate the index of the buffers
static uint8_t *sym_buffer[BLOCK]; // used in read_sym() & write_word()
static int buffer_index = 0;

// This function is a helper function to perform reads
// Loops calls to read() until all bytes that were specified were read or there are no more bytes to read
// Parameters: identifier for infile, pointer to a buffer, specified number of bytes to be read
// Returns the total number of bytes read
int read_bytes(int infile, uint8_t *buf, int to_read) {
    int total_bytes = 0; // Tracks the total number of bytes read
    int bytes = 0; // Tracks the number of bytes read
    while (total_bytes != to_read) {
        bytes = read(infile, buf, to_read);
        if (bytes == -1) {
            fprintf(stderr, "Invalid read.");
        }
        total_bytes += bytes;
        to_read -= bytes;
        buf += bytes;
        if (to_read == 0) {
            break;
        }
    }
    return total_bytes;
}

// This function is a helper function to perform writes()
// Similar implementation to read_bytes() except we perform write()
// Returns the number of bytes written
int write_bytes(int outfile, uint8_t *buf, int to_write) {
    int total_bytes = 0; // Tracks the total number of bytes written
    int bytes = 0; // Tracks the number of bytes written
    while (total_bytes != to_write) {
        bytes = write(outfile, buf, to_write);
        if (bytes == -1) {
            fprintf(stderr, "Invalid write.");
        }
        total_bytes += bytes;
        to_write -= bytes;
        buf += bytes;
        if (to_write == 0) {
            break;
        }
    }
    return total_bytes;
}

// This function reads in sizeof(FileHeader) bytes from an input file, swapping the endianness of the header's magic number and protection fields if the
// system's byte order isn't little endian
void read_header(int infile, FileHeader *header) {
    read_bytes(infile, header, sizeof(FileHeader));
    if (big_endian()) { // Swaps the endianness if big endian
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    if (header->magic != MAGIC) { // Verifies the magic number
        fprintf(stderr, "Invalid magic number for FileHeader");
    }
}

// This function writes sizeof(FileHeader) bytes to the output file, swapping the endianness if the system's byte order isn't little endian
void write_header(int outfile, FileHeader *header) {
    if (big_endian()) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    write_bytes(outfile, header, sizeof(FileHeader));
}

// Keeps track of the currently read symbol in the buffer
// This function returns true if there are still symbols to be read and processed, false otherwise
bool read_sym(int infile, uint8_t *sym) {
    int ending_block = -1; // Keeps track of the end number of bytes
    int bytes = read_bytes(infile, sym_buffer, BLOCK);
    sym = sym_buffer[bit_index];
    bit_index += 1;
    if (bit_index
        == BLOCK) { // If the bit index of the buffer reaches the block size, then reset the index
        bit_index = 0;
    }
    if (bytes != BLOCK) {
        ending_block = bytes + 1;
        return false;
    }
    return true;
}

// The following four helper functions are bitwise operations used for write_pairs()
static inline uint16_t code_get_bit(uint16_t code, int index) {
    uint16_t temp = index % 8;
    uint16_t mask = 1 << temp;
    code = code / 8;
    uint16_t byte = code & mask;
    return byte >> temp;
}

static inline void buffer_set_bit(void) {
    uint8_t byte = binary_buffer[buffer_index / 8];
    uint8_t temp = buffer_index % 8;
    uint8_t mask = 1 << temp;
    binary_buffer[buffer_index / 8] = byte | mask;
    return;
}

static inline void buffer_clr_bit(void) {
    uint8_t byte = binary_buffer[buffer_index / 8];
    uint8_t temp = buffer_index % 8;
    uint8_t mask = ~(1 << temp);
    binary_buffer[buffer_index / 8] = byte & mask;
    return;
}

static inline uint8_t sym_get_bit(uint8_t sym, int index) {
    uint8_t temp = index % 8;
    uint8_t mask = 1 << temp;
    sym = sym / 8;
    uint8_t byte = sym & mask;
    return byte >> temp;
}

// This function writes a pair to outfile, buffering the bits of the code followed by buffering the bits of the symbol
// Parameters: file descriptor outfile, a code of type uint16_t, a uint8_t symbol sym, and the bit-length of the code buffered (bitlen)
void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    if (big_endian()) { // Make sure endianness is little endian
        code = swap16(code);
    }
    for (int i = 0; i < bitlen; i += 1) {
        if (code_get_bit(code, i) == 1) {
            buffer_set_bit();
        } else {
            buffer_clr_bit();
        }
        buffer_index += 1;
        if (buffer_index == BLOCK) {
            write_bytes(outfile, binary_buffer, BLOCK);
            buffer_index = 0;
        }
    }
    for (int i = 0; i < 8; i += 1) {
        if (sym_get_bit(sym, i) == 1) {
            buffer_set_bit();
        } else {
            buffer_clr_bit();
        }
        buffer_index += 1;
        if (buffer_index == BLOCK * 8) {
            write_bytes(outfile, binary_buffer, BLOCK);
            buffer_index = 0;
        }
    }
    return;
}

// This is a helper function to convert the number of bits to bytes
static inline int convert_bytes(int bits) {
    if ((bits % 8) == 0) {
        return bits / 8;
    } else {
        return (bits / 8) + 1;
    }
}
// This function writes out any remaining pairs of symbols and codes to the output file
void flush_pairs(int outfile) {
    if (buffer_index != 0) {
        write_bytes(outfile, binary_buffer, convert_bytes(buffer_index));
    }
    return;
}

// This function reads a pair from the input file
// Returns true if there are still pairs left to read, otherwise false
// Credit goes to TA Eugene for heavy inspiration from his code during lab section
bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    uint16_t temp_code = 0;
    for (int i = 0; i < bitlen; i += 1) {
        if (buffer_index == 0) {
            read_bytes(infile, binary_buffer, BLOCK);
        }
        uint8_t bit
            = (binary_buffer[buffer_index / 8] & (1 << buffer_index % 8)) >> (buffer_index % 8);
        if (bit == 1) {
            temp_code |= (1 << i);
        } else {
            temp_code &= ~(1 << i);
        }
        buffer_index += 1;
        if (buffer_index == BLOCK * 8) {
            buffer_index = 0;
        }
    }
    *code = temp_code;
    uint8_t temp_sym = 0;
    for (int i = 0; i < 8; i += 1) {
        if (buffer_index == 0) {
            read_bytes(infile, binary_buffer, BLOCK);
        }
        uint8_t bit
            = (binary_buffer[buffer_index / 8] & (1 << buffer_index % 8)) >> (buffer_index % 8);
        if (bit == 1) {
            temp_sym |= (1 << i);
        } else {
            temp_sym &= ~(1 << i);
        }
        buffer_index += 1;
        if (buffer_index == BLOCK * 8) {
            buffer_index = 0;
        }
    }
    if (big_endian()) {
        *code = swap16(*code);
    }
    if (*code != STOP_CODE) {
        return true;
    } else {
        return false;
    }
}

// This function writes a word to the output file, given a Word *w
void write_word(int outfile, Word *w) {
    for (int i = 0; i < w->len; i += 1) {
        sym_buffer[bit_index] = w->syms[i];
        bit_index += 1;
        if (bit_index == BLOCK * 8) {
            write_bytes(outfile, sym_buffer, BLOCK);
            bit_index = 0;
        }
    }
}

// This function writes out any remaining symbols in the buffer to the outfile
void flush_words(int outfile) {
    if (bit_index != 0) {
        write_bytes(outfile, sym_buffer, convert_bytes(bit_index));
    }
}
