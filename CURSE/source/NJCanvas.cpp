#include <NJCanvas.h>
#include <iostream>

NJCanvas::NJCanvas(){}
NJCanvas::~NJCanvas()
{
	if(_canvas != NULL)
	{
		for(int i = 0;i<_lines;++i) delete [] _canvas[i];
		delete [] _canvas;
	}
	else
	{
        std::cerr << "ERROR D-R NJCanvas" << std::endl;
	}
}
NJCanvas::NJCanvas(int lines, int columns)
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

	_canvas = temp;
}
bool NJCanvas::link_window(WINDOW* win)
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
void NJCanvas::draw()
{
  for(int i = 0;i<_lines;++i) mvwprintw(_window,i,0,"%s",_canvas[i]);
	wrefresh(_window);	
}
void NJCanvas::cnv_show()
{
	for(int i = 0;i<_lines;++i)
        std::cout << _canvas[i] << std::endl;
}
int NJCanvas::columns()
{
	return _columns;
}
int NJCanvas::lines()
{
	return _lines;
}
char& NJCanvas::canvas(int line,int column)
{
	return _canvas[line][column];
}
void NJCanvas::clear()
{
	for(int i = 0;i<_lines;++i)
		for(int j = 0;j<_columns;++j)
			_canvas[i][j] = ' ';
}
