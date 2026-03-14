#include "vga.h"
#include "stdint.h"
#define FONT_IMPLEMENTATION
#include "font.h"
#include "port.h"
#include "memory.h"

unsigned char *backbuffer_ptr;

void vga_init() {
    backbuffer_ptr = malloc(320*200);
}

void vga_pp(uint32_t x, uint32_t y, uint8_t color) {
    if (x >= VGA_WIDTH || y >= VGA_HEIGHT) return;
    volatile uint8_t* fb = backbuffer_ptr;
    fb[y * VGA_WIDTH + x] = color;
}


void vga_char(uint32_t x, uint32_t y, char c, uint8_t color) {
    if (c < 32 || c > 126) return;
    unsigned char* glyph = font[c];

    for (uint32_t row = 0; row < 16; ++row) {
        unsigned char bits = glyph[row]; // now row 0..15
        for (uint32_t col = 0; col < 8; ++col) {
            if (bits & (0x80 >> col)) {
                vga_pp(x + col, y + row, color);
            }
        }
    }
}

void vga_print(uint32_t x, uint32_t y, char* msg, uint8_t color) {
    uint32_t orig_x = x;
    while (*msg) {
        if (*msg == '\n') {
            x = orig_x;
            y += 16;  // row height = 16 now
        } else {
            vga_char(x, y, *msg, color);
            x += 8;   // 8 pixels wide
        }
        msg++;
    }
}


void vga_cls(uint8_t color) {
    memset(backbuffer_ptr, color, 64000);
    memset(VGA_ADDR, color, 64000);
}


void vga_generate_pallete() {
    uint8_t r, g, b;

    outb(0x3C8, 0);

    for (r = 0; r < 4; r++) {
        for (g = 0; g < 8; g++) {
            for (b = 0; b < 8; b++) {
                uint8_t red6   = (r * 63) / 3;
                uint8_t green6 = (g * 63) / 7;
                uint8_t blue6  = (b * 63) / 7;

                outb(0x3C9, red6);
                outb(0x3C9, green6);
                outb(0x3C9, blue6);
            }
        }
    }
}

void vga_blit(void) {
    memcpy((void*)VGA_ADDR, backbuffer_ptr, VGA_WIDTH * VGA_HEIGHT);
}
