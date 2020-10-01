#ifndef LOGIC_H
#define LOGIC_H

#include "board.h"


enum turn {
    BLACK_NEXT,
    WHITE_NEXT
};

typedef enum turn turn;


enum outcome {
    BLACK_WIN,
    WHITE_WIN,
    DRAW,
    IN_PROGRESS
};

typedef enum outcome outcome;


struct game {
    unsigned int stick, square;
    board* b;
    turn next;
};

typedef struct game game;

//switches turn——for testing only
void switch_turn(game* g);

//moves a tracker pointer according to the bounds of a board
void move_row(game* g, pos* p);

//copies a column in a matrix, then changes the values in the parameter
//board to EMPTY
cell* col_copy(board* b, unsigned int col);

//outputs a boolean represeting if the two cells have the same valued
int cell_compare(cell x, cell y);

//checks if a breakdown would change the board
int can_breakdown(game* g);

//creates a complete game with a board initialized to zero
game* new_game(unsigned int stick, unsigned int square, unsigned int width,
               unsigned int height, enum type type);

//frees a game and the board inside of it
void game_free(game* g);

//drops a horizontal or vertical stick into a column
int drop_stick(game* g, unsigned int col, int vertical);

//checks if a stick can be dropped, but doesn't place the stick
int dont_drop_stick(game* g, unsigned int col, int vertical);

//allows "gravity" to act normally on floating sticks
void breakdown(game* g);

//outputs the current state of a game
outcome game_outcome(game* g);

#endif /* LOGIC_H */
