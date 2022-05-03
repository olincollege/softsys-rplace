// Authors: Chris Allum, Berwin Lan, Maya Sivanandan

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
    // system("xdotool key Ctrl+parenright");
    system("xdotool key Ctrl+plus");
    system("xdotool key Ctrl+plus");
    system("resize -s 24 80 > /dev/null");
    
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    catch_signal(SIGINT, end_game);
    // do initialization stuff for network here 




    //


    // create a new instance of the game
    GameState* game_state = init_game();

    // until the program closes, check for updates and then push
    system("xdotool key Ctrl+minus");
    system("xdotool key Ctrl+minus");
    // system("xdotool key Ctrl+minus");

    system("resize -s 75 300 > /dev/null");
    init_screen();
    for (;;){
        // check for read data

        

        draw_all();







    }
    return 0;


}