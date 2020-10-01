/* Ben Burgess, bburgess19
 * cs 152 spr
 * proj1
 */

#include "board.h"
#include <stdlib.h>
#include <stdio.h>

board* board_new(unsigned int width, unsigned int height, enum type type) {
	int i = 0;
	int cells = (width * height * 2);
	board* out = (board*)malloc(sizeof(board));
	if (out==NULL) {
		fprintf(stderr, "board_new: unable to allocate memory\n");
		exit(1);
	}
	out->width = width; 
	out->height = height;
	out->type = type;
	switch(type) {
		case MATRIX:
			out->u.matrix = (cell**)malloc(sizeof(cell*) * height);
			for (int r = 0; r < height; r++) {
				out->u.matrix[r] = (cell*)malloc(sizeof(cell) * width);
				for (int c = 0; c < width; c++) {
					out->u.matrix[r][c] = EMPTY;
				}
			}
			break;
		case BITS:
			out->u.bits = (unsigned int*)malloc((cells/32 + (cells/32 != 0))
										 * sizeof(unsigned int));
			while(out->u.bits[i]) {
				out->u.bits[i++] = 0;
			}
	}
	return out;
}
void board_free(board* b) {
	if (b->type == MATRIX) {
		for (int r = 0; r < b->height; r++) {
			free(b->u.matrix[r]);
		}
		free(b->u.matrix);
	}
	else free(b->u.bits);
	free(b);
}

void labels(int num, int type) {
	unsigned char i;
	switch(type) {
		case 0:
			printf("  ");
			for (i = 0; i < num; i++) {
				if (i < 10)
					printf((i == num - 1) ? "%d\n" : "%d", i);
				else if (i < 36)
					printf((i == num - 1) ? "%c\n" : "%c", i + 55);
				else if (i < 62)
					printf((i == num - 1) ? "%c\n" : "%c", i + 61);
				else 
					printf((i == num - 1) ? "?\n" : "?");
			}
			break;
		case 1:
			if (num < 10)
				printf("%d ", num);
			else if (num < 36)
				printf("%c ", num + 55);
			else if (num < 62)
				printf("%c ", num + 61);
			else
				printf("? ");
			break;
		default:
			fprintf(stderr, "labels: improper type\n");
			exit(1);
	}
}

void board_show(board* b) {
	labels(b->width, 0);
	pos p = {0,0};
	for(int r = 0; r < b->height; r++) {
		labels(r, 1);
		p.r = r;
		for(int c = 0; c < b->width; c++) {
			p.c = c;
			switch(board_get(b, p)) {
				case EMPTY:
					printf((c == b->width - 1) ? ".\n" : ".");
					break;
				case BLACK:
					printf((c == b->width - 1) ? "*\n" : "*");
					break;
				case WHITE:
					printf((c == b->width - 1) ? "o\n" : "o");
					break;
				default:
					fprintf(stderr, "You shouldn't be seeing this\n");
					exit(1);
			}
		}
	}
	printf("\n\n");
}	

int in_range(unsigned int n, unsigned int start, unsigned int end) {
	return ((n >= start) && (n <= end));
}

cell board_get(board* b, pos p) {
	if (b->type == MATRIX) {
		if ((in_range(p.r, 0, b->height - 1)) && (in_range(p.c, 0, b->width - 1)))
			return b->u.matrix[p.r][p.c];
		else {
			fprintf(stderr, "board_get: out of matrix\n");
			exit(1);
		}
	}
	else {
		unsigned int bits = ((p.r * b->width) + p.c) * 2;
		char mask = 0x3;
		switch(((b->u.bits[bits / 32]) >> (bits - (32 * (bits / 32)))) & mask) {
			case 0:
				return EMPTY;
				break;
			case 1:
				return BLACK;
				break;
			case 2:
				return WHITE;
				break;
			default:
				fprintf(stderr, "board_get: you shouldn't be seeing this\n");
				exit(1);
		}
	}
}

void board_set(board* b, pos p, cell c) {
	if (b->type == MATRIX) {
		if ((in_range(p.r, 0, b->height - 1)) && (in_range(p.c, 0, b->width - 1))) 
			b->u.matrix[p.r][p.c] = c;
		else {
			fprintf(stderr, "board_set: out of matrix\n");
			exit(1);
		}
	}
	else {
		unsigned int bits = ((p.r * b->width) + p.c) * 2;
		int holder = b->u.bits[bits / 32];
		int type = (c == BLACK) ? 1 : (c == WHITE) ? 2 : 0;
		int copy = 0, mask = 0x3;
		int i, j = (bits - (32 * (bits / 32))) / 2;
		for(i = 15; i >= 0; i--) {
				char color = ((holder >> i * 2) & mask) % 3;
				if (i == j) copy += type;
				else if (color == 1) copy += 1;
				else if (color == 2) copy += 2;
				else;
			if (i != 0) {
				copy <<= 2;
			}
		}		
		b->u.bits[bits/32] = copy; 
	}
}
