#ifndef TERMINAL_H
#define TERMINAL_H 1
#include "types.h"

static int cursorX = 0, cursorY = 0;

// VGA
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
uint8_t makeColor(size_t, size_t);
uint16_t makeVgaEntry(char, uint8_t);

// Terminal functions
void terminalInit();
void terminalSetColor(uint8_t);
void terminalPutEntryAt(char, uint8_t, size_t, size_t);
void clearScreen();
void putChar(char);
void updateCursor();
void setCursor(int, int);

#endif