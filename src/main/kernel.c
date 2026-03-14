#include "vga.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "stdint.h"
#include "gfx.h"
#include "keyboard.h"
#include "functions.h"

void kernel_main(void) {
    idt_init();
    pic_remap();
    pit_init(360);
    pic_unmask_irq(0);
    pic_unmask_irq(1);

    asm volatile("sti");
    
    vga_init();
    vga_generate_pallete();

    while (1) {
        uint32_t scancode = keyboard_pop();
        if (scancode) {
            char buf[16];
            int len = itoa(scancode, buf, 16);

            uint8_t code = scancode & 0xFF;
            switch (code) {
                case 0x11: // w
                    vga_cls(RGB233(0,7,0));
                    break;
                case 0x1F: // s
                    vga_cls(RGB233(0,7,7));
                    break;
                case 0x1E: // a
                    vga_cls(RGB233(7,7,0));
                    break;
                case 0x20: // d
                    vga_cls(RGB233(7,0,0));
                    break;
            }
        }

        gfx_text(0,0,"SNAKE OS", RGB233(3,7,7), RGB233(2,5,5), 1,1);

        gfx_text(0,13,"Test by WASD", RGB233(3,7,7), RGB233(2,5,5), 1,1);

        gfx_square_rounded(100,103,50,50,15,RGB233(0,2,1));
        gfx_square_rounded(99,99,52,52,15,RGB233(0,3,1));
        gfx_square_rounded(100,100,50,50,15,RGB233(0,7,1));

        vga_blit();
        asm volatile("hlt");
    }
}