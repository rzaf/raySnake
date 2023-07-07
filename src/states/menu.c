#include "gameStates.h"
#include "raylib.h"
#include "../game/snake.h"
#include "../game/text.h"
#include "../game/camera.h"

#include <inttypes.h>
#include <stdio.h>

extern uint8_t GameState;
extern uint8_t GridsWidthCount;
extern uint8_t GridsHeightCount;
extern int snakeDefaultSpeed;
extern Sound soundSelect1;
extern Sound soundSelect2;
extern float masterVolume;

static uint8_t isInited = false;
static uint8_t isInSetting = false;

enum {
    BUTTON_START = 0,
    BUTTON_SETTING,
    BUTTON_QUIT,
    BUTTONS_COUNT
};
enum {
    SETTING_BUTTON_CHANGE_GRIDX = 0,
    SETTING_BUTTON_CHANGE_GRIDY,
    SETTING_BUTTON_CHANGE_SNAKE_SPEED,
    SETTING_BUTTON_SOUND,
    SETTING_BUTTON_APPLY,
    SETTING_BUTTONS_COUNT
};

static uint8_t currentButton = 0;
static uint8_t currentSettingButton = 0;

static Text start;
static Text setting;
static Text quit;

static Text settingGridX;
static char gridXText[5];
static Text settingGridY;
static char gridYText[5];
static Text settingSnakeSpeed;
static char snakeSpeedText[10];
static Text settingSound;
static Text settingApply;

struct
{
    unsigned int GridsX;
    unsigned int GridsY;
    unsigned int speed;
    bool sound;
}settingValues;


static void init()
{
    start   = (Text){"START",GetFontDefault(),WHITE,75,5}; 
    setting = (Text){"SETTING",GetFontDefault(),WHITE,60,5};
    quit    = (Text){"QUIT",GetFontDefault(),WHITE,60,5};
    settingGridX        = (Text){"Width",GetFontDefault(),WHITE,45,5}; 
    settingGridY        = (Text){"Height",GetFontDefault(),WHITE,45,5}; 
    settingSnakeSpeed   = (Text){"Snake speed",GetFontDefault(),WHITE,45,5};
    settingSound        = (Text){"Sound",GetFontDefault(),WHITE,45,5};
    settingApply        = (Text){"APPLY",GetFontDefault(),WHITE,50,5};

    TextCal(&start);
    TextCal(&setting);
    TextCal(&quit);
    TextCal(&settingGridX);
    TextCal(&settingGridY);
    TextCal(&settingSnakeSpeed);
    TextCal(&settingSound);
    TextCal(&settingApply);
    
    isInited = true;
}

static void updateButtonSizes()
{
    switch (currentButton)
    {
        case BUTTON_START:
            TextSetFontSize(&start,75);
            TextSetFontSize(&setting,60);
            TextSetFontSize(&quit,60);
            break;
        case BUTTON_SETTING:
            TextSetFontSize(&start,60);
            TextSetFontSize(&setting,75);
            TextSetFontSize(&quit,60);
            break;
        case BUTTON_QUIT:
            TextSetFontSize(&start,60);
            TextSetFontSize(&setting,60);
            TextSetFontSize(&quit,75);
            break;
    }
}

