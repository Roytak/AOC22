#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
null_buf(char *buffer)
{
	for (int i = 0; i < strlen(buffer); i++) {
		buffer[i] = 0;
	}
}

int
main(void)
{
	char buffer[10];
	int curr_sum = 0, max1 = 0, max2 = 0, max3 = 0;
	FILE *in = fopen("in.txt", "r");
	if (!in) {
		return 1;
	}

	while (fgets(buffer, 10, in)) {
		if (buffer[0] == '\n') {
			if (curr_sum > max1) {
				if (curr_sum > max2) {
					if (curr_sum > max3) {
						max1 = max2;
						max2 = max3;
						max3 = curr_sum;
					} else {
						max1 = max2;
						max2 = curr_sum;
					}
				} else {
					max1 = curr_sum;
				}
			}
			curr_sum = 0;
		} else {
			curr_sum += atoi(buffer);
		}
		null_buf(buffer);
	}
	if (curr_sum > max1) {
				if (curr_sum > max2) {
					if (curr_sum > max3) {
						max1 = max2;
						max2 = max3;
						max3 = curr_sum;
					} else {
						max1 = max2;
						max2 = curr_sum;
					}
				} else {
					max1 = curr_sum;
				}
			}

	printf("%d\n", max1 + max2 + max3);

	return 0;
}
