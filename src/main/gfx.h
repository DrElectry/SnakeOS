#ifndef GFX_H
#define GFX_H

#define RGB233(r,g,b) (((r & 0x3) << 6) | ((g & 0x7) << 3) | (b & 0x7)) // max values are 3:7:7 inside this macro

#include "stdint.h"
#include "vga.h"

void gfx_square(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color) {
    for (int i = x; i < x+width; i++) {
        for (int j = y; j < y+height; j++) {
            vga_pp(i,j,color);
        }
    }
}

#endif