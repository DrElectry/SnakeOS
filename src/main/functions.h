#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// this header is for helper functions like itoa

#include "stdint.h"

int itoa(uint32_t value, char* buffer, int base) {
    if (base < 2 || base > 16) { buffer[0] = '\0'; return 0; }

    char temp[33];
    int i = 0;

    do {
        uint32_t digit = value % base;
        temp[i++] = (digit < 10) ? ('0' + digit) : ('A' + (digit - 10));
        value /= base;
    } while (value > 0);

    int j = 0;
    while (i > 0) {
        buffer[j++] = temp[--i];
    }
    buffer[j] = '\0';
    return j;
}

#endif