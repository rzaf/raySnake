#include "raylib.h"
#include "snake.h"
#include "timer.h"
#include "camera.h"
#include "../states/gameStates.h"
#include <time.h>
#include <stdlib.h> // rand
#include <stdio.h>


extern uint8_t GameState;
extern uint8_t GridWidth;
extern uint8_t GridHeight;
extern uint8_t GridsWidthCount;
extern uint8_t GridsHeightCount;
extern Sound soundPowerup1;
extern Sound soundHit1;

int Score;
int snakeDefaultSpeed = 300;

static Grid fruit;
static Texture2D fruitTexture;
static SnakePart* snakeHead = NULL;
static SnakePart* snakeLastPart;
static Direction snakeDirection;
static Direction snakeLastDirection;
static Timer snakeTimer = {0,0,0};
static uint16_t snakeSpeed; // millisecond per part   
static void checkSnakeCollision();
static void InitFruit();
static void drawSnakeHead();
static void DrawSnakePart(SnakePart* s,Color color);
static void DrawFruit();
static void ExtendSnake();
static void MoveSnake();
static void SnakePartDestroy(SnakePart* s);
static SnakePart* SnakePartInit();
static void DestroySnakeTail();

static Color snakeColor = (Color){ 10, 80, 240, 255 };


void InitSnake() // with 2 parts
{
    Score = 1;
    if(fruitTexture.id==0)
        fruitTexture = LoadTexture("resources/apple.png");
    
    snakeSpeed = snakeDefaultSpeed;
    srand(time(NULL));
    snakeDirection = rand()%4;
    if(snakeHead == NULL){
        printf("Snake head created !\n");
        snakeHead = SnakePartInit();
    }
    snakeHead->grid.x = rand()%(GridsWidthCount-4) + 3;
    snakeHead->grid.y = rand()%(GridsHeightCount-4) + 3;
    DestroySnakeTail();
    snakeLastPart = snakeHead;
    ExtendSnake();
    InitFruit();
}

void UpdateSnake()
{
    if(IsKeyPressed(KEY_UP))
    {
        if(snakeLastDirection != DIRECTION_DOWN)
            snakeDirection = DIRECTION_UP;
    }
    else if(IsKeyPressed(KEY_DOWN))
    {
        if(snakeLastDirection != DIRECTION_UP)
            snakeDirection = DIRECTION_DOWN;
    }
    
    if(IsKeyPressed(KEY_RIGHT))
    {
        if(snakeLastDirection != DIRECTION_LEFT)
            snakeDirection = DIRECTION_RIGHT;
    }
    else if(IsKeyPressed(KEY_LEFT))
    {
        if(snakeLastDirection != DIRECTION_RIGHT)
            snakeDirection = DIRECTION_LEFT;
    }

    if(TimerGet(&snakeTimer)>=snakeSpeed){
        snakeLastDirection = snakeDirection;
        MoveSnake();
        checkSnakeCollision();
        TimerStart(&snakeTimer);
    }
}

void DrawSnake()
{
    BeginMode2D(gridsCamera);
        SnakePart* part = snakeHead;
        Color color = snakeColor;
        while (part->next)
        {
            part = part->next;
            DrawSnakePart(part,color);
            if(color.g<120)
                color.g += 3;
            else
                if(color.a>180)
                    color.a -= 1;
        }
        if(GameState==STATE_RUNNING)
            DrawFruit();
        drawSnakeHead();
    EndMode2D();
}

void DestroySnake()
{
    if(snakeHead){
        DestroySnakeTail();
        SnakePartDestroy(snakeHead);
    }
    snakeHead = NULL;
    UnloadTexture(fruitTexture);
}

