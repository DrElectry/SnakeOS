#ifndef PIC_H
#define PIC_H

#include "stdint.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01


void pic_remap();
void pic_unmask_irq(uint8_t irq);
static inline void send_eoi(unsigned char irq);

#endif
