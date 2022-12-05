#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define STACK_COUNT 9

struct stack {
    char array[MAX_STACK_SIZE];
    int top;
};

void
stack_init(struct stack *stack)
{
    int i;

    stack->top = -1;
    for (i = 0; i < MAX_STACK_SIZE; i++) {
        stack->array[i] = 0;
    }
}

int
stack_is_full(struct stack stack)
{
  if (stack.top == (MAX_STACK_SIZE - 1)) {
    return 1;
  }

  return 0;
}

int
stack_is_empty(struct stack stack)
{
  if (stack.top == -1) {
    return 1;
  }

  return 0;
}

int
stack_push(struct stack *stack, char c)
{
    if (stack_is_full(*stack)) {
        return 1;
    }

    stack->top++;
    stack->array[stack->top] = c;
    return 0;
}

void
stack_pop(struct stack *stack)
{
    stack->top--;
}

char
stack_top(struct stack stack)
{
    if (stack_is_empty(stack)) {
        return -1;
    }

    return stack.array[stack.top];
}

int
push_init_values(struct stack stacks[STACK_COUNT])
{
    if (stack_push(&stacks[0], 'S')) {
        return 1;
    }
    if (stack_push(&stacks[0], 'Z')) {
        return 1;
    }
    if (stack_push(&stacks[0], 'P')) {
        return 1;
    }
    if (stack_push(&stacks[0], 'D')) {
        return 1;
    }
    if (stack_push(&stacks[0], 'L')) {
        return 1;
    }
    if (stack_push(&stacks[0], 'B')) {
        return 1;
    }
    if (stack_push(&stacks[0], 'F')) {
        return 1;
    }
    if (stack_push(&stacks[0], 'C')) {
        return 1;
    }
    if (stack_push(&stacks[1], 'N')) {
        return 1;
    }
    if (stack_push(&stacks[1], 'V')) {
        return 1;
    }
    if (stack_push(&stacks[1], 'G')) {
        return 1;
    }
    if (stack_push(&stacks[1], 'P')) {
        return 1;
    }
    if (stack_push(&stacks[1], 'H')) {
        return 1;
    }
    if (stack_push(&stacks[1], 'W')) {
        return 1;
    }
    if (stack_push(&stacks[1], 'B')) {
        return 1;
    }
    if (stack_push(&stacks[2], 'F')) {
        return 1;
    }
    if (stack_push(&stacks[2], 'W')) {
        return 1;
    }
    if (stack_push(&stacks[2], 'B')) {
        return 1;
    }
    if (stack_push(&stacks[2], 'J')) {
        return 1;
    }
    if (stack_push(&stacks[2], 'G')) {
        return 1;
    }
    if (stack_push(&stacks[3], 'G')) {
        return 1;
    }
    if (stack_push(&stacks[3], 'J')) {
        return 1;
    }
    if (stack_push(&stacks[3], 'N')) {
        return 1;
    }
    if (stack_push(&stacks[3], 'F')) {
        return 1;
    }
    if (stack_push(&stacks[3], 'L')) {
        return 1;
    }
    if (stack_push(&stacks[3], 'W')) {
        return 1;
    }
    if (stack_push(&stacks[3], 'C')) {
        return 1;
    }
    if (stack_push(&stacks[3], 'S')) {
        return 1;
    }
    if (stack_push(&stacks[4], 'W')) {
        return 1;
    }
    if (stack_push(&stacks[4], 'J')) {
        return 1;
    }
    if (stack_push(&stacks[4], 'L')) {
        return 1;
    }
    if (stack_push(&stacks[4], 'T')) {
        return 1;
    }
    if (stack_push(&stacks[4], 'P')) {
        return 1;
    }
    if (stack_push(&stacks[4], 'M')) {
        return 1;
    }
    if (stack_push(&stacks[4], 'S')) {
        return 1;
    }
    if (stack_push(&stacks[4], 'H')) {
        return 1;
    }
    if (stack_push(&stacks[5], 'B')) {
        return 1;
    }
    if (stack_push(&stacks[5], 'C')) {
        return 1;
    }
    if (stack_push(&stacks[5], 'W')) {
        return 1;
    }
    if (stack_push(&stacks[5], 'G')) {
        return 1;
    }
    if (stack_push(&stacks[5], 'F')) {
        return 1;
    }
    if (stack_push(&stacks[5], 'S')) {
        return 1;
    }
    if (stack_push(&stacks[6], 'H')) {
        return 1;
    }
    if (stack_push(&stacks[6], 'T')) {
        return 1;
    }
    if (stack_push(&stacks[6], 'P')) {
        return 1;
    }
    if (stack_push(&stacks[6], 'M')) {
        return 1;
    }
    if (stack_push(&stacks[6], 'Q')) {
        return 1;
    }
    if (stack_push(&stacks[6], 'B')) {
        return 1;
    }
    if (stack_push(&stacks[6], 'W')) {
        return 1;
    }
    if (stack_push(&stacks[7], 'F')) {
        return 1;
    }
    if (stack_push(&stacks[7], 'S')) {
        return 1;
    }
    if (stack_push(&stacks[7], 'W')) {
        return 1;
    }
    if (stack_push(&stacks[7], 'T')) {
        return 1;
    }
    if (stack_push(&stacks[8], 'N')) {
        return 1;
    }
    if (stack_push(&stacks[8], 'C')) {
        return 1;
    }
    if (stack_push(&stacks[8], 'R')) {
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

    int i, j;
    int move = 0, from = 0, to = 0;
    char moved, printed;
    char moved_buffer[100] = {0};

    struct stack stacks[STACK_COUNT];
    for (i = 0; i < STACK_COUNT; i++) {
        stack_init(&stacks[i]);
    }

    /* insert init values, cba parsing it */
    if (push_init_values(stacks)) {
        return 1;
    }

    while (fscanf(f, "move %d from %d to %d\n", &move, &from, &to) != EOF) {
        if (move == 1) {
            moved = stack_top(stacks[from - 1]);
            if (moved == -1) {
                return 1;
            }
            stack_pop(&stacks[from - 1]);

            if (stack_push(&stacks[to - 1], moved)) {
                return 1;
            }

            continue;
        }

        for (i = 0; i < move; i++) {
            moved = stack_top(stacks[from - 1]);
            if (moved == -1) {
                return 1;
            }
            stack_pop(&stacks[from - 1]);

            moved_buffer[i] = moved;
        }
        for (j = i - 1; j >= 0; j--) {
            if (stack_push(&stacks[to - 1], moved_buffer[j])) {
                return 1;
            }
        }
    }

    for (i = 0; i < STACK_COUNT; i++) {
        printed = stack_top(stacks[i]);
        if (printed != -1) {
            printf("%c", printed);
        }
    }
    printf("\n");

    return 0;
}
