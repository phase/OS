#include "kernel.h"

void puts(string data) {
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++) putChar(data[i]);
}

void print(string data, size_t c) {
    terminalSetColor(makeColor(c, 0x0));
    puts(data);
}

void newline() {
    putChar('\n');
}

void println(string data, size_t c) {
    print(data, c);
    newline();
}
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kmain. */
#endif
void kmain() {
    terminalInit();
    println("Operating System\n    Version 0.0.0", 0x3);
}