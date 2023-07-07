#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int X = 1;
int cycle = 1;
int sum;

void
add_cycle(int n)
{
	if ((cycle == 20) || (cycle == 60) || (cycle == 100) || (cycle == 140) || (cycle == 180) || (cycle == 220)) {
		sum += cycle * X;
		printf("Cycle: %d new: %d sum: %d\n", cycle, cycle * X, sum);
	}

	X += n;
	cycle++;
	//printf("X: %d\n", X);
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
