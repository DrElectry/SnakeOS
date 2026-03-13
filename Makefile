# beware - the SNAKEOS makefile build!

AS = nasm
CC = gcc
LD = ld
BOOT = src/boot/boot.s
SOURCES = $(wildcard src/main/*.c)
OBJ = $(SOURCES:.c=.o)
ASM_SOURCES = $(wildcard src/asm/*.s)
ASM_OBJ = $(ASM_SOURCES:.s=.o)
OBJ += $(ASM_OBJ)
BOOT_BIN = boot.bin
KERNEL_BIN = kernel.bin

TARGET = floppy.img

QEMU = qemu-system-i386

all: $(OBJ)
	$(AS) $(BOOT) -f bin -o $(BOOT_BIN)

	$(LD) -m elf_i386 -T src/main/linker.ld --oformat binary $(OBJ) -o $(KERNEL_BIN)
	rm $(OBJ)

	cat $(BOOT_BIN) $(KERNEL_BIN) > $(TARGET)

run: all
	$(QEMU) -fda $(TARGET)

src/main/%.o: src/main/%.c
	$(CC) -m32 -nostdlib -ffreestanding -fno-pic -fno-stack-protector -fno-builtin -c $< -o $@

src/asm/%.o: src/asm/%.s
	$(AS) -f elf32 $< -o $@

clean:
	rm -f $(TARGET) $(BOOT_BIN) $(KERNEL_BIN) $(OBJ) *.o
