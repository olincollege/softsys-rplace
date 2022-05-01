#include "header.h"
#define TEST_PAIR	1

void init_screen()
{
    initscr();
    if (has_colors() == false)
	{
		endwin();
		printf("Your terminal does not support colors\n");
		exit(1);
	}

    // setup color pairs
    start_color();


    clear();   // empty screen
	noecho();  // no text output
	curs_set(0);  // cursor invisible
	cbreak();  // no line buffering, pass every key pressed
	keypad(stdscr, true);  // keypad enabled
}

void draw_instructions()
{
	mvprintw(0, 1, "Welcome to Terminal r/place simulations");
	mvprintw(1, 1, "CTRL+C: Quit");
}

void draw_all()
{
    erase(); // clear screen
    
    draw_instructions();

	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(TEST_PAIR));
	mvaddch(2, 1, ACS_CKBOARD);
	mvaddch(2, 3, ACS_BLOCK);
	mvaddch(2, 5, ACS_BOARD);
	mvaddch(2, 7, ACS_DIAMOND);
	attroff(COLOR_PAIR(TEST_PAIR));

    refresh();
}

void draw_state(State* state)
{

}