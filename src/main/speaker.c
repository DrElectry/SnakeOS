#include "stdint.h"
#include "speaker.h"
#include "port.h"

static speaker_state speaker;

void beep(uint32_t frequency, uint32_t duration) {
    if (frequency == 0) {
        speaker.active = 0;
        outb(PC_SPEAKER_CONTROL, inb(PC_SPEAKER_CONTROL) & ~0x03);
        return;
    }
    uint32_t divisor = 1193182 / frequency;
    outb(PIT_COMMAND, 0xB6);
    outb(PIT_CHANNEL2, divisor & 0xFF);
    outb(PIT_CHANNEL2, divisor >> 8);
    uint8_t ppi = inb(PC_SPEAKER_CONTROL);
    outb(PC_SPEAKER_CONTROL, ppi | 0x03);
    speaker.active = 1;
    speaker.frequency = frequency;
    speaker.duration = duration;
    speaker.elapsed = 0;
}

void beep_shut_the_fuck_up() {
    speaker.active = 0;
    outb(PC_SPEAKER_CONTROL, inb(PC_SPEAKER_CONTROL) & ~0x03);
}

void beep_tick() {
    if (!speaker.active) return;
    speaker.elapsed++;
    if (speaker.elapsed >= speaker.duration) {
        beep_shut_the_fuck_up();
    }
}
