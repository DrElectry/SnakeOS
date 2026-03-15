#include "vga.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "stdint.h"
#include "gfx.h"
#include "keyboard.h"
#include "snake.h"
#include "functions.h"
#include "speaker.h"

void panic(char* msg) {
    vga_cls(RGB233(3,0,0));

    gfx_text(0,0,"Kernel panic.", RGB233(3,7,7), RGB233(2,5,5), 1,1);
    gfx_text(0,16,msg, RGB233(3,7,7), RGB233(2,5,5), 1,1);

    vga_blit();
    while (1) {}
}

Game game;
static int show_menu = 1;
static uint32_t last_update = 0;
static int was_alive = 1;

void kernel_main(void) {
    idt_init();
    pic_remap();
    pit_init(180);
    pic_unmask_irq(0);
    pic_unmask_irq(1);

    asm volatile("sti");
    
    vga_init();
    vga_generate_pallete();

    beep(330, 10);

    while (1) {
        uint32_t scancode = keyboard_pop();
        uint32_t ticks = pit_get_global_ticks();
        uint32_t game_over_color = ((pit_get_global_ticks() / 40) % 2 == 0) ? RGB233(7,0,0) : RGB233(7,7,0);
        if (show_menu) {
            vga_cls(RGB233(0,2,1));
            for (int x = 0; x < COLS; x++) {
                for (int y = 0; y < ROWS+2; y++) {
                    int color = ((x + y) % 2 == 0) ? BG_COLOR : BG_GRID_COLOR;
                    gfx_square(x * CELL_SIZE, (y * CELL_SIZE), CELL_SIZE, CELL_SIZE, color);
                }
            }

            // Make the "SNAKE OS" text move up and down 3 pixels
            int offset = (ticks/30 % 6);     // 0,1,2,3,4,5
            if (offset > 3) offset = 6 - offset;  // creates 0,1,2,3,2,1 pattern
            int y_pos = 50 + offset;

            if (ticks % 90 == 45) {
                beep(330, 10);
            }
            if (ticks % 90 == 1) {
                beep(440, 10);
            }

            gfx_text(128, y_pos, "SNAKE OS", game_over_color, RGB233(0,0,0), 1, 1);
            gfx_text(78, 100, "Press ENTER to begin", RGB233(3,7,7), RGB233(0,0,0), 1, 1);
            vga_blit();

            if (scancode && keyboard_get_char(scancode) == '\n') {
                show_menu = 0;
                snake_init(&game);
                beep(330, 10);
            }
            asm volatile("hlt");
            continue;
        }
        if (scancode) {
            uint32_t keycode = scancode;
            if (!game.alive && keyboard_get_char(scancode)) {
                snake_init(&game);
            } else {
                snake_handle_input(&game, keycode);
            }
            if (keycode == 0x01) {
                show_menu = 1;
            }
        }

        if (ticks - last_update >= 15) {
            snake_update(&game);
            if (game.alive == 0 && was_alive == 1) {
                beep(400, 30);
            }
            was_alive = game.alive;
            last_update = ticks;
        }
        vga_cls(RGB233(0,2,1));

        snake_draw(&game);

        gfx_text(0,4,"Score:", RGB233(3,7,7), RGB233(0,0,0), 1,1);

        char score_buf[16];
        int_to_str(game.snake.length, score_buf);
        gfx_text(60,4,score_buf, RGB233(3,7,7), RGB233(0,0,0), 1,1);


        if (!game.alive) {
            gfx_text(120,80,"GAME OVER", game_over_color, RGB233(0,0,0), 2,2);
            gfx_text(60,110,"Press any key to restart", RGB233(7,7,7), RGB233(0,0,0), 1,1);
        }


        vga_blit();
        asm volatile("hlt");
    }
}
