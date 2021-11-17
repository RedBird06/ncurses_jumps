#include <NJSprite.h>

#include <iostream>
#include <thread>
#include <fstream>
#include <unistd.h>

NJSprite::NJSprite()
{
    //
}
NJSprite::~NJSprite()
{
    if(_sprite != NULL)
    {
        if(_height!=1)for(int i = 0;i<_height;++i) delete [] _sprite[i];
        delete [] _sprite;
    }
    else
    {
        std::cerr << "ERROR D-R NJSprite" << std::endl;
    }
}
NJSprite::NJSprite(const char* name,NJCanvas* canvas)
{
    int length = 0;
    int height = 0;

    std::ifstream fin(name);
    if(!fin.is_open())
        std::cerr << "ERROR C-R NJSprite(name). Cannot open file." << std::endl;
    else
    {
        fin >> _length;
        fin >> _height;

        char** temp = new char* [height];
        for(int i = 0; i < _height; ++i) temp[i] = new char [length];
        for(int i = 0; i < _height; ++i) fin >> temp[i];

        _sprite = temp;
        spr_canvas = canvas;

        fin.close();
    }
}
NJSprite::NJSprite(char* platform,int length,NJCanvas* canvas)
{
    _length = length;
    _height = 1;

    char** temp = new char* [_height];
    for(int i = 0;i<_height;++i) temp[i] = new char [length];
    for(int i = 0;i<_height;++i) temp[i] = platform;

    _sprite = temp;
    spr_canvas = canvas;
}
void NJSprite::draw(int line,int col)
{
    for(int i = 0;i<_height;++i)
        for(int j = 0;j<_length;++j)
        {
            spr_canvas->canvas(line+i,col+j) = _sprite[i][j];
        }
    _current.line = line;
    _current.column = col;
}
void NJSprite::erase()
{
    for(int i = 0;i<_height;++i)
        for(int j = 0;j<_length;++j)
            spr_canvas->canvas(_current.line+i,_current.column+j) = ' ';
}
void NJSprite::spr_show()
{
    for(int i = 0;i<_height;++i)
    std::cout << _sprite[i] << std::endl;
}
