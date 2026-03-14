BITS 32
global memset

; but duuude you wrote malloc in C, why do you have to write those functions in assembly??
; SPEED.

memset:
    push edi
    mov edi, [esp + 8]      ; dest
    mov eax, [esp + 12]     ; val
    mov ecx, [esp + 16]     ; count
    test ecx, ecx
    jz .done

    ; replicate byte across eax -> 0xAAAAAAAA if val = 0xAA
    mov edx, eax
    shl edx, 8
    or  eax, edx
    mov edx, eax
    shl edx, 16
    or  eax, edx

    mov edx, ecx
    shr ecx, 2               ; number of dwords
    rep stosd

    mov ecx, edx
    and ecx, 3
    rep stosb

.done:
    mov eax, [esp + 8]
    pop edi
    ret