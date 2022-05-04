#pragma once

// Standard C libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Non-Standard C libraries
#include <curses.h>
#include <ncurses.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros


// board related functions
#define N_ROWS 60
#define N_COLS 250

// color definitions
#define WHITE       1
#define RED         2
#define YELLOW      3
#define GREEN       4
#define CYAN        5
#define BLUE        6
#define MAGENTA     7

#define SELECTED_PAIR   10
#define HOVER_PAIR      11
#define BORDER          12

// State of the game from the client end
typedef struct {
    int grid[N_ROWS][N_COLS];
    int loc_x;
    int loc_y;
    int color;
} PlayerState;


// graphics related functions
void init_all();
void init_screen();
void init_colors();
void init_mouse();
void draw_instructions();
void draw_grid(int, int);
void draw_palette();

//Player draw_all();
void draw_all();
// void draw_state(State* state);

// network related functions
int read_in(int, char*, int);
void error(char*);
int open_listener_socket();
void bind_to_port(int, int);
int say(int, char*);



int catch_signal(int sig, void (*handler) (int));
void end_game(int sig);

void init_mouse();