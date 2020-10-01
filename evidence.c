
/* Ben Burgess, bburgess19
 * cs 152 spr
 * proj1
 */

#include "board.h"
#include "pos.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>

/* tests for board_new */
void evidence_board_new () {
	board* bits = board_new(5, 5, BITS);
	pos p = {2, 2};
	board_set(bits, p, BLACK);
	cell b = board_get(bits, p);
	printf((b == BLACK) ? "It's black\n" : "It's not black\n"); 
	board_free(bits);
}

/* tests for board_show */
void evidence_board_show() {
	game* g = new_game(3, 3, 10, 10, BITS);
	outcome o = IN_PROGRESS;
	drop_stick(g, 0, 1);
	/*drop_stick(g, 1, 1);
	drop_stick(g, 2, 1);
	switch_turn(g);
	drop_stick(g, 4, 1);
	drop_stick(g, 5, 1);
	drop_stick(g, 6, 1);
	//board_show(g->b);
	//switch_turn(g);
	//drop_stick(g, 3, 1);
	//drop_stick(g, 4, 1);
	breakdown(g); */
	board_show(g->b);
	printf("Expected: 1\nActual: %d\n", o == game_outcome(g));
	game_free(g);
}


int main(int argc, char** argv) {
	evidence_board_new();
	evidence_board_show();
	return 0;
}
