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
move_T(struct point *t, struct point *h, struct point **v, int *n, char d)
{
	// same place
	if (t->x == h->x && t->y == h->y) {
		addv(t, v, n);
		return;
	}

	if (around(h, t)) {
		return;
	}

	if (d == 'R') {
		t->y = h->y;
		for (; t->x < h->x - 1;) {
			t->x++;
			addv(t, v, n);
		}
	} else if (d == 'L') {
		t->y = h->y;
		for (; t->x > h->x + 1;) {
			t->x--;
			addv(t, v, n);
		}
	} else if (d == 'U') {
		t->x = h->x;
		for (; t->y < h->y - 1;) {
			t->y++;
			addv(t, v, n);
		}
	} else if (d == 'D') {
		t->x = h->x;
		for (; t->y > h->y + 1;) {
			t->y--;
			addv(t, v, n);
		}
	}
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

int
main(void)
{
	struct point H = {0};
	struct point T = {0};
	char dir;
	int n;
	struct point *visited = calloc(1, sizeof *visited);
	int nvisited = 1;
	char buffer[256] = {0};

	while (fgets(buffer, 256, stdin) != NULL) {
		sscanf(buffer, "%c %d", &dir, &n);
		move_H(dir, n, &H);
		move_T(&T, &H, &visited, &nvisited, dir);
		printf("Dir: %c\nH: x = %d y = %d\nT: x = %d y = %d\n", dir, H.x, H.y, T.x, T.y);
		print_v(visited, nvisited);
		printf("Visited: %d\n", nvisited);
		memset(buffer, 0, 256);
	}
	return 0;
}
