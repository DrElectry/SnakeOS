#include "vga.h"
#include "pit.h"
#include "port.h"
#include "keyboard.h"
#include "pic.h"
#include "speaker.h"
#include "kernel.h"

static uint8_t prefix_e0 = 0;
static uint8_t prefix_f0 = 0;

// isr handlers we call from our assembly
// we just extern them because i trust extern more than headers

void isr0_handler() {
    panic("Division by zero.");
    while (1) {}
}

void isr14_handler() {
    panic("Double fault.");
    while (1) {}
}

void irq0_handler() {
    pit_handle_tick();
    beep_tick();
    //vga_print(0,0,"tick.",255);
}

void irq1_handler() {
    uint8_t scancode = inb(0x60);

    if (scancode == 0xE0) {
        prefix_e0 = 1;
        return;
    }

    if (scancode == 0xF0) {
        prefix_f0 = 1;
        return;
    }

    if (prefix_f0) {
        keyboard_update_state(scancode, 0);
        prefix_f0 = 0;
    } else {
        keyboard_update_state(scancode, 1);
        keyboard_push(scancode | (prefix_e0 ? 0x100 : 0)); 
    }

    prefix_e0 = 0;
    send_eoi(1);
}


