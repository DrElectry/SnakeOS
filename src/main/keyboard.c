#include "keyboard.h"

uint32_t keyboard_buffer[KEYBOARD_BUFFER_SIZE];
uint32_t kb_head = 0;
uint32_t kb_tail = 0;
uint8_t scancode_state[NUM_SCANCODES];

void keyboard_push(uint32_t scancode) {
    keyboard_buffer[kb_head] = scancode;
    kb_head = (kb_head + 1) % KEYBOARD_BUFFER_SIZE;
    if (kb_head == kb_tail) {
        kb_tail = (kb_tail + 1) % KEYBOARD_BUFFER_SIZE;
    }
}

uint32_t keyboard_pop() {
    if (kb_head == kb_tail) return 0;
    uint32_t scancode = keyboard_buffer[kb_tail];
    kb_tail = (kb_tail + 1) % KEYBOARD_BUFFER_SIZE;
    return scancode;
}

uint32_t keyboard_last() {
    if (kb_head == kb_tail) return 0;
    uint32_t last_index = (kb_head == 0) ? (KEYBOARD_BUFFER_SIZE - 1) : (kb_head - 1);
    return keyboard_buffer[last_index];
}

void keyboard_update_state(uint8_t scancode, uint8_t pressed) {
    scancode_state[scancode] = pressed;
}