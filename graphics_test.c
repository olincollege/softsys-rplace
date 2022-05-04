// Authors: Chris Allum, Berwin Lan, Maya Sivanandan
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros


#include "header.h"


int catch_signal(int sig, void (*handler) (int)) {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

void end_game(int sig)
{   
    endwin();
    system("xdotool key Ctrl+plus");
    system("xdotool key Ctrl+plus");
    system("resize -s 24 80 > /dev/null");

    printf("\033[?1003l\n");
    
    exit(EXIT_SUCCESS);
}

void get_grid_loc(int mouse_loc[2], int grid_loc[2])
{
	int x =  mouse_loc[0];
	int y =  mouse_loc[1];

    int x_start =  (COLS - N_COLS) / 2;
    int y_start = (LINES - N_ROWS ) / 2;
	
    int grid_x, grid_y;

	if (x_start <= x && x < x_start + N_COLS -1){
		if (y_start <= y && y < y_start + N_ROWS){
			grid_x = (floor(x/2)*2 + x_start%2 - x_start)/2;
            grid_y = y - y_start;
		}
	}
    else{
        grid_x = -1;
        grid_y = -1;
    }

    grid_loc[0] = grid_x;
    grid_loc[1] = grid_y;
}


int main(int argc, char *argv[])
{
    catch_signal(SIGINT, end_game);
    // do initialization stuff for network here 
        
    // until the program closes, check for updates and then push
    system("xdotool key Ctrl+minus");
    system("xdotool key Ctrl+minus");
    // system("xdotool key Ctrl+minus");

    system("resize -s 75 222 > /dev/null");
    init_screen();
    init_mouse();


    int mouse_loc[2];

    for (;;){

                        
        // check for read data

        
        get_mouse_loc(mouse_loc);
        draw_all(mouse_loc);

        



    }
    return 0;


}