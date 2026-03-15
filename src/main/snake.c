#include "snake.h"
#include "gfx.h"
#include "pit.h"
#include "vga.h"
#include "speaker.h"

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
    game->pending_dir = 0;
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

    // Apply pending direction
    if (game->pending_dir != 0) {
        beep(330, 10);
        char dir = game->pending_dir;
        if (dir >= 'a' && dir <= 'z') dir -= 32;
        char curr = game->snake.dir;
        if ((dir == 'W' && curr != 'S') ||
            (dir == 'S' && curr != 'W') ||
            (dir == 'A' && curr != 'D') ||
            (dir == 'D' && curr != 'A')) {
            game->snake.dir = dir;
        }
        game->pending_dir = 0;
    }

    Point head = game->snake.body[0];
    int d = game->snake.dir;
    Point new_head = {head.x + dx[d], head.y + dy[d]};
    if (new_head.x < 0 || new_head.x >= COLS || new_head.y < 0 || new_head.y >= ROWS) {
        game->alive = 0;
        return;
    }
    int i;
    for (i = 1; i < game->snake.length; i++) {
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
        beep(200, 10);
    }
}

void snake_draw(Game *game) {
    uint32_t offset_y = 24;
    int i;
    for (int x = 0; x < COLS; x++) {
        for (int y = 0; y < ROWS; y++) {
            int color = ((x + y) % 2 == 0) ? BG_COLOR : BG_GRID_COLOR;
            gfx_square(x * CELL_SIZE, (y * CELL_SIZE) + offset_y, CELL_SIZE, CELL_SIZE, color);
        }
    }
    gfx_line(0,24,320,24,RGB233(0,1,0));
    for (i = 0; i < game->snake.length; i++) {
        gfx_square_rounded(game->snake.body[i].x * CELL_SIZE + 1, game->snake.body[i].y * CELL_SIZE + 1 + offset_y, CELL_SIZE, CELL_SIZE, 4, SNAKE_SHADOW_COLOR);
        gfx_square_rounded(game->snake.body[i].x * CELL_SIZE, game->snake.body[i].y * CELL_SIZE + offset_y, CELL_SIZE, CELL_SIZE, 4, SNAKE_COLOR);
    }
    gfx_square_rounded(game->food.x * CELL_SIZE - 1, game->food.y * CELL_SIZE - 1 + offset_y, CELL_SIZE, CELL_SIZE, 8, FOOD_SPECULAR);
    gfx_square_rounded(game->food.x * CELL_SIZE + 1, game->food.y * CELL_SIZE + 1 + offset_y, CELL_SIZE, CELL_SIZE, 8, FOOD_SHADOW_COLOR);
    gfx_square_rounded(game->food.x * CELL_SIZE, game->food.y * CELL_SIZE + offset_y, CELL_SIZE, CELL_SIZE, 8, FOOD_COLOR);
}

void snake_queue_direction(Game *game, uint32_t scancode) {
    uint8_t code = scancode & 0xFF;
    char dir = 0;
    if (code == 0x11) dir = 'w'; // W up
    else if (code == 0x1E) dir = 'a'; // A left
    else if (code == 0x1F) dir = 's'; // S down
    else if (code == 0x20) dir = 'd'; // D right
    if (dir != 0) {
        if (dir >= 'a' && dir <= 'z') dir -= 32;
        char curr = game->snake.dir;
        if ((dir == 'W' && curr != 'S') ||
            (dir == 'S' && curr != 'W') ||
            (dir == 'A' && curr != 'D') ||
            (dir == 'D' && curr != 'A')) {
            game->pending_dir = dir;
        }
    }
}

void snake_handle_input(Game *game, uint32_t scancode) {
    snake_queue_direction(game, scancode);
}

