#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// this header is for helper functions like itoa

#include "stdint.h"

static int itoa(uint32_t value, char* buffer, int base) {
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

static void int_to_str(int n, char* s) {
    int i = 0;
    if (n == 0) {
        s[0] = '0'; s[1] = 0; return;
    }
    while (n > 0) {
        s[i++] = '0' + n % 10; n /= 10;
    }
    s[i] = 0;
    int j = 0, k = i - 1;
    while (j < k) {
        char t = s[j]; s[j] = s[k]; s[k] = t; j++; k--;
    }
}

#endif