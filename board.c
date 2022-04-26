#include "header.h"


State* init(){
    State* state = malloc(sizeof(State));
    memset(state->grid, 0, sizeof(state->grid));
    return state;
}

