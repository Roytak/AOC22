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

	struct directory *parent;
	struct directory *child;
	struct directory *next;

	unsigned long file_size;
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
create_direcory(char *dir_name, struct directory *parent)
{
	struct directory *dir;

	dir = calloc(1, sizeof *dir);
	if (dir) {
		dir->name = strdup(dir_name);
		dir->parent = parent;
	}
	return dir;
}

struct directory *
decode_input(char buffer[BUFSIZE], struct directory *current)
{
	char *new_dir;
	int file_size = 0;
	struct directory *iter = NULL;
	struct directory *new = NULL;

	if (buffer[0] == '$') {
		if (buffer[2] == 'c') {
			/* cd */
			new_dir = buffer + 5;
			//printf("%s\n", new_dir);
			if (!strcmp(new_dir, "..")) {
				current = current->parent;
			} else if (!strcmp(new_dir, "/")) {
				while (strcmp(current->name, new_dir)) {
					current = current->parent;
				}
			} else {
				current = current->child;
				while (strcmp(new_dir, current->name)) {
					current = current->next;
				}
			}
		}
	} else if (buffer[0] == 'd') {
		/* dir */
		new = create_direcory(buffer + 4, current);
		if (!current->child) {
			current->child = new;
		} else {
			iter = current->child;
			while (iter->next) {
				iter = iter->next;
			}
			iter->next = new;
		}
	} else {
		/* file */
		sscanf(buffer, "%d", &file_size);
		current->file_size += file_size;
	}

	//printf("name: %s fsize %ld\n", current->name, current->file_size);
	return current;
}

unsigned long long
tree_sum(struct directory *tree, unsigned long long *final_sum)
{
	unsigned long long sum = 0;

	if (!tree) {
		return 0;
	}

	sum += tree_sum(tree->child, final_sum);

	sum += tree->file_size;

	if (sum < MAX_FILE_SIZE) {
		*final_sum += sum;
	}

	sum += tree_sum(tree->next, final_sum);

	printf("current %s sum %llu\n", tree->name, *final_sum);

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
	unsigned long long sum = 0;
	struct directory *current;
	struct directory *home = create_direcory("/", NULL);
	if (!home) {
		return 1;
	}

	current = home;
	while (fgets(buffer, BUFSIZE, f) != NULL) {
		if (buffer[strlen(buffer) - 1] == '\n') {
			buffer[strlen(buffer) - 2] = 0;
		}
		//printf("%s\n", buffer);
		current = decode_input(buffer, current);
		null_buf(buffer);
	}

	//compute_sum(home, &sum);
	tree_sum(home, &sum);
	printf("%llu\n", sum);

	return 0;
}
