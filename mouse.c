#include <curses.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

void init_mouse()
{
  keypad(stdscr, TRUE);
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  printf("\033[?1003h\n");
}

// Sample code for how this could be integrated.
// The important part is in the for loop
// void main_mouse() {
//   init_all();

//   for (;;) {
//     MEVENT event = mouse();

//     erase();      // you can comment this out to make sure the below code is working

//     // If hovering
//     if (event.bstate == 0x10000000) {
//       attron(COLOR_PAIR(HOVER_PAIR));
//       mvaddch(event.y, event.x, ACS_DIAMOND);	// representing player location
//       attroff(COLOR_PAIR(HOVER_PAIR));
//     } 
//     // If double-click
//     if (event.bstate == 0x00000008) {
//       attron(COLOR_PAIR(SELECTED_PAIR));
//       mvaddch(event.y, event.x, ACS_DIAMOND);	// representing player location
//       attroff(COLOR_PAIR(SELECTED_PAIR));
//     }
//     refresh();
//   }
// }

void get_mouse_loc(int* loc)
{
  MEVENT event;
  getmouse(&event);

  if (event.bstate == 0x10000000) {
    loc[0] = event.x;
    loc[1] = event.y;
  }
  // If double-click
  if (event.bstate == 0x00000008) {
    loc[0] = event.x;
    loc[1] = event.y;
  }
}
