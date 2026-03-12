BITS 32
SECTION .text.entry

GLOBAL boot_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

extern kernel_main

; the existence of this boostrap is not miserable trust me
; without this prestige piece of code we should ve placed our _start function at the very top of the binary, resulting insufferable coding

boot_start:
    call kernel_main

.halt:
    hlt
    jmp .halt
