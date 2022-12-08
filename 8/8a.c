#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 2048

int map[MAP_SIZE][MAP_SIZE] = {0};

int
check_left(int row, int col)
{
	int val, i;

	val = map[row][col];
	for (i = 0; i < col; i++) {
		if (map[row][i] >= val) {
			return 0;
		}
	}

	return 1;
}

int
check_up(int row, int col)
{
	int val, i;

	val = map[row][col];
	for (i = 0; i < row; i++) {
		if (map[i][col] >= val) {
			return 0;
		}
	}

	return 1;
}

int
check_right(int row, int col, int cols)
{
	int val, i;

	val = map[row][col];
	for (i = cols - 1; i > col; i--) {
		if (map[row][i] >= val) {
			return 0;
		}
	}

	return 1;
}

int
check_down(int row, int col, int rows)
{
	int val, i;

	val = map[row][col];
	for (i = rows - 1; i > row; i--) {
		if (map[i][col] >= val) {
			return 0;
		}
	}

	return 1;
}

int
main(void)
{
	FILE *f = fopen("in.txt", "r");
	if (!f) {
		return 1;
	}

	int i, j;
	int c;
	char buf[2] = {0};
	int rows, cols;
	int ret = 0;

	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			c = fgetc(f);
			if (c == EOF) {
				break;
			} else if (c == '\n') {
				break;
			}
			buf[0] = c;
			map[i][j] = atoi(buf);
		}
		if (c == EOF) {
			break;
		}
	}

	rows = i + 1;
	cols = j;

	for (i = 1; i < rows - 1; i++) {
		for (j = 1; j < cols - 1; j++) {
			if (check_left(i, j) || check_up(i, j) || check_right(i, j, cols) || check_down(i, j, rows)) {
				ret++;
			}
		}
	}

	printf("part1: %d\n", ret + 4*rows - 4);

	return 0;
}
