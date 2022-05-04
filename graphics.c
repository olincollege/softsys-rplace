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


void draw_instructions()
{
	mvprintw(0, 1, "Welcome to Terminal r/place simulations");
	mvprintw(1, 1, "CTRL+C: Quit");
	mvprintw(2, 1, "Use Left and Right arrow to select color");

}


// good for now, will need to be fixed later to account for color later
void draw_grid(int x_start, int y_start, PlayerState* player_state)
{
	
	int color;
	
	for (int row = 0; row < N_ROWS; row ++){
		for (int col = 0; col < N_COLS; col ++){
			color = player_state->grid[row][col/2];
			attron(COLOR_PAIR(color));
			mvaddch(y_start + row, x_start + col, ACS_CKBOARD);
			attroff(COLOR_PAIR(color));
		}
	}
	
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


void draw_palette(int x_start, int y_start, PlayerState * game_state) {

	int palette_height = 5;
	int palette_width = 16;

	int total_width = palette_width*8;

	int x = (N_COLS - total_width)/2 + x_start;

	for (int i = 0; i < 8; i ++){
		int x1 = x + 1 + palette_width*i;
		int y1 = y_start + N_ROWS + 1;
		rectangle(x1, y1, palette_width - 4, palette_height, i);
		
		if (game_state->color == i)
			rectangle(x1, y1 + palette_height + 1, palette_width - 4, 1, i);
	}
}

void draw_cursor(int start_x, int start_y, PlayerState * game_state) {

	int grid_x = game_state->loc_x;
	int grid_y = game_state->loc_y;
	int color = game_state->color;

	
	if (grid_x != -1 && grid_y != -1){
		mvprintw(3, 1, "X Coordinate: %d\n", grid_x);
		mvprintw(4, 1, "Y Coordinate: %d\n", grid_y);
		rectangle(grid_x*2 + start_x, grid_y + start_y, 2, 1, color);

	}

}

void draw_locked(PlayerState * game_state){
	if (game_state->locked)
		mvprintw(5, 1, "LOCKED");

}


// KEEP AS VOID FUNC!!!!
// NOTHING SHOULD BE CALCULATED IN THIS FILE!!!
// ONLY THING THAT GETS PASSED AROUND ARE THE ESSENTIALS FOR DRAWING
// KEEP THE DRAW ALL FILE AS ONLY FOR DRAWING A BUNCH OF SMALL ITEMS
// IN THE SUB FUNCITONS, ONLY PASS AROUND X_START, Y_START, AND PLAYERSTATE STRUCT
void draw_all(PlayerState * game_state) 
{
	erase();

	int x_start = (COLS - N_COLS) / 2; // adjust start x and y to center board
    int y_start = (LINES - N_ROWS ) / 2;

	draw_grid(x_start, y_start, game_state);
	draw_instructions();
	draw_palette(x_start, y_start, game_state);


	draw_cursor(x_start, y_start, game_state);

	draw_locked(game_state);

	refresh();
}