#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list;

struct element {
	int is_int;

	union {
		int value;
		struct list *list;
	};
};

struct list {
	struct element *items;
	int nitems;
};

int
make_sublist(char *buffer, struct element *e)
{
	int i, read, j;
	char dig[5] = {0};

	e->is_int = 0;
	e->list = calloc(1, sizeof *e->list);

	i = 0;
	while (buffer[i] != ']') {
		if (buffer[i] == '[') {
			e->list->items = realloc(e->list->items, (e->list->nitems + 1) * sizeof *e->list->items);
			i++;
			read = make_sublist(&buffer[i], &e->list->items[e->list->nitems]);
			e->list->nitems++;
			i += read;
		} else if (isdigit(buffer[i])) {
			j = 0;
			while (isdigit(buffer[i])) {
				dig[j] = buffer[i];
				j++;
				i++;
			}
			e->list->items = realloc(e->list->items, (e->list->nitems + 1) * sizeof *e->list->items);
			e->list->items[e->list->nitems].is_int = 1;
			e->list->items[e->list->nitems].value = atoi(dig);
			e->list->nitems++;
			memset(dig, 0, 5);
		} else if (buffer[i] == ',') {
			i++;
		}
	}

	return i + 1;
}

struct list *
make_list(char *buffer)
{
	int i, j, read;
	struct list *l;
	char dig[5] = {0};

	l = calloc(1, sizeof *l);
	for (i = 0; buffer[i]; i++) {
		if (buffer[i] == '[') {
			l->items = realloc(l->items, (l->nitems + 1) * sizeof *l->items);
			i++;
			read = make_sublist(&buffer[i], &l->items[l->nitems]);
			l->nitems++;
			i += read;
		} else if (isdigit(buffer[i])) {
			j = 0;
			while (isdigit(buffer[i])) {
				dig[j] = buffer[i];
				j++;
				i++;
			}
			l->items = realloc(l->items, (l->nitems + 1) * sizeof *l->items);
			l->items[l->nitems].is_int = 1;
			l->items[l->nitems].value = atoi(dig);
			l->nitems++;
			memset(dig, 0, 5);
		}
	}

	return l;
}

// return 1 if ok
int
check_order(struct list *left, struct list *right)
{
	int i, ret;
	struct list *l;

	if (!left->nitems && !right->nitems) {
		return -1;
	} else if (!left->nitems) {
		//printf("\tLeft side is smaller, so inputs are in the right order.\n");
		return 1;
	} else if (!right->nitems) {
		//printf("\tRight side ran out of items, so inputs are not in the right order.\n");
		return 0;
	}

	for (i = 0; i < left->nitems; i++) {
		if (i == right->nitems) {
			//printf("\tRight side ran out of items, so inputs are not in the right order.\n");
			return 0;
		}

		if (left->items[i].is_int && right->items[i].is_int) {
			// both ints
			if (right->items[i].value > left->items[i].value) {
				//printf("\tLeft side is smaller, so inputs are in the right order.\n");
				return 1;
			} else if (right->items[i].value < left->items[i].value) {
				//printf("\tRight side is smaller, so inputs are not in the right order.\n");
				return 0;
			}
		} else if (!left->items[i].is_int && !right->items[i].is_int) {
			// both lists
			ret = check_order(left->items[i].list, right->items[i].list);
			if (ret != -1) {
				return ret;
			}
		} else if (left->items[i].is_int && !right->items[i].is_int) {
			// left is int
			l = malloc(sizeof *l);
			l->items = malloc(sizeof *l->items);
			l->items->is_int = 1;
			l->items->value = left->items[i].value;
			l->nitems = 1;
			ret = check_order(l, right->items[i].list);
			if (ret != -1) {
				return ret;
			}
		} else if (!left->items[i].is_int && right->items[i].is_int) {
			// right is int
			l = malloc(sizeof *l);
			l->items = malloc(sizeof *l->items);
			l->items->is_int = 1;
			l->items->value = right->items[i].value;
			l->nitems = 1;
			ret = check_order(left->items[i].list, l);
			if (ret != -1) {
				return ret;
			}
		}
	}

	if (i < right->nitems) {
		//printf("\tLeft side ran out of items, so inputs are in the right order.\n");
		return 1;
	}

	return -1;
}

int
insert(struct list *l, struct list **ll, int nll)
{
	int i;
	struct list *tmp;

	if (!nll) {
		ll[nll] = l;
		return 1;
	}

	for (i = 0; i < nll; i++) {
		if (check_order(l, ll[i]) == 1) {
			// l is smaller
			if (i + 1 == nll) {
				// instead of last
				tmp = ll[i];
				ll[i] = l;
				ll[i + 1] = tmp;
			} else {
				tmp = ll[i];
				ll[i] = l;
				memmove(&ll[i + 2], &ll[i + 1], (nll - i - 1) * sizeof *ll);
				ll[i + 1] = tmp;
			}
			return i + 1;
		}
	}

	ll[i] = l;
	return i + 1;
}

int
main(void)
{
	FILE *f;
	char buffer[512] = {0};
	struct list *list, **ll;
	int nll = 0, pos1, pos2;
	char buf1[] = "[2]]";
	char buf2[] = "[6]]";

	ll = calloc(sizeof *ll, 100 * sizeof *ll);

	f = fopen("in.txt", "r");
	while (1) {
		if (!fgets(buffer, 512, f)) {
			break;
		}
		if (buffer[0] == '\n') {
			continue;
		}
		list = make_list(buffer + 1);
		insert(list, ll, nll);
		nll++;

		memset(buffer, 0, 512);
	}
	list = make_list(buf1);
	pos1 = insert(list, ll, nll);
	nll++;
	list = make_list(buf2);
	pos2 = insert(list, ll, nll);
	nll++;

	for (int i =0; i < nll; i++) {
		printf("item cnt: %d\n", ll[i]->nitems);
	}

	printf("pos 2 = %d pos 6 = %d\n", pos1, pos2);

	return 0;
}
