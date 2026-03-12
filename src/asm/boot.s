BITS 32
SECTION .text.entry

GLOBAL boot_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

extern kernel_main

boot_start:
    call kernel_main

.halt:
    hlt
    jmp .halt
