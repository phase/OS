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
    for(int i = 0; i < strlen(str); i++)
        tmp[i] = str[i];
    return tmp;
}

int amountOfChar(string s, char c) {
    int r = 0;
    for(int i = 0; i < strlen(s); i++)
        r += s[i] == c ? 1 : 0;
    return r;
}
/*
char **split(char** buf, string s, char d) {
    char *strs[amountOfChar(s, d) + 1];
    int p = 0, j = 0;
    string buff = "";
    for(int i = 0; i < strlen(s); i++) {
        if(s[i] == d) {
            strs[p++] = copyString(buff);
            buff = "";
            j = 0;
        } else {
            buff[j++] = s[i];
        }
    }
    return strs;
}*/

#endif