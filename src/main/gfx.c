#include "gfx.h"
#include "stdint.h"
#include "vga.h"
#include "functions.h"

void gfx_square(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color) {
    for (int i = x; i < x+width; i++) {
        for (int j = y; j < y+height; j++) {
            vga_pp(i,j,color);
        }
    }
}

void gfx_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color) {
    int dx = abs((int)x2 - (int)x1);
    int dy = abs((int)y2 - (int)y1);

    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;

    int err = dx - dy;

    while (1) {
        vga_pp(x1, y1, color);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
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