#include "kernel.h"
#include "terminal.h"
 
size_t strlen(const char* str) {
    size_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
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
    println("Operating System\n    Version 0.0.0", 0x3);
}