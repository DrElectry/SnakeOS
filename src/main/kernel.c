#include "vga.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "stdint.h"
#include "gfx.h"
#include "keyboard.h"

#define HEAP_START 0x100000
#define HEAP_END 0x200000
#define HEAP_ALIGN 16

int itoa(uint32_t value, char* buffer, int base) { // itoa for this keyboard test
    if (base < 2 || base > 16) { buffer[0] = '\0'; return 0; }

    char temp[33];
    int i = 0;

    do {
        uint32_t digit = value % base;
        temp[i++] = (digit < 10) ? ('0' + digit) : ('A' + (digit - 10));
        value /= base;
    } while (value > 0);

    int j = 0;
    while (i > 0) {
        buffer[j++] = temp[--i];
    }
    buffer[j] = '\0';
    return j;
}

unsigned char *heap_ptr = (unsigned char*)HEAP_START;

// we have to implement bitmap malloc for double buffering
// we CAN do double buffering in the binary, but having our binary >64kb is bad and im not interested in doing it

void* malloc(uint32_t size) {
    size = (size + HEAP_ALIGN - 1) & ~(HEAP_ALIGN - 1);
    if (heap_ptr + size > (unsigned char*)HEAP_END) {
        return (void*)0;
    }
    void* ptr = heap_ptr;
    heap_ptr += size;
    return ptr;
}

static char keymap[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', 0,
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z',
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

char get_char(uint32_t scancode) {
    if (scancode & 0xFF00) return 0; // ignore release/extend
    uint8_t code = scancode & 0xFF;
    if (code >= 128) return 0;
    return keymap[code];
}

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