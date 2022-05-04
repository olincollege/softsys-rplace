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

#define PORT 9999

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
    // system("xdotool key Ctrl+parenright");
    system("xdotool key Ctrl+plus");
    system("xdotool key Ctrl+plus");
    system("resize -s 24 80 > /dev/null");

    system("reset");
    
    exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[])
{
    catch_signal(SIGINT, end_game);
    // do initialization stuff for network here 
        
    // until the program closes, check for updates and then push
    system("xdotool key Ctrl+minus");
    system("xdotool key Ctrl+minus");
    // system("xdotool key Ctrl+minus");

    system("resize -s 75 300 > /dev/null");
    init_screen();
    init_mouse();


    int mouse_loc[2];

    for (;;){
        // check for read data

        

        

        get_mouse_loc(mouse_loc);
        draw_all(mouse_loc[0], mouse_loc[1]);

        



    }
    return 0;


}