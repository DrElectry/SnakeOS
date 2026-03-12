#include "vga.h"

void kernel_main(void) {

    vga_generate_pallete();
    vga_cls(0);

    vga_print(0, 0, "Hello, world!", 255);

    int x0 = 219, y0 = 99;
    int rect_width = 100;
    int rect_height = 100;

    for (int y = y0; y < 200; y++) {
        for (int x = x0; x < 320; x++) {
            int color_index = ((y - y0) * rect_width + x) * 256 / (rect_width * rect_height);
            vga_pp(x, y, color_index);
        }
    }

    while (1) {
        asm volatile("hlt");
    }
}