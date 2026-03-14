#ifndef MEMORY_H
#define MEMORY_H

#include "stdint.h"

#define HEAP_START 0x100000
#define HEAP_END 0x200000
#define HEAP_ALIGN 16

extern void *memcpy(void *dest, const void *src, unsigned int n);
extern void *memset(void *dest, int val, unsigned int count);
void* malloc(uint32_t size);

#endif