#include "stdint.h"
#include "memory.h"

unsigned char *heap_ptr = (unsigned char*)HEAP_START;

// we have to implement bitmap malloc for double buffering
// we CAN do double buffering in the binary, but having our binary >64kb is bad and im not interested in doing it

void* malloc(uint32_t size) {
    size = (size + HEAP_ALIGN - 1) & ~(HEAP_ALIGN - 1);
    if (heap_ptr + size > (unsigned char*)HEAP_END) {
        return (void*)0;
    }
    void* ptr = heap_ptr;
    heap_ptr += size;
    return ptr;
}