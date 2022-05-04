#pragma once

// Standard C libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

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
    int grid[N_ROWS][N_COLS/2];
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
void draw_all(int mouse_x, int mouse_y); 
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
void get_mouse_loc(int* loc);
