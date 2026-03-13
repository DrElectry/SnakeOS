BITS 32
global memcpy

; but dudee why do you have to use assembly for simple memcpy function???
; SPEED.

memcpy:
    push esi
    push edi
    mov edi, [esp + 12]
    mov esi, [esp + 16]
    mov ecx, [esp + 20]
    test ecx, ecx
    jz .ret

    shr ecx, 2
    rep movsd
    mov ecx, [esp + 20]
    and ecx, 3
    rep movsb
.ret:
    mov eax, [esp + 12]
    pop edi
    pop esi
    ret
