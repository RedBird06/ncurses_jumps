#pragma once
#include <ncurses.h>
#include <NJCanvas.h>
#include <NJSprite.h>

class NJGame
{
	private:
		NJCanvas* _FIELD;
		NJSprite* _platforms;

		WINDOW* _scorebar;

		int pl_count;
		bool game_over;

		NJGame();
	public:
		~NJGame();
		NJGame(NJCanvas* field);
		int score;
		void link_scorebar(WINDOW* scorebar);
		void upd_scorebar();
		void game_init(const char* map_name);
		bool gameover();
		void game_end();
};

