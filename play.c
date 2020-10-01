/* Ben Burgess, bburgess19
 * cs 152 spr
 * proj2
 */

#include "logic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

game* read_game(int len, char** com) {
	unsigned int w, h, k, q;
	enum type type;
	if (len != 10) {
		fprintf(stderr, "read_game: improper board request\n");
		exit(1);
	}
	for(int i = 0; i < len; i++) {
		if (!strcmp(com[i], "-w"))
			w = atoi(com[i+1]);
		else if (!strcmp(com[i], "-h"))
			h = atoi(com[i+1]);
		else if (!strcmp(com[i], "-k"))
			k = atoi(com[i+1]);
		else if (!strcmp(com[i], "-q"))
			q = atoi(com[i+1]);
		else if (!strcmp(com[i], "-m"))
			type = MATRIX;
		else if (!strcmp(com[i], "-b"))
			type = BITS;
	}
	return new_game(k, q, w, h, type);
}

int col_convert(char c) {
	if (in_range(c, '0', '9'))
		return c - 48;
	else if (in_range(c, 'A','Z'))
		return c - 55;
	else if (in_range(c, 'a', 'z'))
		return c - 61;
	else 
		return -1;
}

void read_action(game* g) {
	do {
	int vertical;
	char action, col;
		printf("Choose action:\n");
		printf("\"-\": horizontal drop\n");
		printf("\"|\": vertical drop\n");
		printf("\"!\": breakdown\n\n");
		scanf("%c%*c", &action);
		if(action == '!') {
			breakdown(g);
				break;
		}
		else if ((action == '-') || (action == '|')) {
			printf("Which column?\n");
			scanf("%c%*c", &col);
			vertical = (action == '|') ? 1 : 0;
			if (!drop_stick(g, col_convert(col), vertical)) {
				printf("Unable to drop a stick there\n\n");
			}
			else break;
		}
		else
			printf("Invalid action. Try again.\n\n");
	} while(1);
}
		
int main(int argc, char** argv) {
	game *g = read_game(argc, argv);
	outcome o;
	while((o = game_outcome(g)) == IN_PROGRESS) {
		board_show(g->b);
		if (g->next == BLACK_NEXT)
			printf("Black Turn:\n");
		else
			printf("White Turn:\n");
		read_action(g);
		switch_turn(g);
	}
	board_show(g->b);
	if (o == BLACK_WIN)
		printf("BLACK WINS\n\n");
	else if (o == WHITE_WIN)
		printf("WHITE WINS\n\n");
	else printf("DRAW\n\n");
	return 0;
}
