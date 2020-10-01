
#ifndef BOARD_H
#define BOARD_H

#include "pos.h"


enum cell {
    EMPTY,
    BLACK,
    WHITE
};

typedef enum cell cell;

union board_rep {
    enum cell** matrix;
    unsigned int* bits;
};

typedef union board_rep board_rep;

enum type {
    MATRIX, BITS
};


struct board {
    unsigned int width, height;
    enum type type;
    board_rep u;
};

typedef struct board board;

//Adds the labels for the rows and columns for the board.
//The type indicates whether a row or column is being drawn
void labels(int num, int type);

//creates a new board struct with all empty cells
board* board_new(unsigned int width, unsigned int height, enum type type);

//frees a board and all of the cells
void board_free(board* b);

//prints a board onto the screen
void board_show(board* b);

//returns the cell at a given location
cell board_get(board* b, pos p);

//changes a cell at a given location to a given value
void board_set(board* b, pos p, cell c);

//outputs a pseudo boolean to check if a number is in between two numbers
int in_range(unsigned int n, unsigned int start, unsigned int end);

#endif /* BOARD_H */