static void drawSnakeHead()
{
    DrawSnakePart(snakeHead,snakeColor);
    // DrawSnakePart(snakeHead,DARKBLUE);
    if(GameState==STATE_GAMEOVER)
        DrawSnakePart(snakeHead,(Color){ 200, 40, 55, 255 } );
    switch (snakeDirection)
    {
    case DIRECTION_UP: {
        int x1 = snakeHead->grid.x * GridWidth + GridWidth/3;
        int x2 = snakeHead->grid.x * GridWidth + GridWidth*2/3;
        int y1 = snakeHead->grid.y * GridHeight + GridHeight/4;
        int y2 = snakeHead->grid.y * GridHeight + GridHeight/4;
        DrawCircle(x1,y1,GridWidth/12,WHITE);
        DrawCircle(x2,y2,GridWidth/12,WHITE);
        }
    break;
    case DIRECTION_DOWN:{
        int x1 = snakeHead->grid.x * GridWidth + GridWidth/3;
        int x2 = snakeHead->grid.x * GridWidth + GridWidth*2/3;
        int y1 = snakeHead->grid.y * GridHeight + GridHeight*3/4;
        int y2 = snakeHead->grid.y * GridHeight + GridHeight*3/4;
        DrawCircle(x1,y1,GridWidth/12,WHITE);
        DrawCircle(x2,y2,GridWidth/12,WHITE);
        }
    break;
    case DIRECTION_RIGHT:{
        int x1 = snakeHead->grid.x * GridWidth + GridWidth*3/4;
        int x2 = snakeHead->grid.x * GridWidth + GridWidth*3/4;
        int y1 = snakeHead->grid.y * GridHeight + GridHeight/3;
        int y2 = snakeHead->grid.y * GridHeight + GridHeight*2/3;
        DrawCircle(x1,y1,GridWidth/12,WHITE);
        DrawCircle(x2,y2,GridWidth/12,WHITE);
        }
    break;
    case DIRECTION_LEFT:{
        int x1 = snakeHead->grid.x * GridWidth + GridWidth/4;
        int x2 = snakeHead->grid.x * GridWidth + GridWidth/4;
        int y1 = snakeHead->grid.y * GridHeight +GridHeight/3;
        int y2 = snakeHead->grid.y * GridHeight +GridHeight*2/3;
        DrawCircle(x1,y1,GridWidth/12,WHITE);
        DrawCircle(x2,y2,GridWidth/12,WHITE);
        }
    break;
    }
}

static void checkSnakeCollision()
{
    if(Score > GridsWidthCount*GridsHeightCount-3){
        printf("WON !!!!!! \n");
        GameState = STATE_WIN;
    }
    if(snakeHead->grid.x == fruit.x && snakeHead->grid.y == fruit.y){
        ExtendSnake();
        PlaySound(soundPowerup1);
        InitFruit();
        Score +=1;
        snakeSpeed -= 2;
    }
    SnakePart* part = snakeHead;
    while (part->next)
    {
        part = part->next;
        if(snakeHead->grid.x==part->grid.x && snakeHead->grid.y==part->grid.y){
            printf("Game over !!! \n");
            GameState = STATE_GAMEOVER;
            PlaySound(soundHit1);
        }
    }
     
}

static void DrawSnakePart(SnakePart* s,Color color)
{
    DrawRectangle(
        s->grid.x*GridWidth+0,
        s->grid.y*GridHeight+0,
        GridWidth,
        GridHeight,
        color
    );
    // DrawRectangle(x*GridWidth,y*GridHeight,GridWidth-1,GridHeight-1,color);
}

SnakePart* SnakePartInit()
{
    SnakePart* s = malloc(sizeof(SnakePart));
    // SnakePart* s = MemAlloc(sizeof(SnakePart));
    s->next = NULL;
    s->before = NULL;
    return s;
}

static void SnakePartDestroy(SnakePart* s)
{
    // if(s==snakeHead)
    //     printf("freeing %p (HEAD)\n",s);
    // else
    //     printf("freeing %p\n",s);
    free(s);
}

static void DestroySnakeTail()
{
    SnakePart* part1 = snakeHead->next;
    SnakePart* part2;
    // printf("%d \n",part1->next);
    while (part1 != NULL)
    {
        // printf("Deleted one part! \n");
        part2 = part1->next; 
        SnakePartDestroy(part1);
        part1 = part2;
    }

}

