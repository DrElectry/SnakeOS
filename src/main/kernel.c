#include "vga.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "stdint.h"
#include "gfx.h"
#include "keyboard.h"
#include "snake.h"
#include "functions.h"

void int_to_str(int n, char* s) {
    int i = 0;
    if (n == 0) {
        s[0] = '0'; s[1] = 0; return;
    }
    while (n > 0) {
        s[i++] = '0' + n % 10; n /= 10;
    }
    s[i] = 0;
    int j = 0, k = i - 1;
    while (j < k) {
        char t = s[j]; s[j] = s[k]; s[k] = t; j++; k--;
    }
}

Game game;
static uint32_t last_update = 0;

void kernel_main(void) {
    idt_init();
    pic_remap();
pit_init(360);
    pic_unmask_irq(0);
    pic_unmask_irq(1);

    asm volatile("sti");
    
    vga_init();
    vga_generate_pallete();

    snake_init(&game);

    while (1) {
        uint32_t scancode = keyboard_pop();
        if (scancode) {
            uint32_t keycode = scancode;
            if (!game.alive && keyboard_get_char(scancode)) {
                snake_init(&game);
            } else {
                snake_handle_input(&game, keycode);
            }
        }

        uint32_t ticks = pit_get_global_ticks();
        if (ticks - last_update >= 15) {
            snake_update(&game);
            last_update = ticks;
        }
        vga_cls(RGB233(0,2,1));
        snake_draw(&game);


        gfx_text(0,0,"SNAKE OS", RGB233(3,7,7), RGB233(0,0,0), 1,1);

        char score_buf[16];
        int_to_str(game.snake.length, score_buf);
        gfx_text(80,0,score_buf, RGB233(3,7,7), RGB233(0,0,0), 1,1);

        if (!game.alive) {
            gfx_text(100,80,"GAME OVER", RGB233(7,0,0), RGB233(0,0,0), 2,2);
            gfx_text(60,110,"Press any key to restart", RGB233(7,7,7), RGB233(0,0,0), 1,1);
        }

        vga_blit();
        asm volatile("hlt");
    }
}
