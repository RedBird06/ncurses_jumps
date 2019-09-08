#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <fstream>
#include "config.h"

typedef struct coord {int line;int column;} coord;
class CANVAS
{
	private:
		unsigned int _lines;
		unsigned int _columns;

		char** _canvas;
		WINDOW* _window;

		CANVAS();
	public:
		char& canvas(int l,int c);
		int columns();
		int lines();

		CANVAS(int l,int c);
		~CANVAS();
		bool link_window(WINDOW* win);
		void draw();
		void cnv_show(); 
		void clear();
};
class SPRITE
{
	protected:
		char** _sprite;
		unsigned int _length;
		unsigned int _height;
		coord _current;

		CANVAS* spr_canvas;

		SPRITE();

		friend class GAME;
	public:
		SPRITE(const char* name, CANVAS* canvas);
		SPRITE(char* platform,int length,CANVAS* canvas);
		~SPRITE();
		void draw(int l,int c);
	  void erase();
		void spr_show();
};
class GAME
{
	private:
		CANVAS* _FIELD;
		SPRITE* _platforms;

		WINDOW* _scorebar;

		int pl_count;
		bool game_over;

		GAME();
	public:
		~GAME();
		GAME(CANVAS* field);
		int score;
		void link_scorebar(WINDOW* scorebar);
		void upd_scorebar();
		void game_init(const char* map_name);
		bool gameover();
		void game_end();
};
class MOVABLE_SPRITE : public SPRITE
{
	private:
		MOVABLE_SPRITE() : SPRITE(){};
		GAME* _game;
		CANVAS* _screen;
	public:
		MOVABLE_SPRITE(const char* name, CANVAS* canvas) : SPRITE(name,canvas),is_jump(false),jump_counter(JUMPS){};

		void gravitati_on();

		bool is_jump;
		int jump_counter;

		void move_jump();
		void move_up();
		void move_down();
		void move_left();
		void move_right();

		bool collision(char direction);

		void link_game(GAME* game);
		void link_screen(CANVAS* screen);

		void refr_screen();
};

