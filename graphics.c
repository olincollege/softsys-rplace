#include "header.h"
// #define TEST_PAIR		0
// #define SELECTOR_PAIR	1

// setup the screen
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
	init_pair(0, COLOR_CYAN, COLOR_BLACK);
	init_pair(1, COLOR_WHITE, COLOR_CYAN);

    clear();   				// empty screen
	noecho();  				// no text output
	curs_set(1);  			// cursor invisible
	cbreak();  				// no line buffering, pass every key pressed
	keypad(stdscr, true);  	// keypad enabled
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







// Player draw_all(int player_x, int player_y)
// {
//     erase(); // clear screen
    
//     draw_instructions();

// 	attron(COLOR_PAIR(TEST_PAIR));
// 	mvaddch(2, 1, ACS_CKBOARD);		// representing pixel
// 	attroff(COLOR_PAIR(TEST_PAIR));

// 	attron(COLOR_PAIR(SELECTOR_PAIR));
// 	mvaddch(player_y, player_x, ACS_DIAMOND);	// representing player location
// 	attroff(COLOR_PAIR(SELECTOR_PAIR));

// 	// Update selector location
// 	int ch;
// 	ch = getch();
// 	if (ch == KEY_LEFT)
// 		player_x--;	
// 	if (ch == KEY_RIGHT)
// 		player_x++;
// 	if (ch == KEY_UP)
// 		player_y--;
// 	if (ch == KEY_DOWN)
// 		player_y++;

//     refresh();
// 	return (Player){player_x, player_y};
// }








// KEEP AS VOID FUNC!!!!
// NOTHING SHOULD BE CALCULTED IN THIS FILE!!!
// ONLY THING THAT GETS PASSED AROUND ARE THE ESENTIALS FOR DRAWING
// KEEP THE DRAW ALL FILE AS ONLY FOR DRAWING A BUNCH OF SMALL ITEMS
// IN THE SUB FUNCITONS, ONLY PASS AROUND X_START, Y_START, AND PLAYERSTATE STRUCT
void draw_all(){
	erase();

	int x_start = (COLS - N_COLS) / 2; // adjust start x and y to center board
    int y_start = (LINES - N_ROWS )/ 2;


	draw_instructions();
	draw_grid(x_start, y_start);

	refresh();
}