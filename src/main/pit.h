#ifndef PIT_H
#define PIT_H

// we require programmable interval timer, to access the same tick speed of our game, no matter what the cpu clock is

#define PIT_FREQUENCY 1193182
#define PIT_CHANNEL0 0x40
#define PIT_COMMAND  0x43
#define PIT_CHANNEL2  0x42

#include "stdint.h"

static volatile uint32_t ticks = 0;

void pit_init(uint32_t hz);
void pit_set_frequency(uint32_t hz);
uint32_t pit_get_global_ticks();
void pit_handle_tick();

#endif