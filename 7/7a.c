#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256
#define MAX_FILE_SIZE 100000

struct file {
	char *name;
	int size;
};

struct directory {
	char *name;

	struct directory *parent_dir;

	struct directory *sub_directories;
	int sub_directory_cnt;

	struct file *files;
	int file_cnt;
};

void
null_buf(char buffer[BUFSIZE])
{
	int i;

	for (i = 0; i < BUFSIZE; i++) {
		buffer[i] = 0;
	}
}

struct directory *
decode_input(char buffer[BUFSIZE], struct directory *current)
{
	char *new_dir;
	char file_name[256] = {0};
	int file_size = 0;
	int i;

	if (buffer[0] == '$') {
		if (buffer[2] == 'c') {
			/* cd */
			new_dir = buffer + 5;
			//printf("%s\n", new_dir);
			if (!strcmp(new_dir, "..")) {
				current = current->parent_dir;
			} else if (!strcmp(new_dir, "/")) {
				while (strcmp(current->name, new_dir)) {
					current = current->parent_dir;
				}
			} else {
				for (i = 0; i < current->sub_directory_cnt; i++) {
					if (!strcmp(new_dir, current->sub_directories[i].name)) {
						current = &current->sub_directories[i];
						break;
					}
				}
			}
		}
	} else if (buffer[0] == 'd') {
		/* dir */
		//printf("%s\n", buffer + 4);
		current->sub_directories = realloc(current->sub_directories, (current->sub_directory_cnt + 1) * sizeof *current->sub_directories);
		memset(&current->sub_directories[current->sub_directory_cnt], 0, sizeof *current->sub_directories);
		current->sub_directories[current->sub_directory_cnt].name = strdup(buffer + 4);
		current->sub_directories[current->sub_directory_cnt].parent_dir = current;
		current->sub_directory_cnt++;
	} else {
		/* file */
		current->files = realloc(current->files, (current->file_cnt + 1) * sizeof *current->files);
		memset(&current->files[current->file_cnt], 0, sizeof *current->files);
		sscanf(buffer, "%d %s", &file_size, file_name);
		current->files[current->file_cnt].name = strdup(file_name);
		current->files[current->file_cnt].size = file_size;
		current->file_cnt++;
	}

	return current;
}

int
compute_sum(struct directory *current, int *final)
{
	int sum = 0, i, j, sub_dir_sum = 0;

	if (!current) {
		return 0;
	}

	for (i = 0; i < current->sub_directory_cnt; i++) {
		sub_dir_sum += compute_sum(&current->sub_directories[i], final);
		//printf("subd %s size %d\n", current->sub_directories[i].name, dir_sum);
	}

	//printf("subd %s size %d\n", current->name, sub_dir_sum);

	for (j = 0; j < current->file_cnt; j++) {
		sum += current->files[j].size;
	}

	if (sum + sub_dir_sum < MAX_FILE_SIZE) {
		*final += sum + sub_dir_sum;
	}
	//printf("curr %s sum %d\n", current->name, sum+sub_dir_sum);

	return sum;
}

int
main(void)
{
	FILE *f = fopen("in.txt", "r");
	if (!f) {
		return 1;
	}

	char buffer[BUFSIZE];
	int sum = 0;
	struct directory *current;
	struct directory *home = calloc(1, sizeof *home);
	if (!home) {
		return 1;
	}
	home->name = strdup("/");

	current = home;
	while (fgets(buffer, BUFSIZE, f) != NULL) {
		if (buffer[strlen(buffer) - 1] == '\n') {
			buffer[strlen(buffer) - 2] = 0;
		}
		//printf("%s\n", buffer);
		current = decode_input(buffer, current);
		null_buf(buffer);
	}

	compute_sum(home, &sum);
	printf("%d\n", sum);

	return 0;
}
