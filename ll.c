//Practice

#include <stdlib.h>
#include <stdio.h>
#include "ll.h"

intlist* cons(int first, intlist* rest) {
	intlist* res = (intlist*)malloc(sizeof(intlist));
	if (res == NULL) {
		fprintf(stderr, "cons: unable to allocate\n");
		exit(1);
	}
	res->value = first;
	res->next = rest;
	return res;
}

int is_empty(intlist* l) {
	return l == NULL;
}

int first(intlist* l) {
	if (l != NULL) {
		return l->value;
	}

	fprintf(stderr, "first: empty list\n");
	exit(1);
}
	
intlist* rest(intlist* l) {
	if (l != NULL) {
		return l->next;
	}
	
	fprintf(stderr, "rest: empty list\n");
	exit(1);
}

int sum(intlist* l) {
	int res = 0;
	while (l) {
		res += l->value;
		l = l->next;
	}
	return res;
}

intlist* squares_copy(intlist* l) {
	if (is_empty(l)) {
		return NULL;
	}
	return cons(first(l) * first(l), squares_copy(rest(l)));
}

intlist* evens(intlist* l) {
	intlist* g = NULL;
	intlist* tail;
	while (l) {
		if (l->value % 2 == 0) {
			intlist* item = cons(l->value, NULL);
			if (g) {
				tail->next = item;
			} else {
				g = item;
			}
			tail = item;
		}
		l = l->next;
	}
	return g;
}

void list_free(intlist* l) {
	intlist* next;
	while (l) {
		next = l->next;
		free(l);
		l = next;
	}
}	

void remove_end(intlist** l) {
	intlist* temp = *l;
	if (*l == NULL) {
		fprintf(stderr, "remove_end: passed in empty list\n");
		exit(1);
	} else if ((*l)->next == NULL) {
			free(*l);
	} else {
		while (*l) {
			if ((*l)->next->next == NULL) {
				free((*l)->next);
				(*l)->next = NULL;
				break;
			}
			*l = (*l)->next;
		}
		*l = temp;
	}
}		
	
void remove_head(intlist** l) {
	if (*l == NULL) {
		fprintf(stderr, "remove_head: passed in empty array\n");
		exit(1);
	}
	intlist* temp = *l;
	*l = (*l)->next;
	free(temp);
}

void remove_n(intlist** l, unsigned int n) {
	intlist* temp = *l;
	if ((*l)->next == NULL) {
			remove_end(l);
	} 
	if (n == 0) {
		remove_head(l);
	} else {
		while (n) {
			 if (n == 1) {
				(*l)->next = (*l)->next->next;
				free((*l)->next);
				break;
			}
			*l = (*l)->next;
			n--;
		}
		*l = temp;
	}
}

/*void reverse(intlist** l) {
	intlist* prev = NULL;
	intlist* curr = *l;
	intlist* next;
	while(curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*l = prev;
} */

intlist* reverse(intlist* l) {
	if((!l->next) || !l) {
		return l;
	}
	else {
		intlist* head = reverse(l->next);
		l->next->next = l;
		l->next = NULL;
		return head;
	}
}	
		


