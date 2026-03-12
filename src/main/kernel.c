void print(const char* str) {
    volatile char* video_memory = (char*)0xb8000;
    int i = 0;

    for(int j = 0; j < 80 * 25 * 2; j += 2) {
        video_memory[j] = ' ';
        video_memory[j + 1] = 0x07;
    }

    while(str[i] != '\0') {
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x07;
        i++;
    }
}

void kernel_main(void) {
    print("hi");
    while(1) asm("hlt");
}