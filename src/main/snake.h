#ifndef SNAKE_H
#define SNAKE_H

#include "stdint.h"

// the core game

#define WIDTH 320
#define HEIGHT 200
#define CELL_SIZE 16
#define COLS (WIDTH / CELL_SIZE)
#define FIELD_OFFSET_Y 16
#define ROWS ((HEIGHT - FIELD_OFFSET_Y) / CELL_SIZE)
#define MAX_SNAKE 500

#define SNAKE_COLOR RGB233(0,7,3)
#define FOOD_COLOR RGB233(3,0,0)
#define FOOD_SHADOW_COLOR RGB233(1,0,0)
#define BG_COLOR RGB233(0,2,1)
#define SNAKE_SHADOW_COLOR RGB233(0,1,0)
#define BG_COLOR RGB233(0,2,1)
#define BG_GRID_COLOR RGB233(0,3,2)
#define FOOD_SPECULAR RGB233(3,6,6)

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

