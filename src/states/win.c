#include "raylib.h"
#include "gameStates.h"
#include "../game/snake.h"
#include "../game/text.h"

#include <stdio.h>
#include <inttypes.h>

extern uint8_t GameState;
extern int Score;

static int isInited = false;
static Text win;
static Text restart;
static Text menu;
static char scoreText[15];

static void init()
{
    win = (Text){"YOU WON !!!!! ",GetFontDefault(),RED,65,10};
    restart = (Text){"PRESS R TO RESTART",GetFontDefault(),WHITE,50,2};
    menu = (Text){"PRESS ESCAPE TO GO TO MENU",GetFontDefault(),WHITE,50,2};
    TextCal(&win);
    TextCal(&restart);
    TextCal(&menu);
}

void UpdateWin()
{
    if(!isInited)
        init();
    if(IsKeyPressed(KEY_R)){
        InitSnake();
        GameState = STATE_RUNNING;
    }
    if(IsKeyPressed(KEY_ESCAPE)){
        GameState = STATE_MENU;
    }
}

void DrawWin()
{
    DrawGridLines();
    DrawSnake();
    
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),(Color){0,0,0,120});
    

    sprintf(scoreText,"SCORE = %d",Score);
    DrawText(scoreText,30,30,35,RED);

    TextDrawCenteredAt(&win,GetScreenWidth()/2,GetScreenHeight()/2-80);
    TextDrawCenteredAt(&restart,GetScreenWidth()/2,GetScreenHeight()/2+30);
    TextDrawCenteredAt(&menu,GetScreenWidth()/2,GetScreenHeight()/2+100);
}