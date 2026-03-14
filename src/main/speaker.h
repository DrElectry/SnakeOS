#ifndef SPEAKER_H
#define SPEAKER_H

#define PC_SPEAKER_CONTROL 0x61
#define PIT_CHANNEL2 0x42
#define PIT_COMMAND 0x43
#include "stdint.h"

// pc speaker is the easiest if you want "some" noise

typedef struct {
    uint8_t active;
    uint32_t frequency;
    uint32_t duration;
    uint32_t elapsed;
} speaker_state;

void beep(uint32_t frequency, uint32_t duration);
void beep_shut_the_fuck_up();
void beep_tick();

#endif