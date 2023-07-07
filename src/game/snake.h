#ifndef SNAKE_H
#define SNAKE_H

#include "grid.h"
#include "raylib.h"

typedef enum {
    DIRECTION_RIGHT,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_UP,
} Direction;

struct SnakePart
{
    Grid grid;
    struct SnakePart* next;     // toward tail
    struct SnakePart* before;   // toward head
};

// typedef struct Snake
// {

// };

typedef struct SnakePart SnakePart;


void InitSnake();
void UpdateSnake();
void DrawSnake();
void DestroySnake();

#endif // SNAKE_H