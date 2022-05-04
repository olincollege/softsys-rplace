#include "header.h"

void init_all() {
	init_screen();
	init_colors();
	init_mouse();
}

// setup the screen
void init_screen()
{
    initscr();

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
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(4, COLOR_GREEN, COLOR_GREEN);
	init_pair(5, COLOR_CYAN, COLOR_CYAN);
	init_pair(6, COLOR_BLUE, COLOR_BLUE);
	init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(8, COLOR_WHITE, COLOR_WHITE);
	init_pair(9, COLOR_BLACK, COLOR_BLACK);

	init_pair(10, COLOR_CYAN, COLOR_WHITE);
	init_pair(11, COLOR_WHITE, COLOR_CYAN);
}

void init_mouse() {
	// Enables keypad mode. This makes (at least for me) mouse events getting
	// reported as KEY_MOUSE, instead as of random letters.
	keypad(stdscr, TRUE);

	// Don't mask any mouse events
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

	printf("\033[?1003h\n"); // Makes the terminal report mouse movement events
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


void rectangle(int x_start, int y_start, int width, int height, int color)
{
	attron(COLOR_PAIR(RED));
    for (int row = y_start; row < y_start + height; row ++){
		for (int col = x_start; col < x_start + width; col ++){
			mvaddch(row, col, ACS_CKBOARD);
		}
	}
	attroff(COLOR_PAIR(RED));
}


void draw_palette(int x_start, int y_start) {

	int pallette_width = N_COLS/8;

	for (int i = 2; i < 9; i ++){
		int x = x_start + i * pallette_width;
		rectangle(x, y_start + N_ROWS + 1, pallette_width, 5, RED);

	}


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
	draw_palette(x_start, y_start);

	refresh();
}