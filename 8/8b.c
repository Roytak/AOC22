#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 2048

int map[MAP_SIZE][MAP_SIZE] = {0};

int
check_left(int row, int col)
{
	int val, i, score = 0;

	val = map[row][col];
	for (i = col - 1; i >= 0; i--) {
		score++;
		if (map[row][i] >= val) {
			break;
		}
	}

	return score;
}

int
check_up(int row, int col)
{
	int val, i, score = 0;

	val = map[row][col];
	for (i = row - 1; i >= 0; i--) {
		score++;
		if (map[i][col] >= val) {
			break;
		}
	}

	return score;
}

int
check_right(int row, int col, int cols)
{
	int val, i, score = 0;

	val = map[row][col];
	for (i = col + 1; i < cols; i++) {
		score++;
		if (map[row][i] >= val) {
			break;
		}
	}

	return score;
}

int
check_down(int row, int col, int rows)
{
	int val, i, score = 0;

	val = map[row][col];
	for (i = row + 1; i < rows; i++) {
		score++;
		if (map[i][col] >= val) {
			break;
		}
	}

	return score;
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
	int left_score, up_score, right_score, down_score;
	int score, max_score = 0;

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
			left_score = check_left(i, j);
			up_score = check_up(i, j);
			right_score = check_right(i, j, cols);
			down_score = check_down(i, j, rows);
			score = left_score * up_score * right_score * down_score;
			if (score > max_score) {
				max_score = score;
			}
		}
	}

	printf("part2: %d\n", max_score);

	return 0;
}
