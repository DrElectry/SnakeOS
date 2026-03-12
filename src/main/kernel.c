typedef unsigned char uint8_t;
typedef unsigned long uint32_t;
#define FB_ADDR 0xA0000
#define FB_WIDTH 320
#define FB_HEIGHT 200

#define FONT_IMPLEMENTATION
#include "font.h"

void set_pixel(uint32_t x, uint32_t y, uint8_t color) {
    if (x >= FB_WIDTH || y >= FB_HEIGHT) return;
    volatile uint8_t* fb = (volatile uint8_t*)FB_ADDR;
    fb[y * FB_WIDTH + x] = color;
}

void draw_char(uint32_t x, uint32_t y, char c, uint8_t color) {
    if (c < 32 || c > 126) return;
    unsigned char* glyph = letters[c - 32];

    for (uint32_t i = 0; i < 13; ++i) {
        uint32_t row = 12 - i;
        unsigned char bits = glyph[row];
        for (uint32_t col = 0; col < 8; ++col) {
            if (bits & (0x80 >> col)) { // check if the bit is 1
                set_pixel(x + col, y + i, color);
            }
        }
    }
}

void print(uint32_t x, uint32_t y, char* msg, uint8_t color) {
    uint32_t orig_x = x;
    while (*msg) {
        if (*msg == '\n') {
            x = orig_x;
            y += 13;
        } else {
            draw_char(x, y, *msg, color);
            x += 8;
        }
        msg++;
    }
}

void kernel_main(void) {
    for (uint32_t y = 0; y < FB_HEIGHT; ++y) {
        for (uint32_t x = 0; x < FB_WIDTH; ++x) {
            set_pixel(x, y, 0);
        }
    }

    print(0,0,"Insert mario here.",15);

    while(1) asm("hlt");
}