#include "header.h"

void init_all() {
	init_screen();

	init_mouse();
}

// setup the screen
void init_screen()
{
    WINDOW * screen = initscr();

    clear();   				// empty screen
	noecho();  				// no text output
	curs_set(0);  			// cursor invisible
	cbreak();  				// no line buffering, pass every key pressed
	keypad(stdscr, true);  	// keypad enabled

	init_colors();
	// wbkgd(screen, COLOR_PAIR(BLACK));

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
	
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_RED);
	init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(4, COLOR_GREEN, COLOR_GREEN);
	init_pair(5, COLOR_CYAN, COLOR_CYAN);
	init_pair(6, COLOR_BLUE, COLOR_BLUE);
	init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);


	init_pair(10, COLOR_CYAN, COLOR_WHITE);
	init_pair(11, COLOR_WHITE, COLOR_CYAN);
	init_pair(12, COLOR_WHITE, COLOR_BLACK);


	
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
	attron(COLOR_PAIR(WHITE));
	for (int row = 0; row < N_ROWS; row ++){
		for (int col = 0; col < N_COLS; col ++){
			mvaddch(y_start + row, x_start + col, ACS_CKBOARD);
		}
	}
	attroff(COLOR_PAIR(WHITE));
}


void rectangle(int x_start, int y_start, int width, int height, int color)
{

	attron(COLOR_PAIR(color));
    for (int row = y_start; row < y_start + height; row ++){
		for (int col = x_start; col < x_start + width; col ++){
			mvaddch(row, col, ACS_CKBOARD);
		}
	}
	attroff(COLOR_PAIR(color));
}


void draw_palette(int x_start, int y_start) {

	int palette_height = 5;
	int palette_width = 16;

	int total_width = palette_width*8;

	int x = (N_COLS - total_width)/2 + x_start;

	for (int i = 0; i < 8; i ++){
		int x1 = x + 1 + palette_width*i;
		int x2 = x + 1 + palette_width*i + palette_width;
		int y1 = y_start + N_ROWS + 1;
		int y2 = y_start + N_ROWS + 1 + palette_height;

		rectangle(x1, y1, palette_width - 4, palette_height, i);
		
		attron(COLOR_PAIR(BORDER));
		// mvhline(y1, x1, 0, palette_width);
		// mvhline(y2, x1, 0, palette_width);
		// mvvline(y1, x1, 0, palette_height);
		// mvvline(y1, x2, 0, palette_height);
		// mvaddch(y_start, x_start, ACS_ULCORNER);
		// mvaddch(y_start + N_ROWS, x_start, ACS_LLCORNER);
		// mvaddch(y_start, x_start + N_COLS, ACS_URCORNER);
		// mvaddch(y_start + N_ROWS, x_start + N_COLS, ACS_LRCORNER);
		attroff(COLOR_PAIR(BORDER));
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