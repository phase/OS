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

string readString() {
    char buff;
    string buffstr;
    uint8 i = 0;
    uint8 reading = 1;
    while(reading) {
        if(inportb(0x64) & 0x1) {
            //putChar(inportb(0x60));
            switch(inportb(0x60)) {
            case 1:
                //escape button
                i = 0;
                break;
            case 2:
                putChar('1');
                buffstr[i] = '1';
                i++;
                break;
            case 3:
                putChar('2');
                buffstr[i] = '2';
                i++;
                break;
            case 4:
                putChar('3');
                buffstr[i] = '3';
                i++;
                break;
            case 5:
                putChar('4');
                buffstr[i] = '4';
                i++;
                break;
            case 6:
                putChar('5');
                buffstr[i] = '5';
                i++;
                break;
            case 7:
                putChar('6');
                buffstr[i] = '6';
                i++;
                break;
            case 8:
                putChar('7'); //Is called when mouse moves for some reason
                buffstr[i] = '7';
                i++;
                break;
            case 9:
                putChar('8');
                buffstr[i] = '8';
                i++;
                break;
            case 10:
                putChar('9');
                buffstr[i] = '9';
                i++;
                break;
            case 11:
                putChar('0');
                buffstr[i] = '0';
                i++;
                break;
            case 12:
                putChar('-');
                buffstr[i] = '-';
                i++;
                break;
            case 13:
                putChar('=');
                buffstr[i] = '=';
                i++;
                break;
            case 14:
                putChar('\b');
                i--;
                buffstr[i] = 0;
                break;
            /* case 15:
                putChar('\t');          Tab button
                buffstr[i] = '\t';
                i++;
                break;*/
            case 16:
                putChar('q');
                buffstr[i] = 'q';
                i++;
                break;
            case 17:
                putChar('w');
                buffstr[i] = 'w';
                i++;
                break;
            case 18:
                putChar('e');
                buffstr[i] = 'e';
                i++;
                break;
            case 19:
                putChar('r');
                buffstr[i] = 'r';
                i++;
                break;
            case 20:
                putChar('t');
                buffstr[i] = 't';
                i++;
                break;
            case 21:
                putChar('y');
                buffstr[i] = 'y';
                i++;
                break;
            case 22:
                putChar('u');
                buffstr[i] = 'u';
                i++;
                break;
            case 23:
                putChar('i');
                buffstr[i] = 'i';
                i++;
                break;
            case 24:
                putChar('o');
                buffstr[i] = 'o';
                i++;
                break;
            case 25:
                putChar('p');
                buffstr[i] = 'p';
                i++;
                break;
            case 26:
                putChar('[');
                buffstr[i] = '[';
                i++;
                break;
            case 27:
                putChar(']');
                buffstr[i] = ']';
                i++;
                break;
            case 28:
               // putChar('\n');
               // buffstr[i] = '\n';
                  i++;
               reading = 0;
                break;
        /*  case 29:
                putChar('q'); // Left Control
                buffstr[i] = 'q';
                i++;
                break;*/
            case 30:
                putChar('a');
                buffstr[i] = 'a';
                i++;
                break;
            case 31:
                putChar('s');
                buffstr[i] = 's';
                i++;
                break;
            case 32:
                putChar('d');
                buffstr[i] = 'd';
                i++;
                break;
            case 33:
                putChar('f');
                buffstr[i] = 'f';
                i++;
                break;
            case 34:
                putChar('g');
                buffstr[i] = 'g';
                i++;
                break;
            case 35:
                putChar('h');
                buffstr[i] = 'h';
                i++;
                break;
            case 36:
                putChar('j');
                buffstr[i] = 'j';
                i++;
                break;
            case 37:
                putChar('k');
                buffstr[i] = 'k';
                i++;
                break;
            case 38:
                putChar('l');
                buffstr[i] = 'l';
                i++;
                break;
            case 39:
                putChar(';');
                buffstr[i] = ';';
                i++;
                break;
            case 40:
                putChar((char)44);               //   Single quote (')
                buffstr[i] = (char)44;
                i++;
                break;
            case 41:
                putChar((char)44);               // Back tick (`)
                buffstr[i] = (char)44;
                i++;
                break;
        /* case 42:                                 Left shift 
                putChar('q');
                buffstr[i] = 'q';
                i++;
                break;
            case 43:                                 \ (< for somekeyboards)   
                putChar((char)92);
                buffstr[i] = 'q';
                i++;
                break;*/
            case 44:
                putChar('z');
                buffstr[i] = 'z';
                i++;
                break;
            case 45:
                putChar('x');
                buffstr[i] = 'x';
                i++;
                break;
            case 46:
                putChar('c');
                buffstr[i] = 'c';
                i++;
                break;
            case 47:
                putChar('v');
                buffstr[i] = 'v';
                i++;
                break;                
            case 48:
                putChar('b');
                buffstr[i] = 'b';
                i++;
                break;               
            case 49:
                putChar('n');
                buffstr[i] = 'n';
                i++;
                break;                
            case 50:
                putChar('m');
                buffstr[i] = 'm';
                i++;
                break;               
            case 51:
                putChar(',');
                buffstr[i] = ',';
                i++;
                break;                
            case 52:
                putChar('.');
                buffstr[i] = '.';
                i++;
                break;            
            case 53:
                putChar('/');
                buffstr[i] = '/';
                i++;
                break;            
            case 54:
                putChar('.');
                buffstr[i] = '.';
                i++;
                break;            
            case 55:
                putChar('/');
                buffstr[i] = '/';
                i++;
                break;            
            /*case 56:
                putChar(' ');           Right shift
                buffstr[i] = ' ';
                i++;
                break;*/           
            case 57:
                putChar(' ');
                buffstr[i] = ' ';
                i++;
                break;
            }
        }
    }
    buffstr[i] = 0;                   
    return buffstr;
}