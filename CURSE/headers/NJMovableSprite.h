#pragma once
#include <NJGame.h>
#include <NJStructs.h>

class NJMovableSprite : public NJSprite
{
private:
    NJMovableSprite();
    NJCanvas* _screen;
    NJGame* _game;
public:
    NJMovableSprite(const char* name, NJCanvas* canvas);

    bool is_jump;
    int jump_counter;

    void move_jump();
    void move_up();
    void move_down();
    void move_left();
    void move_right();

    bool collision(char direction);
    void gravitati_on();

    void link_game(NJGame* game);
    void link_screen(NJCanvas* screen);
    void refr_screen();
};

