#include "kernel.h"

uint8_t makeColor(enum VGA_COLOR fg, enum VGA_COLOR bg) {
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
    tcolor = makeColor(COLOR_LIGHT_GREY, COLOR_BLACK);
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

void print(const char*);

void putChar(char c) {
    if (c == '\n') {
        tx = 0;
        ty++;
    }
    else if (c == '\t') {
        print("    ");
    }
    else {
        terminalPutEntryAt(c, tcolor, tx, ty);
        if (++tx == VGA_WIDTH) {
            tx = 0;
            if (++ty == VGA_HEIGHT) ty = 0;
        }
    }
}
 
void print(const char* data) {
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++) putChar(data[i]);
}

void printc(const char* data, enum VGA_COLOR fg) {
    terminalSetColor(makeColor(fg, COLOR_BLACK));
    print(data);
}
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kmain. */
#endif
void kmain() {
    terminalInit();
    printc("Operating System\n\tVersion 0.0.0", COLOR_BLUE);
}