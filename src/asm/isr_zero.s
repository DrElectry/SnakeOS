bits 32

global isr0_stub
global isr8_stub
global isr13_stub
global isr14_stub
extern isr0_handler
extern isr8_handler
extern isr13_handler
extern isr14_handler

isr0_stub:
    push byte 0  ; error code
    push byte 0  ; interrupt number
    jmp isr_common

isr8_stub:
    push byte 8  ; interrupt number (error code already pushed by CPU for #DF)
    jmp isr_common

isr13_stub:
    push byte 13 ; interrupt number (error code already pushed by CPU for #GP)
    jmp isr_common

isr14_stub:
    push byte 14 ; interrupt number (error code already pushed by CPU for #PF)
    jmp isr_common

isr_common:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr0_handler

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
