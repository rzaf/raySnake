#include "raylib.h"

#include "stdio.h"
#include <inttypes.h>

Camera2D gridsCamera;

extern uint8_t GridWidth;
extern uint8_t GridHeight;
extern uint8_t GridsWidthCount ;
extern uint8_t GridsHeightCount;

void FitCamera()
{
    float screenRatio = (float)GetScreenHeight()/GetScreenWidth();    
    float gridRatio = (float)(GridsHeightCount*GridHeight)/(GridsWidthCount*GridWidth);
    if(screenRatio < gridRatio)
        gridsCamera.zoom = (float)GetScreenHeight()/(GridsHeightCount*GridHeight);
    else
        gridsCamera.zoom = (float)GetScreenWidth()/(GridsWidthCount*GridWidth);

    float xOffset = (GetScreenWidth()-GridsWidthCount*GridWidth*gridsCamera.zoom)/2;
    float yOffset = (GetScreenHeight()-GridsHeightCount*GridHeight*gridsCamera.zoom)/2;
    gridsCamera.offset.x = xOffset;
    gridsCamera.offset.y = yOffset;
    // printf("camera fitted zoom:%f ofsset:(%.2f,%.2f)\n",gridsCamera.zoom,gridsCamera.offset.x,gridsCamera.offset.y);
}

void InitCamera()
{
    gridsCamera.offset = (Vector2){0,0};
    gridsCamera.target = (Vector2){0,0};
    gridsCamera.rotation = 0.0f;
    gridsCamera.zoom = 1.0f;
    FitCamera();
}