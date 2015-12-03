#ifndef SYSTEM_H
#define SYSTEM_H 1

#include "types.h"

uint8 in(uint16 _port) {
    uint8 rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void out(uint16 _port, uint8 _data) {
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

#endif