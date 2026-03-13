#include "vga.h"
#include "idt.h"
#include "pic.h"

void kernel_main(void) {
    idt_init();
    pic_remap();

    asm volatile ("sti");

    vga_generate_pallete();
    for (int y = 0; y < 200; y++) {
        unsigned char color = y * 255 / 199;
        for (int x = 0; x < 320; x++) {
            vga_pp(x, y, color);
        }
    }
    
    while (1) {
        asm volatile("hlt");
    }
}