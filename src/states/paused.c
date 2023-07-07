#include "raylib.h"
#include "gameStates.h"
#include "../game/snake.h"
#include "../game/text.h"
#include <inttypes.h>
#include <stdio.h>

extern uint8_t GameState;
extern int Score;
extern Sound soundSelect1;

static int isInited = false;
static Text paused;
static Text restart;
static Text resume;
static Text menu;
static Text quit;
static char scoreText[15];

enum {
    BUTTON_RESUME = 0,
    BUTTON_RESTART,
    BUTTON_MENU,
    BUTTON_QUIT,
    BUTTONS_COUNT
};
static uint8_t currentButton = BUTTON_RESUME;

static void init()
{
    currentButton = BUTTON_RESUME;
    paused = (Text){"PAUSED",GetFontDefault(),GRAY,50,5};
    restart = (Text){"RESTART",GetFontDefault(),WHITE,60,5};
    resume = (Text){"RESUME",GetFontDefault(),WHITE,60,5};
    menu = (Text){"MENU",GetFontDefault(),WHITE,60,5};
    quit = (Text){"QUIT",GetFontDefault(),WHITE,60,5};
    TextCal(&paused);
    TextCal(&restart);
    TextCal(&resume);
    TextCal(&menu);
    TextCal(&quit);
    TextSetFontSize(&resume,75);
    isInited = true;    
}

static void updateButtonSizes()
{
    switch (currentButton)
    {
        case BUTTON_RESUME:
            TextSetFontSize(&resume,75);
            TextSetFontSize(&restart,60);
            TextSetFontSize(&menu,60);
            TextSetFontSize(&quit,60);
            break;
        case BUTTON_RESTART:
            TextSetFontSize(&resume,60);
            TextSetFontSize(&restart,75);
            TextSetFontSize(&menu,60);
            TextSetFontSize(&quit,60);
            break;
        case BUTTON_MENU:
            TextSetFontSize(&resume,60);
            TextSetFontSize(&restart,60);
            TextSetFontSize(&menu,75);
            TextSetFontSize(&quit,60);
            break;
        case BUTTON_QUIT:
            TextSetFontSize(&resume,60);
            TextSetFontSize(&restart,60);
            TextSetFontSize(&menu,60);
            TextSetFontSize(&quit,75);
            break;
    }
}

void UpdatePaused()
{
    if(!isInited)
        init();
    
    if(IsKeyPressed(KEY_DOWN)){
        currentButton = (currentButton+1) % BUTTONS_COUNT;
        PlaySound(soundSelect1);
        updateButtonSizes();
    }
    else if(IsKeyPressed(KEY_UP)){
        currentButton = (currentButton-1+BUTTONS_COUNT) % BUTTONS_COUNT;
        PlaySound(soundSelect1);
        updateButtonSizes();
    }

    if(IsKeyPressed(KEY_ENTER)){
        switch (currentButton)
        {
            case BUTTON_RESUME:
                GameState = STATE_RUNNING;
                break;
                isInited = false;
            case BUTTON_RESTART:
                InitSnake();
                GameState = STATE_RUNNING;
                isInited = false;
                break;
            case BUTTON_MENU:
                GameState = STATE_MENU;
                isInited = false;
                break;
            case BUTTON_QUIT:
                GameState = STATE_QUITTING;
                break;
        }
    }else if(IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)){
        GameState = STATE_RUNNING;
    }
}

void DrawPaused()
{

    DrawSnake();
    DrawGridLines();
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),(Color){0,0,0,180});
    
    sprintf(scoreText,"SCORE = %d",Score);
    DrawText(scoreText,30,30,35,RED);
    TextDrawCenteredAt(&paused,GetScreenWidth()/2, 50);

    TextDrawCenteredColoredAt(&resume,GetScreenWidth()/2,GetScreenHeight()/2-200,currentButton==BUTTON_RESUME?RED:WHITE);
    TextDrawCenteredColoredAt(&restart,GetScreenWidth()/2,GetScreenHeight()/2-100,currentButton==BUTTON_RESTART?RED:WHITE);
    TextDrawCenteredColoredAt(&menu,GetScreenWidth()/2,GetScreenHeight()/2,currentButton==BUTTON_MENU?RED:WHITE);
    TextDrawCenteredColoredAt(&quit,GetScreenWidth()/2,GetScreenHeight()/2+100,currentButton==BUTTON_QUIT?RED:WHITE);

}
