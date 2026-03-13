bits 32 ; the div by zero isr
; next isr/irq .s files are practically the same.

global isr0_stub
extern isr0_handler

isr0_stub:
    push byte 0  ; error code
    push byte 0  ; interrupt number
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
