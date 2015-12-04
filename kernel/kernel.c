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

string input;

void readString() {
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
                buffstr[i++] = chars[in];
            }
            else if(in == 14) { //backspace
                buffstr[i--] = 0;
                clearCurrentLine();
                print(buffstr, getTerminalColor());
            }
            else if(in == 28) { //enter
                reading = 0;
            }
        }
    }
    buffstr[i] = 0;
    input = buffstr;
    putChar('\n');
    println(input, 0x5);
    terminalSetColor(0x04);
    readString();
}

void kmain() {
    terminalInit();
    println("Operating System\n    Version -0", 0x3);
    println("Input: ", 0x04);
    readString();
    println("Back out", 0x04);
}