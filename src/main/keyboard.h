#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "stdint.h"

#define KEYBOARD_BUFFER_SIZE 256
#define NUM_SCANCODES 256

extern uint32_t keyboard_buffer[KEYBOARD_BUFFER_SIZE];
extern uint32_t kb_head;
extern uint32_t kb_tail;
extern uint8_t scancode_state[NUM_SCANCODES];

void keyboard_push(uint32_t scancode);
uint32_t keyboard_pop();
uint32_t keyboard_last();
void keyboard_update_state(uint8_t scancode, uint8_t pressed);
char keyboard_get_char(uint32_t scancode);

#endif