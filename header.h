#pragma once

// Standard C libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Non-Standard C libraries
#include <ncurses.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

// board related functions
#define N_ROWS 60
#define N_COLS 250

// State of the Game from the server end
typedef struct {
    int n_player;
    int grid[N_ROWS][N_COLS];
} GameState;

// State of the game from the client end
typedef struct {
    int grid[N_ROWS][N_COLS];
    int loc_x;
    int loc_y;
    int color;
} PlayerState;

GameState* init_game();

// graphics related functions
void init_screen();
void draw_instructions();
void draw_grid(int x_start, int y_start);

//Player draw_all();
void draw_all();
// void draw_state(State* state);

// network related functions
int read_in(int, char*, int);
void error(char*);
int open_listener_socket();
void bind_to_port(int, int);
int say(int, char*);