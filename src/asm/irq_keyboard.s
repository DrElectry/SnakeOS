bits 32

global irq1_stub
extern irq1_handler

irq1_stub:
    push dword 0
    push dword 0x21
    jmp irq_common

irq_common:
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

    call irq1_handler

    mov al, 0x20
    out 0x20, al

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
