
#include "header.h"


void init_mouse()
{
  keypad(stdscr, TRUE);

  // Don't mask any mouse events
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

  printf("\033[?1003h\n"); // Makes the terminal report mouse movement events

}


void get_mouse_loc(int ch, int* loc)
{
    MEVENT event;
    if (ch == KEY_MOUSE) {
      if (getmouse(&event) == OK) {
        loc[0] = event.x;
        loc[1] = event.y;
      }
    }   
}


