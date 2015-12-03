#ifndef STRING_H
#define STRING_H 1
#include "types.h"

size_t strlen(string str) {
    size_t i = 0;
    while(str[i++]);
    return i;
}

#endif