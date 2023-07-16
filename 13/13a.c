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
main(void)
{
	FILE *f;
	char buffer[512] = {0};
	struct list *left, *right;
	int i, total = 0;

	f = fopen("in.txt", "r");
	i = 1;
	while (1) {
		if (!fgets(buffer, 512, f)) {
			break;
		}
		if (buffer[0] == '\n') {
			continue;
		}
		left = make_list(buffer + 1);

		memset(buffer, 0, 512);
		fgets(buffer, 512, f);
		right = make_list(buffer + 1);

		printf("Line %d:\n", i);
		if (check_order(left, right)) {
			printf("\tCorrect\n");
			total += i;
		} else {
			printf("\tWrong\n");
		}

		i++;
	}

	printf("Total %d.\n", total);

	return 0;
}
