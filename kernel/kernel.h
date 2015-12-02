#ifndef KERNEL_H
#define KERNEL_H 1

//Standard Library
#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

// Hardware text mode color constants
enum VGA_COLOR {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};

// Terminal functions
void terminalInit();
void terminalSetColor(uint8_t);
void terminalPutEntryAt(char, uint8_t, size_t, size_t);
void clearScreen();

// Printing to screen
void print(const char*);
void printc(const char*, enum VGA_COLOR);
void putChar(char);

#endif