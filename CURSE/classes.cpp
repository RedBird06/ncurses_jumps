#include "./headers/canvas.h"

using namespace std;

//========================CANVAS==========================

CANVAS::CANVAS(){}
CANVAS::~CANVAS()
{
	if(_canvas != NULL)
	{
		for(int i = 0;i<_lines;++i) delete [] _canvas[i];
		delete [] _canvas;
	}
	else
	{
		cerr << "ERROR D-R CANVAS" << endl;
	}
}
CANVAS::CANVAS(int lines, int columns)
{
	_lines = lines;
	_columns = columns;

	char** temp;
	temp = new char* [lines];
	for(int i = 0;i<lines;++i) temp[i] = new char [columns];

	for(int i = 0;i<lines;++i)
		for(int j = 0;j<columns;++j)
			temp[i][j] = ' ';

	for(int i = 0;i<columns;++i) temp[lines-1][i] = '^';
//	for(int i = 0;i<columns;++i) temp[lines-1][i] = '|';

	_canvas = temp;
}
bool CANVAS::link_window(WINDOW* win)
{
	if(win != NULL)
	{
		_window = win;
		return true;
	}
	else
	{
		return false;
	}
}
void CANVAS::draw()
{
  for(int i = 0;i<_lines;++i) mvwprintw(_window,i,0,"%s",_canvas[i]);
	wrefresh(_window);	
}
void CANVAS::cnv_show()
{
	for(int i = 0;i<_lines;++i)cout << _canvas[i] << endl;
}
int CANVAS::columns()
{
	return _columns;
}
int CANVAS::lines()
{
	return _lines;
}
char& CANVAS::canvas(int line,int column)
{
	return _canvas[line][column];
}
void CANVAS::clear()
{
	for(int i = 0;i<_lines;++i)
		for(int j = 0;j<_columns;++j)
			_canvas[i][j] = ' ';
}
//=======================SPRITE=========================

SPRITE::SPRITE(){}
SPRITE::~SPRITE()
{
	if(_sprite != NULL)
	{
		if(_height!=1)for(int i = 0;i<_height;++i) delete [] _sprite[i];
		delete [] _sprite;
	}
	else
	{
		cerr << "ERROR D-R SPRITE" << endl;
	}
}
SPRITE::SPRITE(const char* name,CANVAS* canvas)
{
	int length,height;

	ifstream fin(name);
	if(!fin.is_open())
		cerr << "ERROR C-R SPRITE(name). Cannot open file." << endl;
	else
	{
		fin >> _length;
		fin >> _height;

		char** temp = new char* [height];
		for(int i = 0;i<_height;++i) temp[i] = new char [length];
		for(int i = 0;i<_height;++i) fin >> temp[i];

		_sprite = temp;
		spr_canvas = canvas;

		fin.close();
	}
}
SPRITE::SPRITE(char* platform,int length,CANVAS* canvas)
{
	_length = length;
	_height = 1;

	char** temp = new char* [_height];
	for(int i = 0;i<_height;++i) temp[i] = new char [length];
	for(int i = 0;i<_height;++i) temp[i] = platform;

	_sprite = temp;
	spr_canvas = canvas;
}
void SPRITE::draw(int line,int col)
{
	//cout << "SPRITE::draw" << endl;
	for(int i = 0;i<_height;++i)
			for(int j = 0;j<_length;++j)
			{	
				spr_canvas->canvas(line+i,col+j) = _sprite[i][j];
			}
	_current.line = line;
	_current.column = col;
	//cout << "DRAW_END" << endl;
			
}
void SPRITE::erase()
{
	//cout << "SPRITE::erase" << endl;

	for(int i = 0;i<_height;++i)
			for(int j = 0;j<_length;++j)
				spr_canvas->canvas(_current.line+i,_current.column+j) = ' ';
}
void SPRITE::spr_show()
{
	for(int i = 0;i<_height;++i)cout << _sprite[i] << endl;
}

//===============MOVABLE_SPRITE=========================
void jump(MOVABLE_SPRITE* hero)
{
	for(int i = 0;i<4;++i)
	{
		hero->move_up();
		usleep(JUMP_SPEED);
	}
}
void gravitation(MOVABLE_SPRITE* hero)
{	
	while(!hero->collision('g'))
	{
		if(hero->is_jump && hero->jump_counter > 0)
		{
			hero->jump_counter--;
			thread hero_jump(jump,hero);
			hero_jump.join();
			hero->is_jump = false;
		}
		hero->move_down();
		usleep(GRAVITATION);
	}
}
void MOVABLE_SPRITE::link_game(GAME* game){_game = game;}
void MOVABLE_SPRITE::link_screen(CANVAS* screen){_screen = screen;}
void MOVABLE_SPRITE::refr_screen(){_screen->draw();}
void MOVABLE_SPRITE::move_jump()
{
	is_jump = true;
}
void MOVABLE_SPRITE::gravitati_on()
{
	thread grv(gravitation,this);
	grv.detach();	
}
void MOVABLE_SPRITE::move_up()
{
	if(!collision('w'))
	{
		erase();
		draw(_current.line-1,_current.column);
	}
}
void MOVABLE_SPRITE::move_down()
{
	if(!collision('s'))
	{
		erase();
		draw(_current.line+1,_current.column);
	}
}
void MOVABLE_SPRITE::move_right()
{
	if(!collision('d'))
	{
		erase();
		draw(_current.line,_current.column+1);
	}
}	
void MOVABLE_SPRITE::move_left()
{
	if(!collision('a'))
	{
		erase();
		draw(_current.line,_current.column-1);
	}
}
bool MOVABLE_SPRITE::collision(char direction)
{
	//cout << "MOVABLE_SPRITE::collision" << endl;

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
				if(spr_canvas->canvas(_current.line+_height,_current.column+i) == '|'){jump_counter = JUMPS; return true;}
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
//========================GAME==========================
GAME::GAME(){}
GAME::~GAME(){}
GAME::GAME(CANVAS* field):score(0)
{
	game_over = false;
	_FIELD = field;
}
void GAME::link_scorebar(WINDOW* scorebar){_scorebar = scorebar;}
void GAME::upd_scorebar()
{
	mvwprintw(_scorebar,0,COLS/2-7,"YOUR SCORE : %d",score);
	wrefresh(_scorebar);
}
void GAME::game_init(const char* map_name)
{
	ifstream fin(map_name);
	if(!fin.is_open())
		cerr << "ERROR GAME::game_init. Cannot open file." << endl;
	else
	{
		int length;
		char* str;
		fin >> pl_count;
		SPRITE* temp = new SPRITE [pl_count];
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
bool GAME::gameover(){return game_over;}
void GAME::game_end(){game_over = true;}
