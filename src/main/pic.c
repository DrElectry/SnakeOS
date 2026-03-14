#include "pic.h"
#include "port.h"
#include "stdint.h"

void pic_unmask_irq(uint8_t irq) {
    uint16_t port;
    uint8_t mask;

    if (irq < 8) {
        port = 0x21;
    } else if (irq < 16) {
        port = 0xA1;
        irq -= 8;
    } else {
        return;
    }

    mask = inb(port);
    mask &= ~(1 << irq);
    outb(port, mask);
}


void send_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(0xA0, 0x20);   // slave
    }
    outb(0x20, 0x20);       // master
}


void pic_remap() {
    uint8_t a1, a2;

    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);

    outb(PIC1_DATA, 4);
    outb(PIC2_DATA, 2);

    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);

    // Mask all interrupts
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
}
