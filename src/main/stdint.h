#ifndef STDINT_H
#define STDINT_H

// fully barebones!, NO system stdint
// actually, because im using default linux gcc to compile kernel with no stdlib flag
// which means that it removes EVERY std*.h file accessible from the C code

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;

typedef char int8_t;
typedef short int16_t;
typedef long int32_t;

#endif