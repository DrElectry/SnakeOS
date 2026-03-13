#include "vga.h"
#include "pit.h"

void isr0_handler() {
    vga_print(0,0,"Division by 0.", 255);
    while (1) {}
}

void irq0_handler() {
    pit_handle_tick();
    //vga_print(0,0,"tick.",255);
}

