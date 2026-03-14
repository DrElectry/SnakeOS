### **W.I.P**

# **SNAKE-OS**

## **About**
**SNAKE-OS** is a 32-bit operating system created out of boredom. It is heavily inspired by **TETRIS-OS**.  

![Demo](screenshots/1.png)

**Implemented Features:**
- Custom-made protected mode bootloader
- 320x200x8 graphics mode
- GDT, IDT, and PIC setup
- Timer implementation (`pit.h` / `pit.c`)
- 8x16 font rendering

**Planned Features:**
- Keyboard driver
- Sprites for Snake, Apple, Background, etc.
- Core Snake game
- Audio driver
- Music and menu

---

## **Requirements**
- A modern **GCC** compiler
- **NASM** assembler for compiling the bootloader and kernel

---

## **How to Run**
1. Ensure you have the **requirements** installed.
2. Clone the GitHub repository:
    ```bash
    git clone <repository_url>
    ```
3. Build the project:
    ```bash
    make all
    ```
4. This will generate `floppy.img` which you can:
    - Run in **QEMU** or any other x86 emulator, or
    - Write to a floppy/USB using **DD** on Linux or **Rufus** in DD mode on Windows  
      *(MacOS compatibility not tested)*

---

## **Notes**
- The latest commit has been tested on **real hardware**.
