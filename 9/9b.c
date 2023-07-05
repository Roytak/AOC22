#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct point {
	int x;
	int y;
};

void
move_H(char d, int n, struct point *p)
{
	switch (d) {
	case 'U':
		p->y += n;
		break;
	case 'D':
		p->y -= n;
		break;
	case 'R':
		p->x += n;
		break;
	case 'L':
		p->x -= n;
		break;
	default:
		break;
	}

	return;
}

void
addv(struct point *t, struct point **v, int *n)
{
	int i;

	if (!v) {
		return;
	}

	for (i = 0; i < *n; i++) {
		if (t->x == (*v)[i].x && t->y == (*v)[i].y) {
			break;
		}
	}

	if (i == *n) {
		/* append */
		*v = realloc(*v, (*n + 1) * sizeof **v);
		(*v)[*n].x = t->x;
		(*v)[*n].y = t->y;
		(*n)++;
	}
}

int
around(struct point *h, struct point *t)
{
    // top left
    if ((h->x == t->x - 1) && (h->y == t->y + 1)) {
        return 1;
    }
    // top
    else if ((h->x == t->x) && (h->y == t->y + 1)) {
        return 1;
    }
    // top right
    else if ((h->x == t->x + 1) && (h->y == t->y + 1)) {
        return 1;
    }
    // left
    else if ((h->x == t->x - 1) && (h->y == t->y)) {
        return 1;
    }
    // right
    else if ((h->x == t->x + 1) && (h->y == t->y)) {
        return 1;
    }
    // bottom left
    else if ((h->x == t->x - 1) && (h->y == t->y - 1)) {
        return 1;
    }
    // bottom
    else if ((h->x == t->x) && (h->y == t->y - 1)) {
        return 1;
    }
    // bottom right
    else if ((h->x == t->x + 1) && (h->y == t->y - 1)) {
        return 1;
    }
    else {
        return 0;
    }
}

void
move_T(struct point *t, struct point *h, struct point **v, int *n, char d, int num)
{
	(void) d;
	// same place
	if (t->x == h->x && t->y == h->y) {
		addv(t, v, n);
		return;
	}

	if (around(h, t)) {
		return;
	}

	printf("%d: moved from [%d, %d] ", num, t->x, t->y);

	if ((h->x > t->x) && (h->y > t->y)) {
		t->x++;
		t->y++;
	} else if ((h->x > t->x) && (h->y < t->y)) {
		t->x++;
		t->y--;
	} else if ((h->x < t->x) && (h->y > t->y)) {
		t->x--;
		t->y++;
	} else if ((h->x < t->x) && (h->y < t->y)) {
		t->x--;
		t->y--;
	} else {
		if (h->x > t->x) {
			t->x++;
		} else if (h->x < t->x) {
			t->x--;
		} else if (h->y > t->y) {
			t->y++;
		} else if (h->y < t->y) {
			t->y--;
		}
	}

	addv(t, v, n);

	printf("to [%d, %d]\n", t->x, t->y);
}

void
print_v(struct point *v, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		printf("[%d, %d] ", v[i].x, v[i].y);
	}
	puts("");
}

void
print_p(struct point *p, char n)
{
	printf("%c: x = %d y = %d\n", n, p->x, p->y);
}

int
main(void)
{
	struct point H = {0};
	struct point T[9] = {0};
	char dir;
	int n;
	struct point *visited = calloc(1, sizeof *visited);
	int nvisited = 1;
	char buffer[256] = {0};
	int i;

	while (fgets(buffer, 256, stdin) != NULL) {
		sscanf(buffer, "%c %d", &dir, &n);
		printf("Dir: %c\n", dir);

		for (i = 0; i < n; i++) {
			move_H(dir, 1, &H);
			print_p(&H, 'H');
			move_T(&T[0], &H, NULL, NULL, dir, 1);
			move_T(&T[1], &T[0], NULL, NULL, dir, 2);
			move_T(&T[2], &T[1], NULL, NULL, dir, 3);
			move_T(&T[3], &T[2], NULL, NULL, dir, 4);
			move_T(&T[4], &T[3], NULL, NULL, dir, 5);
			move_T(&T[5], &T[4], NULL, NULL, dir, 6);
			move_T(&T[6], &T[5], NULL, NULL, dir, 7);
			move_T(&T[7], &T[6], NULL, NULL, dir, 8);
			move_T(&T[8], &T[7], &visited, &nvisited, dir, 9);
		}

		print_v(visited, nvisited);
		printf("Visited: %d\n", nvisited);
		memset(buffer, 0, 256);
	}
	return 0;
}
