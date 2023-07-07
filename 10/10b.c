#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int X = 1;
int cycle = 1;
int pixel = 0;
int sum;

void
add_cycle(int n)
{
	if ((pixel == X - 1) || (pixel == X) || (pixel == X + 1)) {
		printf("#");
	} else {
		printf(".");
	}

	if ((cycle == 40) || (cycle == 80) || (cycle == 120) || (cycle == 160) || (cycle == 200) || (cycle == 240)) {
		printf("\n");
		pixel = 0;
	} else {
		pixel++;
	}

	X += n;
	cycle++;
}

int
main(void)
{
	char buffer[256] = {0};
	int n;

	while (fgets(buffer, 256, stdin)) {
		if (!strncmp(buffer, "noop", 4)) {
			add_cycle(0);
		} else {
			sscanf(buffer, "addx %d", &n);
			add_cycle(0);
			add_cycle(n);
		}
		memset(buffer, 0, 256);
	}

	return 0;
}
