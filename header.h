#pragma once

// Standard C libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>

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

#define PORT 9999

// board related functions
#define N_ROWS 30 //50
#define N_COLS 150 //200

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
    int grid[N_ROWS][N_COLS/2];
    int loc_x;
    int loc_y;
    int color;
    int locked;
} PlayerState;


// graphics related functions
void init_all();
void init_screen();
void init_colors();
void init_mouse();
void draw_instructions();
void draw_grid(int x_start, int y_start, PlayerState* player_state);
void draw_palette(int x_start, int y_start, PlayerState * game_state);

//Player draw_all();
void draw_all(PlayerState * game_state);
// void draw_state(State* state);

// network related functions
int read_in(int, char*, int);
void error(char*);
int open_listener_socket();
void bind_to_port(int, int);
int say(int, char*);

// Mouse function
MEVENT mouse();


// macros for packing floats and doubles
#define pack754_16(f) (pack754((f), 16, 5))
#define pack754_32(f) (pack754((f), 32, 8))
#define pack754_64(f) (pack754((f), 64, 11))
#define unpack754_16(i) (unpack754((i), 16, 5))
#define unpack754_32(i) (unpack754((i), 32, 8))
#define unpack754_64(i) (unpack754((i), 64, 11))

// Packing functions
unsigned long long int pack754(long double f, unsigned bits, unsigned expbits);
long double unpack754(unsigned long long int i, unsigned bits, unsigned expbits);
void packi16(unsigned char *buf, unsigned int i);
void packi32(unsigned char *buf, unsigned long int i);
void packi64(unsigned char *buf, unsigned long long int i);
int unpacki16(unsigned char *buf);
unsigned int unpacku16(unsigned char *buf);
long int unpacki32(unsigned char *buf);
unsigned long int unpacku32(unsigned char *buf);
long long int unpacki64(unsigned char *buf);
unsigned long long int unpacku64(unsigned char *buf);
unsigned int pack(unsigned char *buf, char *format, ...);
void unpack(unsigned char *buf, char *format, ...);


int catch_signal(int sig, void (*handler) (int));
void end_game(int sig);

void init_mouse();
void get_mouse_loc(int ch, int* loc);

void get_grid_loc(int mouse_loc[2], int grid_loc[2]);
void draw_cursor(int start_x, int start_y, PlayerState * game_state);
void get_color(int ch, PlayerState* player_state);
void rectangle(int x_start, int y_start, int width, int height, int color);