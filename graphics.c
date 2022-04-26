#include "header.h"


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
    clear(); // clear screen
    
    draw_instructions();

    refresh();
}

void draw_state(State* state)
{

}