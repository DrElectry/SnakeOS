#ifndef SNAKE_H
#define SNAKE_H

#include "stdint.h"

// the core game

#define WIDTH 320
#define HEIGHT 200
#define CELL_SIZE 16
#define COLS (WIDTH / CELL_SIZE)
#define ROWS (HEIGHT / CELL_SIZE)
#define MAX_SNAKE 500

typedef struct {
    int x,y;
} Point;

typedef struct {
    Point body[MAX_SNAKE];
    int length;
    char dir; // 'W', 'A', 'S', 'D'
} Snake;

typedef struct {
    Snake snake;
    Point food;
    int alive;
    char pending_dir;
} Game;

void snake_place_food(Game* game);
void snake_init(Game *game);
void snake_update(Game *game);
void snake_set_direction(Game *game, char dir);
void snake_queue_direction(Game *game, uint32_t scancode);

void snake_draw(Game *game);
void snake_handle_input(Game *game, uint32_t scancode);

#endif

