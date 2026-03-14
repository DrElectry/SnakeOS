#ifndef VGA_H
#define VGA_H

#include "stdint.h"

#define VGA_ADDR ((void*)0xA0000)
#define VGA_WIDTH 320
#define VGA_HEIGHT 200

void vga_cls(uint8_t color);
void vga_pp(uint32_t x, uint32_t y, uint8_t color);
void vga_char(uint32_t x, uint32_t y, char c, uint8_t color);
void vga_print(uint32_t x, uint32_t y, char* msg, uint8_t color);
void vga_init();

void vga_generate_pallete(void);
void vga_blit(void);

#endif
