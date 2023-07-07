#ifndef TEXT_H
#include "raylib.h"

typedef struct
{
    const char* text;
    Font font;
    Color color;
    float fontSize;
    float space;
    Vector2 pos;
    float _width;
    float _height;
} Text;


void TextCal(Text* text);
void TextSetPos(Text* text,int x,int y);
void TextSetFontSize(Text* text,float fontSize);
void TextDraw(Text* text);
void TextDrawAt(Text* text, int x, int y);
void TextDrawColored(Text* texts,Color color);
void TextDrawColoredAt(Text* text, int x,int y,Color color);
void TextDrawCentered(Text* text);
void TextDrawCenteredAt(Text* text, int x,int y);
void TextDrawCenteredColored(Text* text, Color color);
void TextDrawCenteredColoredAt(Text* text, int x, int y, Color color);


#define TEXT_H
#endif//TEXT_H