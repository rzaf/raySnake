#include "text.h"
// #include <stdio.h>

void TextCal(Text* text)
{
    Vector2 size = MeasureTextEx(text->font,text->text,text->fontSize,text->space);
    text->_width = size.x;
    text->_height = size.y;
}

void TextSetPos(Text* text,int x,int y)
{
    text->pos = (Vector2){x,y};
}

void TextSetFontSize(Text* text,float fontSize)
{
    text->fontSize = fontSize;
    TextCal(text);
}

void TextDraw(Text* text)
{
    DrawTextEx(text->font,text->text,text->pos,text->fontSize,text->space,text->color);
}

void TextDrawAt(Text* text, int x, int y)
{
    DrawTextEx(text->font,text->text,(Vector2){x,y},text->fontSize,text->space,text->color);
}

void TextDrawColored(Text* text,Color color)
{
    DrawTextEx(text->font,text->text,text->pos,text->fontSize,text->space,color);
}

void TextDrawColoredAt(Text* text, int x,int y,Color color)
{
    DrawTextEx(text->font,text->text,(Vector2){x,y},text->fontSize,text->space,color);
}

void TextDrawCentered(Text* text)
{
    DrawTextEx(text->font,text->text,(Vector2){text->pos.x-text->_width/2,text->pos.y-text->_height/2},text->fontSize,text->space,text->color);
}

void TextDrawCenteredAt(Text* text, int x,int y)
{
    DrawTextEx(text->font,text->text,(Vector2){x-text->_width/2,y-text->_height/2},text->fontSize,text->space,text->color);
}

void TextDrawCenteredColored(Text* text ,Color color)
{
    DrawTextEx(text->font,text->text,(Vector2){text->pos.x-text->_width/2,text->pos.y-text->_height/2},text->fontSize,text->space,color);
}

void TextDrawCenteredColoredAt(Text* text, int x, int y, Color color)
{
    DrawTextEx(text->font,text->text,(Vector2){x-text->_width/2,y-text->_height/2},text->fontSize,text->space,color);
}

