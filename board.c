#include "header.h"


GameState* init_game(){
    GameState* game_state = malloc(sizeof(GameState));
    memset(game_state->grid, 0, sizeof(game_state->grid));
    return game_state;
}

