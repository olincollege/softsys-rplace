// I had problems getting mouse movement events working in ncurses, but after
// some research, it seems as if this is how you can do it. The magic is in the
// printf("\033[?1003h\n") which was the missing piece in the puzzle for me
// (see console_codes(4) for more information). 1003 means here that all events
// (even position updates) will be reported.
//
// This seems to work in at least three X-based terminals that I've tested:
// xterm, urxvt and gnome-terminal. It doesn't work when testing in a "normal"
// terminal, with GPM enabled. Perhaps something for the next gist version? :)

#include "header.h"

int main()
{
  initscr();
  cbreak();
  noecho();
  init_screen();

  // Enables keypad mode. This makes (at least for me) mouse events getting
  // reported as KEY_MOUSE, instead as of random letters.
  keypad(stdscr, TRUE);

  // Don't mask any mouse events
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

  printf("\033[?1003h\n"); // Makes the terminal report mouse movement events

  for (;;) { 
    int c = wgetch(stdscr);
 
    // Exit the program on new line fed
    if (c == '\n')
      break;
 
    char buffer[512];
    size_t max_size = sizeof(buffer);
    if (c == ERR) {
      snprintf(buffer, max_size, "Nothing happened.");
    }
    else if (c == KEY_MOUSE) {
      MEVENT event;
      if (getmouse(&event) == OK) {
        erase();      // you can comment this out to make sure the below code is working

        // If hovering
        if (event.bstate == 0x10000000) {
          attron(COLOR_PAIR(HOVER_PAIR));
          mvaddch(event.y, event.x, ACS_DIAMOND);	// representing player location
          attroff(COLOR_PAIR(HOVER_PAIR));
        } 
        // If double-click
        if (event.bstate == 0x00000008) {
          attron(COLOR_PAIR(SELECTED_PAIR));
          mvaddch(event.y, event.x, ACS_DIAMOND);	// representing player location
          attroff(COLOR_PAIR(SELECTED_PAIR));
        }
        refresh();
      }
      else {
        snprintf(buffer, max_size, "Got bad mouse event.");
      }
    }
    else {
      snprintf(buffer, max_size, "Pressed key %d (%s)", c, keyname(c));      
    }
 
    move(0, 0);
    insertln();
    addstr(buffer);
    clrtoeol();
    move(0, 0);
  }
 
  printf("\033[?1003l\n"); // Disable mouse movement events, as l = low

  endwin();
 
  return 0;
}