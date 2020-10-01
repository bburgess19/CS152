// Practice

typedef struct intlist intlist;
struct intlist {
	int value;
	intlist* next;
};

intlist* cons(int first, intlist* rest);

int is_empty(intlist* l);

int first(intlist* l);

intlist* rest(intlist* l);

int sum(intlist* l);

intlist* squares_copy(intlist* l);

intlist* evens(intlist* l);

void list_free(intlist* l);

void remove_head(intlist** l);

void remove_end(intlist** l);

void remove_n(intlist** l, unsigned int n);

intlist* reverse(intlist* l);
