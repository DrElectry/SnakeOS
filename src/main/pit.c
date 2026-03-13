#include "pit.h"
#include "port.h"
#include "stdint.h"

void pit_init(uint32_t hz) {
    uint16_t divisor = (uint16_t)(PIT_FREQUENCY / hz);

    outb(PIT_COMMAND, 0x36);

    outb(PIT_CHANNEL0, (uint8_t)(divisor & 0xFF));

    outb(PIT_CHANNEL0, (uint8_t)((divisor >> 8) & 0xFF));
}

void pit_set_frequency(uint32_t hz) {
    uint16_t divisor = (uint16_t)(PIT_FREQUENCY / hz);

    outb(PIT_COMMAND, 0x36);

    outb(PIT_CHANNEL0, divisor & 0xFF);
    outb(PIT_CHANNEL0, (divisor >> 8) & 0xFF);
}

uint32_t pit_get_global_ticks() {
    return ticks;
}

void pit_send_eoi() {
    outb(0x20, 0x20);
}

void pit_handle_tick() {
    ticks++;
}