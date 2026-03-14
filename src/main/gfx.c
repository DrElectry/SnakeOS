#include "gfx.h"
#include "stdint.h"
#include "vga.h"

void gfx_square(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color) {
    for (int i = x; i < x+width; i++) {
        for (int j = y; j < y+height; j++) {
            vga_pp(i,j,color);
        }
    }
}

void gfx_square_rounded(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t radius, uint32_t color) {
    int r2 = radius * radius;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {

            int dx = 0;
            int dy = 0;

            if (i < radius) dx = radius - i - 1;
            else if (i >= width - radius) dx = i - (width - radius);

            if (j < radius) dy = radius - j - 1;
            else if (j >= height - radius) dy = j - (height - radius);

            if (dx*dx + dy*dy <= r2) {
                vga_pp(x + i, y + j, color);
            }
            else if (dx == 0 || dy == 0) {
                vga_pp(x + i, y + j, color);
            }
        }
    }
}

void gfx_text(uint32_t x, uint32_t y, char* msg, uint32_t color, uint32_t shadow_color, uint32_t shadow_x_offset, uint32_t shadow_y_offset) {
    vga_print(x+shadow_x_offset,y+shadow_y_offset,msg,shadow_color);
    vga_print(x,y,msg,color);
}