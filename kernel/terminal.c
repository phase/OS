#include "terminal.h"
#include "system.h"

uint8_t makeColor(size_t fg, size_t bg) {
    return fg | bg << 4;
}
 
uint16_t makeVgaEntry(char c, uint8_t color) {
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}

size_t ty;
size_t tx;
uint8_t tcolor;
uint16_t* tbuf;

void clearScreen() {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            tbuf[index] = makeVgaEntry(' ', tcolor);
        }
    }
}

void terminalInit() {
    ty = 0;
    tx = 0;
    tcolor = makeColor(0x7, 0x0);
    tbuf = (uint16_t*) 0xB8000;
    clearScreen();
}
 
void terminalSetColor(uint8_t color) {
    tcolor = color;
}
 
void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    tbuf[index] = makeVgaEntry(c, color);
}

void putChar(char c) {
    if (c == '\n') {
        tx = 0;
        ty++;
    }
    else {
        terminalPutEntryAt(c, tcolor, tx, ty);
        if (++tx == VGA_WIDTH) {
            tx = 0;
            if (++ty == VGA_HEIGHT) ty = 0;
        }
    }
}

void updateCursor(){
    unsigned pos;
    pos = cursorY * VGA_WIDTH + cursorX;
    outportb(0x3D4, 14);
    outportb(0x3D5, pos >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, pos);
}

void setCursor(int x, int y) {
    cursorX = x;
    cursorY = y;
    updateCursor();
}