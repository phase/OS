#include "kernel.h"

uint8_t makeColor(size_t fg, size_t bg) {
    return fg | bg << 4;
}
 
uint16_t makeVgaEntry(char c, uint8_t color) {
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}
 
size_t strlen(const char* str) {
    size_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
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

void print(const char*, size_t);

void putChar(char c) {
    if (c == '\n') {
        tx = 0;
        ty++;
    }
    else if (c == '\t') {
        print("    ", tcolor);
    }
    else {
        terminalPutEntryAt(c, tcolor, tx, ty);
        if (++tx == VGA_WIDTH) {
            tx = 0;
            if (++ty == VGA_HEIGHT) ty = 0;
        }
    }
}
 
void puts(const char* data) {
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++) putChar(data[i]);
}

void print(const char* data, size_t c) {
    terminalSetColor(makeColor(c, 0x0));
    puts(data);
}

void newline() {
    putChar('\n');
}

void println(const char* data, size_t c) {
    print(data, c);
    newline();
}
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kmain. */
#endif
void kmain() {
    terminalInit();
    println("Operating System\n\tVersion 0.0.0", 0x4);
}