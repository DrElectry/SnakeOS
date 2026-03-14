AS = nasm
CC = gcc
LD = ld

BOOT = src/boot/boot.s
SOURCES = $(wildcard src/main/*.c)
ASM_SOURCES = $(wildcard src/asm/*.s)

OBJ = $(SOURCES:.c=.o)
ASM_OBJ = $(ASM_SOURCES:.s=.o)
OBJ += $(ASM_OBJ)

BUILD_DIR = build
BOOT_BIN = $(BUILD_DIR)/boot.bin
KERNEL_BIN = $(BUILD_DIR)/kernel.bin
TARGET = floppy.img

QEMU = qemu-system-i386

all: $(BUILD_DIR) $(OBJ)
	$(AS) $(BOOT) -f bin -o $(BOOT_BIN)
	$(LD) -m elf_i386 -T src/main/linker.ld --oformat binary $(OBJ) -o $(KERNEL_BIN)
	rm $(OBJ)
	cat $(BOOT_BIN) $(KERNEL_BIN) > $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	$(QEMU) \
		-audiodev pa,id=snd0 \
		-machine pcspk-audiodev=snd0 \
		-fda $(TARGET)

src/main/%.o: src/main/%.c
	$(CC) -m32 -nostdlib -ffreestanding -fno-pic -fno-stack-protector -fno-builtin -c $< -o $@

src/asm/%.o: src/asm/%.s
	$(AS) -f elf32 $< -o $@

clean:
	rm -f $(TARGET) $(BOOT_BIN) $(KERNEL_BIN) $(OBJ)
