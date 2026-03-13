#include "vga.h"
#include "pit.h"

// isr handlers we call from our assembly
// we just extern them because i trust extern more than headers

void isr0_handler() {
    vga_print(0,0,"Division by 0.", 255);
    while (1) {}
}

void irq0_handler() {
    pit_handle_tick();
    //vga_print(0,0,"tick.",255);
}

