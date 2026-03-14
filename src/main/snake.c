#include "snake.h"
#include "gfx.h"
#include "pit.h"
#include "vga.h"

#define SNAKE_COLOR RGB233(0,7,3)
#define FOOD_COLOR RGB233(7,2,0)
#define BG_COLOR RGB233(0,2,1)

static int dx[256] = {0};
static int dy[256] = {0};

uint32_t rand_seed = 0;

uint32_t rand() {
    rand_seed = rand_seed * 1103515245 + 12345;
    return rand_seed;
}

void snake_place_food(Game* game) {
    while (1) {
        uint32_t r = rand() % (COLS * ROWS);
        game->food.x = r % COLS;
        game->food.y = r / COLS;
        int overlap = 0;
        int i;
        for (i = 0; i < game->snake.length; i++) {
            if (game->food.x == game->snake.body[i].x && game->food.y == game->snake.body[i].y) {
                overlap = 1;
                break;
            }
        }
        if (!overlap) break;
    }
}

void snake_init(Game *game) {
    int i;
    game->snake.length = 3;
    game->snake.body[0].x = COLS / 2 - 1;
    game->snake.body[0].y = ROWS / 2;
    game->snake.body[1].x = COLS / 2 - 2;
    game->snake.body[1].y = ROWS / 2;
    game->snake.body[2].x = COLS / 2 - 3;
    game->snake.body[2].y = ROWS / 2;
    game->snake.dir = 'D';
    game->alive = 1;
    rand_seed = pit_get_global_ticks();
    dx['w'] = dx['W'] = 0; dy['w'] = dy['W'] = -1;
    dx['a'] = dx['A'] = -1; dy['a'] = dy['A'] = 0;
    dx['s'] = dx['S'] = 0; dy['s'] = dy['S'] = 1;
    dx['d'] = dx['D'] = 1; dy['d'] = dy['D'] = 0;
    dx['R'] = 1; dy['R'] = 0;
    snake_place_food(game);
}

void snake_set_direction(Game *game, char dir) {
    if (dir >= 'a' && dir <= 'z') dir -= 32;
    char curr = game->snake.dir;
    if ((dir == 'W' && curr != 'S') ||
        (dir == 'S' && curr != 'W') ||
        (dir == 'A' && curr != 'D') ||
        (dir == 'D' && curr != 'A')) {
        game->snake.dir = dir;
    }
}

void snake_update(Game *game) {
    if (!game->alive) return;
    Point head = game->snake.body[0];
    int d = game->snake.dir;
    Point new_head = {head.x + dx[d], head.y + dy[d]};
    if (new_head.x < 0 || new_head.x >= COLS || new_head.y < 0 || new_head.y >= ROWS) {
        game->alive = 0;
        return;
    }
    int i;
    for (i = 0; i < game->snake.length; i++) {
        if (new_head.x == game->snake.body[i].x && new_head.y == game->snake.body[i].y) {
            game->alive = 0;
            return;
        }
    }
    for (i = game->snake.length - 1; i > 0; i--) {
        game->snake.body[i] = game->snake.body[i - 1];
    }
    game->snake.body[0] = new_head;
    if (new_head.x == game->food.x && new_head.y == game->food.y) {
        game->snake.length++;
        snake_place_food(game);
    }
}

void snake_draw(Game *game) {
    int i;
    for (i = 0; i < game->snake.length; i++) {
        gfx_square(game->snake.body[i].x * CELL_SIZE, game->snake.body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, SNAKE_COLOR);
    }
    gfx_square(game->food.x * CELL_SIZE, game->food.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, FOOD_COLOR);
}


void snake_handle_input(Game *game, uint32_t scancode) {
    uint8_t code = scancode & 0xFF;
    if (code == 0x11) snake_set_direction(game, 'w'); // W up
    else if (code == 0x1E) snake_set_direction(game, 'a'); // A left
    else if (code == 0x1F) snake_set_direction(game, 's'); // S down
    else if (code == 0x20) snake_set_direction(game, 'd'); // D right
}
