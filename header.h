#pragma once

// Standard C libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Non-Standard C libraries
#include <ncurses.h>

// board related functions
#define N_ROWS 100
#define N_COLS 100

// state of board, will add more to later
typedef struct{
    int grid[N_ROWS][N_COLS];
    int current_x;
    int current_y;
    int current_color;
} State;

State* init();

// graphics related functions
void init_screen();
void draw_instructions();
void draw_all();
void draw_state(State* state);

