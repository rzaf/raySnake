#include "raylib.h"
#include "gameStates.h"
#include "../game/snake.h"
#include "../game/timer.h"

// #include <time.h>
// #include <stdlib.h> //rand
#include <stdio.h>

extern uint8_t GameState;
extern uint8_t GridWidth;
extern uint8_t GridHeight;
extern uint8_t GridsWidthCount;
extern uint8_t GridsHeightCount;

static int isInited = false;

static void init()
{
    isInited = true;
}

void UpdateRunning()
{
    if(!isInited)
        init();
        
    UpdateSnake();
    
    if(IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P)){
        GameState = STATE_PAUSED;
    }
}

void DrawRunning()
{
    if(GameState != STATE_RUNNING)
        return;

    DrawSnake();
    DrawGridLines();

    //DrawGrid for snake parts e.x Grid{4,5}
    // DrawRectangle(4*GridWidth,5*GridHeight,GridWidth,GridHeight,BLUE);
    // DrawSnakePart(2,3,BLUE);
}


