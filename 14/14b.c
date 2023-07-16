#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum bg {
	AIR = 0,
	SAND = 1,
	STONE = 2
};

void
parse_line(char *buf, int *max, int **array)
{
	int oldx, oldy, newx, newy;
	int swap = 0;
	char *token = NULL;
	int i;

	token = strtok(buf, "->");
	while (token) {
		if (token[0] == ' ') {
			token++;
		}

		if (!swap) {
			sscanf(token, "%d,%d", &oldx, &oldy);
			if (oldy > *max) {
				*max = oldy;
			}

			swap = 1;
			token = strtok(NULL, "->");
			continue;
		}

		sscanf(token, "%d,%d", &newx, &newy);

		if (newy > *max) {
			*max = newy;
		}

		if (oldx == newx) {
			// moving y
			if (oldy > newy) {
				for (i = newy; i <= oldy; i++) {
					array[i][oldx] = STONE;
				}
			} else {
				for (i = oldy; i <= newy; i++) {
					array[i][oldx] = STONE;
				}
			}
		} else {
			if (oldx > newx) {
				for (i = newx; i <= oldx; i++) {
					array[oldy][i] = STONE;
				}
			} else {
				for (i = oldx; i <= newx; i++) {
					array[oldy][i] = STONE;
				}
			}
		}

		oldx = newx;
		oldy = newy;

		token = strtok(NULL, "->");
	}
}

int
drop_sand(int **array)
{
	int currx = 500, curry = 0;

	while (1) {
		if (array[1][499] == SAND && array[1][500] == SAND && array[1][501] == SAND ) {
			return 1;
		}

		if (array[curry + 1][currx] == AIR) {
			curry++;
		} else if (array[curry + 1][currx - 1] == AIR) {
			curry++;
			currx--;
		} else if (array[curry + 1][currx + 1] == AIR) {
			curry++;
			currx++;
		} else {
			array[curry][currx] = SAND;
			return 0;
		}
	}
}

int
main(void)
{
	FILE *f;
	char *buffer = NULL;
	size_t s;
	int i;
	int max = 0, sand = 0;
	int **array;

	f = fopen("in", "r");

	array = malloc(5000 * sizeof *array);
	for (i = 0; i < 5000; i++) {
		array[i] = malloc(5000 * sizeof **array);
	}

	while (getline(&buffer, &s, f) != -1) {
		parse_line(buffer, &max, array);
		free(buffer);
		buffer = NULL;
	}

	for (i = 0; i < 5000; i++) {
		array[max + 2][i] = STONE;
	}

	while (!drop_sand(array)) {
		sand++;
	}

	printf("Sand: %d\n", sand + 1);

	fclose(f);
	free(array);
	return 0;
}
