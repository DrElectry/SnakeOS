#include "vga.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "stdint.h"
#include "gfx.h"

#define HEAP_START 0x100000
#define HEAP_END 0x200000
#define HEAP_ALIGN 16

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

void kernel_main(void) {
    idt_init();
    pic_remap();
    pit_init(360);
    pic_unmask_irq(0);

    asm volatile("sti");

    vga_init();

    vga_generate_pallete();

    while (1) {
        uint32_t t = pit_get_global_ticks();

        if (t % 360 >= 180) {
            vga_cls(RGB233(3,0,0));
        } else {
            vga_cls(RGB233(0,0,7));
        }

        vga_print(0,1,"Hello, world!",RGB233(0,0,0));
        vga_print(0,0,"Hello, world!",RGB233(3,7,7));

        gfx_square(80,80,50,50,RGB233(0,7,0));


        vga_blit();
        asm volatile("hlt");
    }
}
