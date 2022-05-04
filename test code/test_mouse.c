// I had problems getting mouse movement events working in ncurses, but after
// some research, it seems as if this is how you can do it. The magic is in the
// printf("\033[?1003h\n") which was the missing piece in the puzzle for me
// (see console_codes(4) for more information). 1003 means here that all events
// (even position updates) will be reported.
//
// This seems to work in at least three X-based terminals that I've tested:
// xterm, urxvt and gnome-terminal. It doesn't work when testing in a "normal"
// terminal, with GPM enabled. Perhaps something for the next gist version? :)

#include <curses.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>



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
    system("reset");
    
    exit(EXIT_SUCCESS);
}


void get_mouse_loc(int* loc)
{
    int c = getch();
    MEVENT event;
    if (c == KEY_MOUSE) {
      if (getmouse(&event) == OK) {
        loc[0] = event.x;
        loc[1] = event.y;
      }
    }   
}
 
int main()
{
    catch_signal(SIGINT, end_game);
    initscr();
    cbreak();
    noecho();

    // Enables keypad mode. This makes (at least for me) mouse events getting
    // reported as KEY_MOUSE, instead as of random letters.
    keypad(stdscr, TRUE);

    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    printf("\033[?1003h\n"); // Makes the terminal report mouse movement events

    int test[2];
    for (;;) { 
        get_mouse_loc(test);
        printf("%d\n",test[0]);
        printf("%d\n",test[1]);

    }
    
    printf("\033[?1003l\n"); // Disable mouse movement events, as l = low

    endwin();
    
    return 0;
}


