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

const char chars[256] =    {
     0 ,  0 , '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=',  0 ,'\t', 'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']',  0 ,  0 ,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
   '\'', '`',  0 ,'\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/',  0 , '*',  0 , ' ',  0 ,
};

string readString() {
    char buff;
    string buffstr;
    uint8 i = 0;
    uint8 reading = 1;
    while(reading) {
        if(inportb(0x64) & 0x1) {
            //putChar(inportb(0x60));
            uint8 in = inportb(0x60);
            if(chars[in]) {
                putChar(chars[in]);
                buffstr[i] = chars[in];
                i++;
            }
        }
    }
    buffstr[i] = 0;                   
    return buffstr;
}
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kmain. */
#endif
void kmain() {
    terminalInit();
    println("Operating System\n    Version 0.0.0", 0x3);
    setCursor(5, 6);
    string input = readString();
    println(input, 0x4);
}