#pragma once
#include <ncurses.h>

class NJCanvas
{
private:
	unsigned int _lines;
	unsigned int _columns;

	char** _canvas;
	WINDOW* _window;

	NJCanvas();
public:
	NJCanvas(int l, int c);
	~NJCanvas();

	char& canvas(int l, int c);
	int columns();
	int lines();

	bool link_window(WINDOW* win);
	void draw();
	void cnv_show();
	void clear();
};

