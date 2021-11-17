#include <NJMovableSprite.h>
#include <NJConfig.h>

#include <iostream>
#include <thread>
#include <fstream>
#include <unistd.h>

void jump(NJMovableSprite* hero);
void gravitation(NJMovableSprite* hero);

NJMovableSprite::NJMovableSprite():
    NJSprite()
{
    //
}
NJMovableSprite::NJMovableSprite(const char* name, NJCanvas* canvas):
    NJSprite(name,canvas),
    is_jump(false),
    jump_counter(MAX_JUMPS)
{
    //
}
void NJMovableSprite::link_game(NJGame* game)
{
    _game = game;
}
void NJMovableSprite::move_jump()
{
    is_jump = true;
}
void NJMovableSprite::gravitati_on()
{
    std::thread grv(gravitation,this);
    grv.detach();
}
void NJMovableSprite::move_up()
{
    if(!collision('w'))
    {
        erase();
        draw(_current.line-1,_current.column);
        draw_on_screen(_current.line - 1, _current.line + _height + 1);
    }
}
void NJMovableSprite::move_down()
{
    if(!collision('s'))
    {
        erase();
        draw(_current.line+1,_current.column);
        draw_on_screen(_current.line - 1, _current.line + _height + 1);
    }
}
void NJMovableSprite::move_right()
{
    if(!collision('d'))
    {
        erase();
        draw(_current.line, _current.column+1);
        draw_on_screen(_current.line - 1, _current.line + _height + 1);
    }
}
void NJMovableSprite::move_left()
{
    if(!collision('a'))
    {
        erase();
        draw(_current.line, _current.column-1);
        draw_on_screen(_current.line - 1, _current.line + _height + 1);
    }
}
bool NJMovableSprite::collision(char direction)
{
    //cout << "NJMovableSprite::collision" << endl;

    switch(direction)
    {
        case 'w':
        {
            if(_current.line == 0) return true;
            for(int i = 0;i<_length;++i)
            {
                if(spr_canvas->canvas(_current.line-1,_current.column+i) == '*'){_game->score++; return false;}
                if(spr_canvas->canvas(_current.line-1,_current.column+i) != ' ') return true;
            }
            return false;
        }
        case 's':
        {
            for(int i = 0;i<_length;++i)
            {
                if(spr_canvas->canvas(_current.line+_height,_current.column+i) == '*'){_game->score++;return false;}
                if(spr_canvas->canvas(_current.line+_height,_current.column+i) == '^'){_game->game_end();return true;}
                if(spr_canvas->canvas(_current.line+_height,_current.column+i) == '|'){jump_counter = MAX_JUMPS; return true;}
            }
            return false;
        }
        case 'g':
        {
            if(_current.line+_height == spr_canvas->lines()-1){_game->game_end();return true;}
            return false;
        }
        case 'd':
        {
            if(_current.column+_length == spr_canvas->columns()) return true;
            for(int i = 0;i<_height;++i)
            {
                if(spr_canvas->canvas(_current.line+i,_current.column+_length) == '*'){_game->score++; return false;}
                if(spr_canvas->canvas(_current.line+i,_current.column+_length) != ' ') return true;
            }
            return false;
        }
        case 'a':
        {
            if(_current.column == 0) return true;
            for(int i = 0;i<_height;++i)
            {
                if(spr_canvas->canvas(_current.line+i,_current.column-1) == '*'){_game->score++; return false;}
                if(spr_canvas->canvas(_current.line+i,_current.column-1) != ' ') return true;
            }
            return false;
        }
        default: return false;

    }
}

void NJMovableSprite::draw_on_screen(int line_from, int line_to)
{
    if(!_game->gameover())
    {
        spr_canvas->draw(line_from, line_to);
        _game->upd_scorebar();
    }
}

void jump(NJMovableSprite* hero)
{
    for(int i = 0;i<4;++i)
    {
        hero->move_up();
        usleep(JUMP_SPEED);
    }
}
void gravitation(NJMovableSprite* hero)
{
    while(!hero->collision('g'))
    {
        if(hero->is_jump && hero->jump_counter > 0)
        {
            hero->jump_counter--;
            std::thread hero_jump(jump,hero);
            hero_jump.join();
            hero->is_jump = false;
        }
        hero->move_down();
        usleep(GRAVITATION);
    }
}