static void InitFruit()
{
    fruit.x = GetRandomValue(0,GridsWidthCount-1);
    fruit.y = GetRandomValue(0,GridsHeightCount-1);
    // printf("Fruit: %d,%d\n",fruit.x,fruit.y);
    
    // SnakePart* part = snakeHead;
    // while (part->next)
    // {
    //     part = part->next;
    //     if(part->grid.x == fruit.x && part->grid.y == fruit.y){
    //         fruit.x = snakeLastPart->grid.x;
    //         fruit.y = snakeLastPart->grid.y;
    //         return;
    //     }
    // }
}

static void DrawFruit()
{
    DrawTexturePro(
        fruitTexture,
        (Rectangle){0,0,88,100},
        (Rectangle){
            fruit.x*GridWidth,
            fruit.y*GridHeight,
            GridWidth,
            GridHeight
        },
        (Vector2){0,0},
        0,
        WHITE
    );
    // DrawTextureEx(fruitTexture,(Vector2){fruit.x*GridWidth,fruit.y*GridHeight},0,???,WHITE);
        
    // DrawCircle(fruit.x*GridWidth+GridWidth/2,fruit.y*GridHeight+GridHeight/2,GridWidth/2-5,RED);
    // DrawRectangle(fruit.x*GridWidth,fruit.y*GridHeight,GridWidth-1,GridHeight-1,RED);
}

static void ExtendSnake() // add one part to end of snake
{
    SnakePart* newEnd = SnakePartInit();
    if(Score>5){
        newEnd->grid.x = snakeLastPart->grid.x;
        newEnd->grid.y = snakeLastPart->grid.y;
    }
    else
        switch (snakeDirection)
        {
            case DIRECTION_DOWN:
                newEnd->grid.x = snakeLastPart->grid.x;
                newEnd->grid.y = snakeLastPart->grid.y-1;
            break;
            case DIRECTION_UP:
                newEnd->grid.x = snakeLastPart->grid.x;
                newEnd->grid.y = snakeLastPart->grid.y+1;
            break;
            case DIRECTION_RIGHT:
                newEnd->grid.x = snakeLastPart->grid.x-1;
                newEnd->grid.y = snakeLastPart->grid.y;
            break;
            case DIRECTION_LEFT:
                newEnd->grid.x = snakeLastPart->grid.x+1;
                newEnd->grid.y = snakeLastPart->grid.y;
            break;
        }
    newEnd->before = snakeLastPart;
    snakeLastPart->next = newEnd;
    snakeLastPart = newEnd;
}

static void MoveSnake()  // add a new head and remove last part
{
    if(GameState != STATE_RUNNING)
        return;
    SnakePart* newHead = SnakePartInit();
    switch (snakeDirection)
    {
        case DIRECTION_DOWN:
            newHead->grid.x = snakeHead->grid.x;
            newHead->grid.y = snakeHead->grid.y+1;
        break;
        case DIRECTION_UP:
            newHead->grid.x = snakeHead->grid.x;
            newHead->grid.y = snakeHead->grid.y-1;
        break;
        case DIRECTION_RIGHT:
            newHead->grid.x = snakeHead->grid.x+1;
            newHead->grid.y = snakeHead->grid.y;
        break;
        case DIRECTION_LEFT:
            newHead->grid.x = snakeHead->grid.x-1;
            newHead->grid.y = snakeHead->grid.y;
        break;
    }
    
    newHead->grid.x = (newHead->grid.x+GridsWidthCount)%GridsWidthCount;
    newHead->grid.y = (newHead->grid.y+GridsHeightCount)%GridsHeightCount;

    snakeHead->before = newHead;
    newHead->next = snakeHead;
    snakeHead = newHead;

    SnakePart* oldLastPartAddr = snakeLastPart;
    snakeLastPart->before->next = NULL;
    snakeLastPart = snakeLastPart->before;
    SnakePartDestroy(oldLastPartAddr);
}
