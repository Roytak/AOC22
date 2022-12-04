#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
check_overlap(int fl, int fh, int sl, int sh)
{
	if ((fh >= sl) && (fl <= sh)) {
		return 1;
	}

	return 0;
}

int
main(void)
{
	FILE *f = fopen("in.txt", "r");
	if (!f) {
		return 1;
	}

	int first_low = 0, first_high = 0, second_low = 0, second_high = 0;
	int overlaps = 0;

	while (fscanf(f, "%d-%d,%d-%d\n", &first_low, &first_high, &second_low, &second_high) != EOF) {
		overlaps += check_overlap(first_low, first_high, second_low, second_high);
	}

	printf("%d\n", overlaps);

	return 0;
}
