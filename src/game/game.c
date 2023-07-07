#include "raylib.h"
#include "../states/gameStates.h"
#include "camera.h"
#include "snake.h"
#include "sounds.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint8_t GameState = STATE_MENU;
static void update();
static void draw();


void InitGame()
{
    printf("raylib version: %s\n",RAYLIB_VERSION);
    // printf("app directory: %s\n",GetApplicationDirectory());
    ChangeDirectory(GetApplicationDirectory());
    SetTraceLogLevel(LOG_ERROR);
    if(!DirectoryExists("resources")){
        printf("`resources` directory not found!\n");
        exit(1);
    }
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    LoadSounds();
    InitWindow(750,750,"Snake ...");
    InitCamera();
    SetExitKey(0);
    SetWindowPosition(GetScreenWidth()/2,GetScreenHeight()/2);
}

void DestroyGame() 
{
    printf("quitting \n");
    DestroySnake();
    UnLoadSounds();
    CloseWindow();
    CloseAudioDevice();
}

void RunGame() 
{
    while (!WindowShouldClose() && GameState != STATE_QUITTING)
    {
        update();
        draw();
    }
}

static void update() 
{
    if(IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
        MaximizeWindow();
    if(IsWindowResized()){
        FitCamera();
    }
    
    switch (GameState)
    {
    case STATE_MENU:
        UpdateMenu();
        break;
    case STATE_RUNNING:
        UpdateRunning();
        break;
    case STATE_GAMEOVER:
        UpdateGameover();
        break;
    case STATE_WIN:
        UpdateWin();
        break;
    case STATE_PAUSED:
        UpdatePaused();
        break;
    }
}

static void draw() 
{
    BeginDrawing();
        ClearBackground(BLACK);
        // DrawRectangle(50,50,200,200,WHITE);
        switch (GameState)
        {
        case STATE_MENU:
            DrawMenu();
            break;
        case STATE_RUNNING:
            DrawRunning();
            break;
        case STATE_GAMEOVER:
            DrawGameover();
            break;
        case STATE_WIN:
            DrawWin();
            break;
        case STATE_PAUSED:
            DrawPaused();
            break;
        }
    EndDrawing();
}
