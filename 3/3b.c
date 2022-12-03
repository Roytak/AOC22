#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char already_checked[500] = {0};

int
check_checked(char c)
{
	int i;

	for (i = 0; i < 500; i++) {
		if (c == already_checked[i]) {
			return 1;
		}
	}

	return 0;
}

void
null_checked()
{
	int i;

	for (i = 0; i < 500; i++) {
		already_checked[i] = 0;
	}
}

void
add_checked(char c)
{
	int i;

	for (i = 0; already_checked[i]; i++);
	already_checked[i] = c;
}

int
part2(char *first, char *second, char *third)
{
	size_t i, j, k;
	int sum = 0;

	for (i = 0; i < strlen(first); i++) {
		for (j = 0; j < strlen(second); j++) {
			if (first[i] == second[j]) {
					for (k = 0; k < strlen(third); k++) {
						if (second[j] == third[k]) {
							if (check_checked(first[i])) {
								break;
							}
							add_checked(first[i]);
							if (first[i] >= 'a') {
								sum += first[i] - 'a' + 1;
							} else {
								sum += first[i] - 'A' + 27;
							}
						}
					}
			}
		}
	}

	return sum;
}

int
main(void)
{
	FILE *f = fopen("in.txt", "r");
	if (!f) {
		return 1;
	}

	char *buffer[300];
	int id = 0;
	size_t n = 0;
	ssize_t nchr = 0;
	int sum = 0;

	char *ptr = NULL;
	while ((nchr = getline(&ptr, &n, f)) != -1) {
		while (nchr > 0 && (ptr[nchr-1] == '\n' || ptr[nchr-1] == '\r')){
            ptr[--nchr] = 0;
		}

		buffer[id++] = strdup(ptr);
	}

	id = 0;
	while (buffer[id]) {
		if (id % 3 == 2) {
			sum += part2(buffer[id - 2], buffer[id - 1], buffer[id]);
			null_checked();
		}
		id++;
	}

	printf("%d\n", sum);
	return 0;
}
