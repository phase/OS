#ifndef STRING_H
#define STRING_H 1
#include "types.h"

size_t strlen(string str) {
    size_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
}

#endif