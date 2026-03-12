#include "vga.h"

void isr0_handler() {
    vga_print(0,0,"isr 0", 255);;
    while (1) {}
}

void isr8_handler() {
    vga_print(0,0,"page fault", 255);
    while (1) {}
}

void isr13_handler() {
    vga_print(0,0,"page fault", 255);
    while (1) {}
}

void isr14_handler() {
    vga_print(0,0,"double fault", 255);
    while (1) {}
}

