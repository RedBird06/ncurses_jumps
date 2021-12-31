#include <NJCanvas.h>
#include <NJGame.h>

#include <iostream>
#include <fstream>

NJGame::NJGame()
{
    //
}
NJGame::~NJGame()
{
   //
}
NJGame::NJGame(NJCanvas* field):
    score(0)
{
	game_over = false;
	_FIELD = field;
}
void NJGame::link_scorebar(WINDOW* scorebar){_scorebar = scorebar;}
void NJGame::upd_scorebar()
{
	mvwprintw(_scorebar,0,COLS/2-7,"YOUR SCORE : %d",score);
	wrefresh(_scorebar);
}
void NJGame::game_init(const char* map_name)
{
    std::ifstream fin(map_name);
	if(!fin.is_open())
		std::cerr << "ERROR NJGame::game_init. Cannot open file." << std::endl;
	else
	{
		fin >> pl_count;
		NJSprite* temp = new NJSprite [pl_count];
		for(int i = 0;i<pl_count;++i)
		{
			fin >> temp[i]._length;
			temp[i]._height = 1;
			fin >> temp[i]._current.line;
			fin >> temp[i]._current.column;
			char** str = new char* [1];
			str[0] = new char [temp[i]._length];
			fin >> str[0];
			temp[i]._sprite = str;
			temp[i].spr_canvas = _FIELD;
		}
		_platforms = temp;	
		fin.close();

		for(int i = 0;i<pl_count;++i)
			_platforms[i].draw(_platforms[i]._current.line,_platforms[i]._current.column);
	}
}
bool NJGame::gameover()
{
    return game_over;
}
void NJGame::game_end()
{
    game_over = true;
}
