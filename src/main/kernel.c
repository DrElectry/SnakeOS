#include "vga.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"

void kernel_main(void) {
    idt_init();
    pic_remap();
    pit_init(360);
    pic_unmask_irq(0);

    asm volatile("sti");

    vga_generate_pallete();

    while (1) {
        uint32_t t = pit_get_global_ticks();

        for (int y = 0; y < 200; y++) {
            unsigned char color = ((y + t) % 200) * 255 / 199;
            for (int x = 0; x < 320; x++) {
                vga_pp(x, y, color);
            }
        }

        vga_print(0,0,"Hello",255);

        asm volatile("hlt");
    }
}