/* Ben Burgess, bburgess19
 * cs 152 spr
 * proj1
 */

#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

game* new_game(unsigned int stick, unsigned int square, unsigned int width,
			   unsigned int height, enum type type)
{
	if(height <= 2) {
		fprintf(stderr, "height is too small\n");
		exit(1);
	} else if(width <= 2) {
		fprintf(stderr, "width is too small\n");
		exit(1);
	} else if(stick <= 0) {
		fprintf(stderr, "stick is too small\n");
		exit(1);
	} else if(stick >= height) {
		fprintf(stderr, "stick is too big for the height\n");
		exit(1);
	} else if(stick >= width) {
		fprintf(stderr, "stick is too big for the heigth\n");
		exit(1);
	} else if((square + 2 > height) && (square + 2 > width)) {
		fprintf(stderr, "square dimensions are too big for the board\n");
		exit(1);
	} else if(square <= 1) {
		fprintf(stderr, "square is too small\n");
		exit(1);
	}

	srand(time(0));
	game* out = (game*)malloc(sizeof(game));
	if (out==NULL) {
		fprintf(stderr, "new_game: unable to allocate memory\n");
		exit(1);
	}
	out->b = board_new(width, height, type);
	out->stick = stick;
	out->square = square;

	unsigned int r = rand() % 2;
	switch(r) {
		case 0:
			out->next = BLACK_NEXT;
			break;
		case 1:
			out->next = WHITE_NEXT;
			break;
		default:
			fprintf(stderr, "new_game: you shouldn't be seeing this\n");
			exit(1); } return out;
}

void game_free(game* g) {
	board_free(g->b);
	free(g);
}

void switch_turn(game* g) {
	if (g->next == BLACK_NEXT)
		g->next = WHITE_NEXT;
	else
		g->next = BLACK_NEXT;
}

void move_row(game* g, pos* p) {
	if(p->r == g->b->height - 1) {
		if (p->c != g->b->width - 1)
			p->r = 0;
		else
			p->r++;
		p->c++;
	} else
		p->r++;
}

int drop_stick(game* g, unsigned int col, int vertical) {
	unsigned int i = 0, open = 0;
	pos p = {0, col};
	if (!in_range(col, 0, g->b->width - 1)) return 0;
	if (!vertical) {
		if (col + g->stick > g->b->width)
			return 0;
		else {
			while((board_get(g->b, p) == EMPTY) && (open < g->b->height)) {
				if (i < g->stick - 1) {
					i++;
					p.c++;
				} else {
					p.c = col;
					i = 0;
					open++;
					if (p.r < g->b->height - 1)
						p.r++;
				}
			}
			if (open == 0)
				return 0;
			if (board_get(g->b, p) != EMPTY)
				p.r--;
			p.c = col;
			for(i = 0; i < g->stick; i++) {
				if (g->next == BLACK_NEXT)
					board_set(g->b, p, BLACK);
				else
					board_set(g->b, p, WHITE);
				p.c++;
			}
		}
		return 1;
	}
	else {
		while((board_get(g->b, p) == EMPTY) && (open < g->b->height - 1)) {
			p.r = ++open;
		}
		if ((p.r != 0) && board_get(g->b, p) != EMPTY)
			p.r--;
		if (open < g->stick)
			return 0;
		else {
			for(i = 0; i < g->stick; i++) {
				if (g->next == BLACK_NEXT) 
					board_set(g->b, p, BLACK);
				else 
					board_set(g->b, p, WHITE);
				p.r--;
			}
			return 1;
		}
	}
}

int dont_drop_stick(game* g, unsigned int col, int vertical) {
	unsigned int i = 0, open = 0;
	pos p = {0, col};
	
	if (!vertical) {
		if (col + g->stick > g->b->width)
			return 0;
		else {
			while((board_get(g->b, p) == EMPTY) && (open < g->b->height)) {
				if (i < g->stick - 1) {
					i++;
					p.c++;
				} else {
					p.c = col;
					i = 0;
					open++;
					if (p.r < g->b->height - 1)
						p.r++;
				}
			}
			if (open == 0)
				return 0;
			if (board_get(g->b, p) != EMPTY)
				p.r--;
			p.c = col;
		}
		return 1;
	}
	else {
		while((board_get(g->b, p) == EMPTY) && (open < g->b->height - 1)) {
			p.r = ++open;
		}
		if ((p.r != 0) && board_get(g->b, p) != EMPTY)
			p.r--;
		if (open < g->stick)
			return 0;
		else {
			return 1;
		}
	}
}

int can_breakdown(game* g) {
	char present;
	pos p = {0, 0};
	while((p.r < g->b->height) && (p.c < g->b->width)) {
	cell color = board_get(g->b, p);
		if (color != EMPTY)
			present = 1;
		if ((color == EMPTY) && present)
			return 1;
		else {
			if (p.r == g->b->height - 1) {
					p.r = 0;
					p.c++;
					present = 0;
				} else
					p.r++;
		}
	}
	return 0;
}

void breakdown(game* g) {
	pos p, tracker;
	int is_space;
	for (unsigned int c = 0; c < g->b->width; c++) {
		is_space = 0;
		for (int r = g->b->height - 1; r > -1; r--) {
			p.r = r;
			p.c = c;
			if (board_get(g->b, p) == EMPTY) {
				is_space++;
				if (is_space == 1) {
					tracker.r = p.r;
					tracker.c = p.c;
				}
			} else if ((is_space) && (board_get(g->b, p) != EMPTY)) {
				board_set(g->b, tracker, board_get(g->b, p));
				board_set(g->b, p, EMPTY);
				tracker.r--;
			}
		}
	}
}	

int cell_compare(cell x, cell y) {
	return (x == y);
}

int can_move(game* g) {
	int vertical = 1, i = 0;
	int iterations = g->b->width + (g->b->width - (g->stick - 1));
	while(iterations > 0) {
		if (i == g->b->width) {
			vertical = 0;
			i = 0;
		} 
		if (dont_drop_stick(g, i, vertical))
			return 1;
		i++;
		iterations--;
	}
	return can_breakdown(g);
}

outcome game_outcome(game* g) {
	int b = 0, w = 0, count = 0;
	pos p = {0, 0};
	cell color = board_get(g->b, p);
	cell prev = board_get(g->b, p);
	outcome out;
	while((p.r < g->b->height) && (p.c < g->b->width)) {
		if (count == 0) prev = color;
		if ((color != EMPTY) && (cell_compare(color, prev))) {
				//If the cube has been formed
				if ((count + 1) == g->square * g->square) {
					(color == BLACK) ? b++ : w++;
					count = 0;
					p.c -= g->square - 1;
					move_row(g, &p);
				}
				//At the end of an "arm" of a cube i.e.   v
				//																		*****
				else if (((count + 1) % g->square == 0) &&
						   		(count + 1 != g->square * g->square)) {
					if (p.r == g->b->height - 1) {
						count = 0;
						p.c -= (g->square - 1);
					} 
					else {
						p.c -= g->square - 1;
						count++;
					}
					move_row(g, &p);
				} 
				else {
					p.c++;
					count++;
				}
		}
		else {
			p.c -= (count % g->square);
			count = 0;
			move_row(g, &p);
		}
		if((p.r < g->b->height) && (p.c < g->b->width)) {
			prev = color;
			color = board_get(g->b, p);
		}
	}

	if ((b && w) || !can_move(g))
		out = DRAW;
	else if (b)
		out = BLACK_WIN;
	else if (w)
		out = WHITE_WIN;
	else
		out = IN_PROGRESS;
	return out;
}
