#include "idt.h"
#include "stdint.h"

extern void isr0_stub();

void idt_set_gate(uint8_t n, uint32_t isr, uint16_t selector, uint8_t flags) {
    idt[n].isr_low   = isr & 0xFFFF;         // lower 16 bits
    idt[n].kernel_cs = selector;             // code segment selector
    idt[n].reserved  = 0;                    // always zero
    idt[n].attributes = flags;               // type and flags
    idt[n].isr_high  = (isr >> 16) & 0xFFFF; // higher 16 bits
}

static idtr_t idtr;

void idt_init() {
    idtr.limit = (sizeof(idt_entry_t) * 256) - 1;
    idtr.base  = (uint32_t)&idt;

    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    idt_set_gate(0,  (uint32_t)isr0_stub,  0x08, 0x8E);

    asm volatile ("lidt (%0)" : : "r" (&idtr));
}
