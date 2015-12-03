#ifndef STRING_H
#define STRING_H 1
#include "types.h"

size_t strlen(string str) {
    size_t i = 0;
    while(str[i++]);
    return i;
}

string copyString(string str) {
    string tmp;
    for(int i = 0; i < strlen(str); i++) {
        tmp[i] = str[i];
    }
    return tmp;
}

#endif