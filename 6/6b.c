#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PACKET_START 14

int
cmp(const void *f, const void *s)
{
	if (*(char *)f < *(char *)s) {
		return -1;
	} else if (*(char *)f > *(char *)s) {
		return 1;
	} else {
		return 0;
	}
}

int
main(void)
{
	FILE *f = fopen("in.txt", "r");
	if (!f) {
		return 1;
	}

	char buffer[4096] = {0};
	char *current;
	size_t read = 0;
	int i;
	fscanf(f, "%s", buffer);

	while (strlen(buffer) > read + NUM_PACKET_START) {
		current = strndup(buffer + read, NUM_PACKET_START);
		qsort(current, NUM_PACKET_START, sizeof(char), cmp);
		for (i = 0; i < NUM_PACKET_START; i++) {
			if (current[i] == current[i+1]) {
				break;
			}
		}
		if (i == NUM_PACKET_START) {
			break;
		}
		read++;
		free(current);
	}
	printf("%zu\n", read + NUM_PACKET_START);

	return 0;
}
