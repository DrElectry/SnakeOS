#ifndef GFX_H
#define GFX_H

#define RGB233(r,g,b) (((r & 0x3) << 6) | ((g & 0x7) << 3) | (b & 0x7)) // max values are 3:7:7 inside this macro

#include "stdint.h"
#include "vga.h"

// gfx.h is created for cool ass advanced graphics
// like shadow text, rounded rectangles, you got me

void gfx_square(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
void gfx_square_rounded(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t radius, uint32_t color);
void gfx_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
void gfx_text(uint32_t x, uint32_t y, char* msg, uint32_t color, uint32_t shadow_color, uint32_t shadow_x_offset, uint32_t shadow_y_offset);

#endif