void UpdateMenu()
{
    if(!isInited)
        init();
    
    if(!isInSetting)
    {
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
                case BUTTON_START:
                    InitSnake();
                    GameState = STATE_RUNNING;
                break;
                case BUTTON_SETTING:
                    isInSetting = true;
                    if(currentSettingButton==SETTING_BUTTON_APPLY)
                        currentSettingButton = 0;
                    settingValues.GridsX = GridsWidthCount;
                    settingValues.GridsY = GridsHeightCount;
                    settingValues.speed  = snakeDefaultSpeed;
                    settingValues.sound  = masterVolume<0.5f?0:1;
                break;
                case BUTTON_QUIT:
                    GameState = STATE_QUITTING;
                break;
            }
        } 
    }else
    {
        if(IsKeyPressed(KEY_ESCAPE)){
            isInSetting = false;
        }else if(IsKeyPressed(KEY_ENTER)){
            switch (currentSettingButton)
            {
                case SETTING_BUTTON_APPLY:
                    PlaySound(soundSelect2);
                    GridsWidthCount=settingValues.GridsX;
                    GridsHeightCount=settingValues.GridsY;
                    snakeDefaultSpeed=settingValues.speed ;
                    if(settingValues.sound){
                        SetMasterVolume(0.5f);
                        masterVolume = 5.0f;
                    }
                    else{
                        masterVolume = 0.0f;
                        SetMasterVolume(0);
                    }

                    FitCamera();
                    isInSetting = 0;
                break;
            }
        }

        if(IsKeyPressed(KEY_DOWN)){
            PlaySound(soundSelect1);
            currentSettingButton = (currentSettingButton+1) % SETTING_BUTTONS_COUNT;
        }
        else if(IsKeyPressed(KEY_UP)){
            PlaySound(soundSelect1);
            currentSettingButton = (currentSettingButton-1+SETTING_BUTTONS_COUNT) % SETTING_BUTTONS_COUNT;
        }

        uint8_t right = IsKeyPressed(KEY_RIGHT),left = IsKeyPressed(KEY_LEFT);
        if(left || right){
            PlaySound(soundSelect2);
            switch (currentSettingButton)
            {
            case SETTING_BUTTON_CHANGE_GRIDX:
                settingValues.GridsX += 1*(left==1?-1:1);
                if(settingValues.GridsX<6)
                    settingValues.GridsX = 5;
            break;
            case SETTING_BUTTON_CHANGE_GRIDY:
                settingValues.GridsY += 1*(left==1?-1:1);
                if(settingValues.GridsY<6)
                    settingValues.GridsY = 5;
            break;
            case SETTING_BUTTON_CHANGE_SNAKE_SPEED:
                settingValues.speed += 10*(left==1?-1:1);
                if(settingValues.speed<=40)
                    settingValues.speed = 40;
            break;
            case SETTING_BUTTON_SOUND:
                settingValues.sound = !settingValues.sound;
            break;
            }
        }
    }
}

void DrawMenu()
{
    DrawGridLines();
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),(Color){0,0,0,180});

    if(!isInSetting)
    {
        DrawTextEx(
            GetFontDefault(),
            "IN MENU",
            (Vector2){50,50},
            50,
            5,
            GRAY
        );

        TextDrawCenteredColoredAt(&start,GetScreenWidth()/2,GetScreenHeight()/2-100,currentButton==BUTTON_START?RED:WHITE);
        TextDrawCenteredColoredAt(&setting,GetScreenWidth()/2,GetScreenHeight()/2,currentButton==BUTTON_SETTING?RED:WHITE);
        TextDrawCenteredColoredAt(&quit,GetScreenWidth()/2,GetScreenHeight()/2+100,currentButton==BUTTON_QUIT?RED:WHITE);
    }else
    {
        DrawTextEx(
            GetFontDefault(),
            "IN SETTING",
            (Vector2){50,50},
            50,
            5,
            GRAY
        );
        
        TextDrawColoredAt(&settingGridX,GetScreenWidth()/2-200,GetScreenHeight()/2-200,currentSettingButton==SETTING_BUTTON_CHANGE_GRIDX?RED:WHITE);
        sprintf(gridXText,"%d",settingValues.GridsX);
        DrawTextEx(GetFontDefault(),gridXText,(Vector2){GetScreenWidth()/2+200,GetScreenHeight()/2-200+5},40,5,WHITE); 
        
        TextDrawColoredAt(&settingGridY,GetScreenWidth()/2-200,GetScreenHeight()/2-100,currentSettingButton==SETTING_BUTTON_CHANGE_GRIDY?RED:WHITE);
        sprintf(gridYText,"%d",settingValues.GridsY);
        DrawTextEx(GetFontDefault(),gridYText,(Vector2){GetScreenWidth()/2+200,GetScreenHeight()/2-100+5},40,5,WHITE); 
        
        TextDrawColoredAt(&settingSnakeSpeed,GetScreenWidth()/2-200,GetScreenHeight()/2,currentSettingButton==SETTING_BUTTON_CHANGE_SNAKE_SPEED?RED:WHITE);
        sprintf(snakeSpeedText,"%d",settingValues.speed);
        DrawTextEx(GetFontDefault(),snakeSpeedText,(Vector2){GetScreenWidth()/2+200,GetScreenHeight()/2+5},40,5,WHITE); 
        
        TextDrawColoredAt(&settingSound,GetScreenWidth()/2-200,GetScreenHeight()/2+100,currentSettingButton==SETTING_BUTTON_SOUND?RED:WHITE);
        DrawTextEx(GetFontDefault(),settingValues.sound==1?"ON":"OFF",(Vector2){GetScreenWidth()/2+200,GetScreenHeight()/2+100+5},40,5,WHITE);


        TextDrawCenteredColoredAt(&settingApply,GetScreenWidth()/2,GetScreenHeight()-30,currentSettingButton==SETTING_BUTTON_APPLY?RED:WHITE);
    }

}
