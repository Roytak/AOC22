#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 41
#define COLS 93
#define SIZE 1024

struct node {
	int x;
	int y;
	int steps;
};

struct queue_node {
	struct node *data;
	struct queue_node *next;
};

struct queue {
	struct queue_node *front;
	struct queue_node *rear;
};

char buf[ROWS][COLS];
struct node ancestors[SIZE];
int nancestors;

struct queue_node *
new_queue_node(struct node *data)
{
	struct queue_node *n;

	n = malloc(sizeof *n);
	n->data = data;
	n->next = NULL;

	return n;
}

struct node *
new_node(int x, int y, int steps)
{
	struct node *n;

	n = malloc(sizeof *n);
	n->x = x;
	n->y = y;
	n->steps = steps;

	return n;
}

int
dupl_open(struct queue *q, struct node *n)
{
	struct queue_node *iter;

	for (iter = q->front; iter; iter = iter->next) {
		if ((iter->data->x == n->x) && (iter->data->y == n->y)) {
			return 1;
		}
	}

	return 0;
}

int
ance_open(struct node *n)
{
	int i;

	for (i = 0; i < nancestors; i++) {
		if ((ancestors[i].x == n->x) && (ancestors[i].y == n->y)) {
			return 1;
		}
	}

	return 0;
}

void
enqueue(struct queue *q, struct node *n)
{
	struct queue_node *qn;

	qn = new_queue_node(n);

	if (!q->front) {
		q->front = qn;
		q->rear = qn;
	} else {
		if (dupl_open(q, n) || ance_open(n)) {
			printf("Node [%d, %d] is invalid.\n", n->x, n->y);
			//free(n);
			//free(qn);
			return;
		}
		q->rear->next = qn;
		q->rear = qn;
	}
}

struct node *
dequeue(struct queue *q)
{
	struct queue_node *qn;
	struct node *n;


	qn = q->front;
	n = qn->data;
	q->front = qn->next;
	if (!q->front) {
		q->rear = NULL;
	}
	free(qn);

	ancestors[nancestors].x = n->x;
	ancestors[nancestors].y = n->y;
	ancestors[nancestors].steps = n->steps;
	nancestors++;

	return n;
}

void
find_start(int *x, int *y)
{
	int i, j;

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if (buf[i][j] == 'S') {
				*x = i;
				*y = j;
				return;
			}
		}
	}
}

int
value_ok(char curr, char next)
{
	if (next == 'E') {
		next = 'z';
	}

	if (next <= curr + 1) {
		return 1;
	}

	return 0;
}

void
enqueue_next(struct queue *q, struct node *n)
{
	// up
	int x = n->x;
	int y = n->y;
	int steps = n->steps;
	struct node *n1, *n2, *n3, *n4;

	if (x) {
		if (value_ok(buf[x][y], buf[x - 1][y])) {
			n1 = new_node(x - 1, y, steps + 1);
			enqueue(q, n1);
		}
	}

	// right
	if (y != COLS - 1) {
		if (value_ok(buf[x][y], buf[x][y + 1])) {
			n2 = new_node(x, y + 1, steps + 1);
			enqueue(q, n2);
		}
	}

	// down
	if (x != ROWS - 1) {
		if (value_ok(buf[x][y], buf[x + 1][y])) {
			n3 = new_node(x + 1, y, steps + 1);
			enqueue(q, n3);
		}
	}

	// left
	if (y) {
		if (value_ok(buf[x][y], buf[x][y - 1])) {
			n4 = new_node(x, y - 1, steps + 1);
			enqueue(q, n4);
		}
	}
}

void
bfs(struct queue *q)
{
	struct node *curr;

	curr = dequeue(q);
	while (buf[curr->x][curr->y] != 'E') {
		printf("Current node: [%d, %d] = '%c'.\n", curr->x, curr->y, buf[curr->x][curr->y]);
		enqueue_next(q, curr);
		free(curr);
		curr = dequeue(q);
	}

	if (buf[curr->x][curr->y] == 'E') {
		printf("Steps: %d\n", curr->steps);
		return;
	}
}

int
main(void)
{
	int i, j;
	FILE *f;
	struct queue *q = calloc(1, sizeof *q);
	struct node *n;

	f = fopen("in", "r");

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			buf[i][j] = fgetc(f);
		}
		fgetc(f);
		fgetc(f);
	}

	find_start(&i, &j);
	buf[i][j] = 'a';

	n = new_node(i, j, 0);
	enqueue(q, n);

	bfs(q);

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			putchar(buf[i][j]);
		}
		puts("");
	}

	fclose(f);
	return 0;
}

