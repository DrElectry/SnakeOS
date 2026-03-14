org 0x7c00
bits 16

start:
    jmp main ; so we dont execute disk read without the call inside main

GDT: 
	dd 0                
	dd 0 
	
	dw 0xFFFF
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0
	
	dw 0xFFFF
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0
END_GDT:

GDT_PTR: 
	dw END_GDT - GDT - 1
	dd GDT
	
CODE_SEG equ 0x08
DATA_SEG equ 0x10

disk_load:
  pusha

  push dx

  mov ah, 0x02
  mov al, dh
  mov ch, 0
  mov dh, 0
  mov cl, 2

  int 0x13

  pop dx
   
  ; Check carry flag.
  jc disk_error
   
  cmp al, dh
  jne disk_error

  popa
  ret
 
disk_error:
    hlt
    jmp disk_error

main: ; Daniel
    cli
    xor ax, ax          ; this was the minor issue preventing from booting on a real hardwaresssss
    mov ds, ax          ; make DS=0 so we can access BOOT_DRIVE
    mov es, ax          ; set ES for disk_load target
    mov ss, ax
    mov sp, 0x9000

    mov [BOOT_DRIVE], dl
    sti

    mov ax, 0x13
    int 0x10 ; prestige 320x200x256 text mode

    mov bp, 0x9000          ; Set up the stack. This gives us 5 kB above the loaded boot sector
    mov sp, bp              ; at 0x7c00 (there are 638 kB of free memory there).

    mov bx, KERNEL_OFFSET
    mov dh, 50               ; i think 50 is enough sectors for our kernel
    mov dl, [BOOT_DRIVE]
    call disk_load

    cli
    lgdt [GDT_PTR]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp CODE_SEG:pm_main

BOOT_DRIVE db 0x0
KERNEL_OFFSET equ 0x1000

bits 32

pm_main: ; The COOLER Daniel
    mov ax, DATA_SEG

    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    jmp CODE_SEG:0x1000 ; this jmp expects instructions AT THAT EXACT point

    hlt

.halt:
    hlt
    jmp .halt

times 510-($-$$) db 0
dw 0xAA55