#include <NJCanvas.h>
#include <NJGame.h>
#include <NJConfig.h>
#include <NJMovableSprite.h>

#include <thread>
#include <unistd.h>
#include <iostream>

void refr(NJCanvas* screen,NJGame* game)
{
	while(!game->gameover())
	{
		screen->draw();
		game->upd_scorebar();
		usleep(Hz);
	}
}

int main()
{
	initscr();
	curs_set(0);
	noecho();		
	
    mvwprintw(stdscr,LINES/2,COLS/2-30,"HELLO :3 | THE NJGame WILL START IN 5 SEC | ENJOY!");
	refresh();
	sleep(5);

	WINDOW* main_screen = newwin(LINES-4,COLS,0,0);
	WINDOW* sub_screen = newwin(3,COLS,LINES-3,0);
	WINDOW* score_bar = newwin(1,COLS,LINES-4,0);

    NJCanvas screen(LINES-4,COLS);
    NJMovableSprite hero("../data/hero.spr",&screen);
    NJGame NewGame(&screen);

    NewGame.game_init("../data/map_I.mp");
	NewGame.link_scorebar(score_bar);

	hero.link_game(&NewGame);
	hero.link_screen(&screen);
		
	screen.link_window(main_screen);
	hero.draw(23,4);
	
	screen.draw();
	refresh();

	mvwprintw(score_bar,0,COLS/2-7,"YOUR SCORE : %d",NewGame.score);
	wrefresh(score_bar);

	wborder(sub_screen,'|','|','-','-','+','+','+','+');
	mvwprintw(sub_screen,1,COLS/2-45,"^ == DEATH | YOU SHOULD COLLECT * TO GAIN SCORE POINTS | GOOD LUCK! | PRESS 0 TO EXIT");
	wrefresh(sub_screen);
	refresh();

    std::thread thr(refr,&screen,&NewGame);
	thr.detach();

	hero.gravitati_on();

	while(!NewGame.gameover())
	{
		char c = getch();
		switch(c)
		{
			case 'w':
			{
				hero.move_jump();
				screen.draw();
				break;
			}
			case 'd':
			{
				hero.move_right();
				screen.draw();
				break;
			}
			case 'a':
			{
				hero.move_left();
				screen.draw();
				break;
			}
			case '0':
			{
				NewGame.game_end();
				break;
			}
			default: break;
		}
	}

	screen.clear();
	screen.draw();
	wclear(main_screen);
	wclear(sub_screen);
	wrefresh(sub_screen);

    mvwprintw(stdscr,LINES/2,COLS/2-4,"NJGame OVER");
	refresh();
	sleep(3);

	endwin();

    std::cout << "YOUR SCORE : " << NewGame.score << std::endl;
		
	return 0;
}
