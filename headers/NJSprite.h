#pragma once
#include <NJStructs.h>
#include <NJCanvas.h>

class NJSprite
{
protected:
    char** _sprite;
    int _length;
    int _height;
    coord _current;
    NJCanvas* spr_canvas;

    NJSprite();

    friend class NJGame;
public:
    NJSprite(const char* name, NJCanvas* canvas);
    NJSprite(char* platform, int length, NJCanvas* canvas);
    ~NJSprite();

    void draw(int l,int c);
    void erase();
    void spr_show();
};


