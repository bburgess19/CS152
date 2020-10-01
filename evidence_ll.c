//Practice

#include <stdlib.h>
#include <stdio.h>
#include "ll.h"
	
//printing lists
void list_print(intlist* l) {
	if (l == NULL) {
		fprintf(stderr, "list_print: empty list");
		exit(1);
	}
	while (l) {
		printf("%d, ", l->value);
		l = l->next;
	}
	printf("\n");
}


//tests for sum
void evidence_sum() {
	intlist* s = cons(1, cons(2, cons(3, NULL)));
	printf("*** testing sum\n");
	printf("Expected: 6 Actual: %d\n", sum(s));
	free(s);
}

//tests for squares_copy
void evidence_squares_copy() {
	intlist* s = cons(1, cons(2, cons(3, NULL)));
	printf("*** testing squares_copy\n");
	printf("Expected 1, 4, 9\n");
	printf("Actual: "); list_print(squares_copy(s));
	free(s);
}

//tests for evens
void evidence_evens() {
	intlist* s = cons(1, cons(2, cons(3, cons(4, NULL))));
	printf("*** testing evens\n");
	printf("Expected: 2, 4\n");
	printf("Actual: "); list_print(evens(s));
	free(s);
}

//tests for remove_end
void evidence_remove_end() {
	intlist* s = cons(1, cons(2, cons(3, cons(4, NULL))));
	intlist* r = cons(1, NULL);
	printf("*** testing remove_end\n");
	printf("Expected: 1, 2, 3,\n");
	printf("Actual: "); remove_end(&s); list_print(s);
	free(s); free(r);
}

//tests for remove
void evidence_remove() {
	intlist* s = cons(1, cons(2, cons(3, cons(4, NULL))));
	printf("*** testing remove\n");
	printf("Expected: 2, 3, 4,\n");
	printf("Actual: "); remove_n(&s, 0); list_print(s);
	free(s);
}

//tests for reverse
void evidence_reverse() {
	intlist* s = cons(1, cons(2, cons(3, cons(4, NULL))));
	printf("*** testing reverse\n");
	printf("Expected: 4, 3, 2, 1\n");
	printf("Actual: "); list_print(reverse(s));
}

int main(int argc, char** argv) {
	evidence_sum();
	evidence_squares_copy();
	evidence_evens();
	evidence_remove_end();
	evidence_remove();
	evidence_reverse();
	return 0;
}
