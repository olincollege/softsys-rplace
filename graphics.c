#include "header.h"

// setup the screen
void init_screen()
{
    initscr();

	init_colors();

    clear();   				// empty screen
	noecho();  				// no text output
	curs_set(1);  			// cursor invisible
	cbreak();  				// no line buffering, pass every key pressed
	keypad(stdscr, true);  	// keypad enabled
}

void init_colors() {
    if (has_colors() == false)
	{
		endwin();
		printf("Your terminal does not support colors\n");
		exit(1);
	}

    // set up color pairs
    start_color();
	init_pair(0, COLOR_RED, COLOR_RED);
	init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(2, COLOR_GREEN, COLOR_GREEN);
	init_pair(3, COLOR_CYAN, COLOR_CYAN);
	init_pair(4, COLOR_BLUE, COLOR_BLUE);
	init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(6, COLOR_WHITE, COLOR_WHITE);
	init_pair(7, COLOR_BLACK, COLOR_BLACK);

	init_pair(10, COLOR_CYAN, COLOR_WHITE);
	init_pair(11, COLOR_WHITE, COLOR_CYAN);
}

void draw_instructions()
{
	mvprintw(0, 1, "Welcome to Terminal r/place simulations");
	mvprintw(1, 1, "CTRL+C: Quit");
}


// good for now, will need to be fixed later to account for color later
void draw_grid(int x_start, int y_start)
{
	for (int row = 0; row < N_ROWS; row ++){
		for (int col = 0; col < N_COLS; col ++){
			mvaddch(y_start + row, x_start + col, ACS_CKBOARD);
		}
	}
}

void draw_palette() {
	attron(COLOR_PAIR(RED));
	mvaddch(2, 1, ACS_CKBOARD);
	attroff(COLOR_PAIR(RED));
	attron(COLOR_PAIR(YELLOW));
	mvaddch(2, 2, ACS_CKBOARD);
	attroff(COLOR_PAIR(YELLOW));
	attron(COLOR_PAIR(GREEN));
	mvaddch(2, 3, ACS_CKBOARD);
	attroff(COLOR_PAIR(GREEN));
	attron(COLOR_PAIR(CYAN));
	mvaddch(2, 4, ACS_CKBOARD);
	attroff(COLOR_PAIR(CYAN));
	attron(COLOR_PAIR(BLUE));
	mvaddch(2, 5, ACS_CKBOARD);
	attroff(COLOR_PAIR(BLUE));
	attron(COLOR_PAIR(MAGENTA));
	mvaddch(2, 6, ACS_CKBOARD);
	attroff(COLOR_PAIR(MAGENTA));
	attron(COLOR_PAIR(WHITE));
	mvaddch(2, 7, ACS_CKBOARD);
	attroff(COLOR_PAIR(WHITE));
	attron(COLOR_PAIR(BLACK));
	mvaddch(2, 8, ACS_CKBOARD);
	attroff(COLOR_PAIR(BLACK));
}


// KEEP AS VOID FUNC!!!!
// NOTHING SHOULD BE CALCULATED IN THIS FILE!!!
// ONLY THING THAT GETS PASSED AROUND ARE THE ESSENTIALS FOR DRAWING
// KEEP THE DRAW ALL FILE AS ONLY FOR DRAWING A BUNCH OF SMALL ITEMS
// IN THE SUB FUNCITONS, ONLY PASS AROUND X_START, Y_START, AND PLAYERSTATE STRUCT
void draw_all() {
	erase();

	int x_start = (COLS - N_COLS) / 2; // adjust start x and y to center board
    int y_start = (LINES - N_ROWS ) / 2;

	draw_grid(x_start, y_start);
	draw_instructions();
	draw_palette();

	refresh();
}