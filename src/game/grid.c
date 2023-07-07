#include "raylib.h"
#include "camera.h"

#include <inttypes.h>

// unsigned int GridWidth  = 88;
// unsigned int GridHeight = 100;
// unsigned int GridsWidthCount  = 8;
// unsigned int GridsHeightCount = 8;

uint8_t GridWidth  = 88;
uint8_t GridHeight = 100;
uint8_t GridsWidthCount  = 8;
uint8_t GridsHeightCount = 8;


void DrawGridLines()
{
    BeginMode2D(gridsCamera);
        for (int i=1 ; i<GridsWidthCount ; ++i) 
        {
            int xOffset = i*GridWidth; 
            DrawLine(xOffset,0,xOffset,GridHeight*GridsHeightCount,WHITE);
        }
        for (int j=1 ; j<GridsHeightCount ; ++j) 
        {
            int yOffset = j*GridHeight;
            DrawLine(0,yOffset,GridWidth*GridsWidthCount,yOffset,WHITE);
        }
    EndMode2D();
}

