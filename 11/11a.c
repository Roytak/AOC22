#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N_MONKEYS 8
#define N_ROUNDS 20

typedef struct monkey {
	int items[256];
	int nitems;
	int (*op)(int old);
	int div_by;
	int m_true;
	int m_false;
	int inspected;
} Monkey;

int
m0(int old)
{
	return old * 7;
}

int
m1(int old)
{
	return old * 11;
}

int
m2(int old)
{
	return old + 8;
}

int
m3(int old)
{
	return old + 7;
}

int
m4(int old)
{
	return old + 5;
}

int
m5(int old)
{
	return old + 4;
}

int
m6(int old)
{
	return old * old;
}

int
m7(int old)
{
	return old + 3;
}

// void
// init(Monkey monkeys[N_MONKEYS])
// {
// 	monkeys[0].items[0] = 79;
// 	monkeys[0].items[1] = 98;
// 	monkeys[0].nitems = 2;
// 	monkeys[0].op = &m0;
// 	monkeys[0].div_by = 23;
// 	monkeys[0].m_true = 2;
// 	monkeys[0].m_false = 3;

// 	monkeys[1].items[0] = 54;
// 	monkeys[1].items[1] = 65;
// 	monkeys[1].items[2] = 75;
// 	monkeys[1].items[3] = 74;
// 	monkeys[1].nitems = 4;
// 	monkeys[1].op = &m1;
// 	monkeys[1].div_by = 19;
// 	monkeys[1].m_true = 2;
// 	monkeys[1].m_false = 0;

// 	monkeys[2].items[0] = 79;
// 	monkeys[2].items[1] = 60;
// 	monkeys[2].items[2] = 97;
// 	monkeys[2].nitems = 3;
// 	monkeys[2].op = &m2;
// 	monkeys[2].div_by = 13;
// 	monkeys[2].m_true = 1;
// 	monkeys[2].m_false = 3;

// 	monkeys[3].items[0] = 74;
// 	monkeys[3].nitems = 1;
// 	monkeys[3].op = &m3;
// 	monkeys[3].div_by = 17;
// 	monkeys[3].m_true = 0;
// 	monkeys[3].m_false = 1;
// }

void
init(Monkey monkeys[N_MONKEYS])
{
	monkeys[0].items[0] = 85;
	monkeys[0].items[1] = 77;
	monkeys[0].items[2] = 77;
	monkeys[0].nitems = 3;
	monkeys[0].op = &m0;
	monkeys[0].div_by = 19;
	monkeys[0].m_true = 6;
	monkeys[0].m_false = 7;

	monkeys[1].items[0] = 80;
	monkeys[1].items[1] = 99;
	monkeys[1].nitems = 2;
	monkeys[1].op = &m1;
	monkeys[1].div_by = 3;
	monkeys[1].m_true = 3;
	monkeys[1].m_false = 5;

	monkeys[2].items[0] = 74;
	monkeys[2].items[1] = 60;
	monkeys[2].items[2] = 74;
	monkeys[2].items[3] = 63;
	monkeys[2].items[4] = 86;
	monkeys[2].items[5] = 92;
	monkeys[2].items[6] = 80;
	monkeys[2].nitems = 7;
	monkeys[2].op = &m2;
	monkeys[2].div_by = 13;
	monkeys[2].m_true = 0;
	monkeys[2].m_false = 6;

	monkeys[3].items[0] = 71;
	monkeys[3].items[1] = 58;
	monkeys[3].items[2] = 93;
	monkeys[3].items[3] = 65;
	monkeys[3].items[4] = 80;
	monkeys[3].items[5] = 68;
	monkeys[3].items[6] = 54;
	monkeys[3].items[7] = 71;
	monkeys[3].nitems = 8;
	monkeys[3].op = &m3;
	monkeys[3].div_by = 7;
	monkeys[3].m_true = 2;
	monkeys[3].m_false = 4;

	monkeys[4].items[0] = 97;
	monkeys[4].items[1] = 56;
	monkeys[4].items[2] = 79;
	monkeys[4].items[3] = 65;
	monkeys[4].items[4] = 58;
	monkeys[4].nitems = 5;
	monkeys[4].op = &m4;
	monkeys[4].div_by = 5;
	monkeys[4].m_true = 2;
	monkeys[4].m_false = 0;

	monkeys[5].items[0] = 77;
	monkeys[5].nitems = 1;
	monkeys[5].op = &m5;
	monkeys[5].div_by = 11;
	monkeys[5].m_true = 4;
	monkeys[5].m_false = 3;

	monkeys[6].items[0] = 99;
	monkeys[6].items[1] = 90;
	monkeys[6].items[2] = 84;
	monkeys[6].items[3] = 50;
	monkeys[6].nitems = 4;
	monkeys[6].op = &m6;
	monkeys[6].div_by = 17;
	monkeys[6].m_true = 7;
	monkeys[6].m_false = 1;

	monkeys[7].items[0] = 50;
	monkeys[7].items[1] = 66;
	monkeys[7].items[2] = 61;
	monkeys[7].items[3] = 92;
	monkeys[7].items[4] = 64;
	monkeys[7].items[5] = 78;
	monkeys[7].nitems = 6;
	monkeys[7].op = &m7;
	monkeys[7].div_by = 2;
	monkeys[7].m_true = 5;
	monkeys[7].m_false = 1;
}

void
throw(Monkey monkeys[N_MONKEYS], int from, int to, int item_id)
{
	/* append */
	monkeys[to].items[monkeys[to].nitems] = monkeys[from].items[item_id];
	monkeys[to].nitems++;
}

void
do_round(Monkey monkeys[N_MONKEYS])
{
	int i, j;

	for (i = 0; i < N_MONKEYS; i++) {
		printf("Monkey %d: \n", i);
		for (j = 0; j < monkeys[i].nitems; j++) {
			/* inspect */
			printf("\tMonkey inspects an item with a worry level of %d.\n", monkeys[i].items[j]);
			monkeys[i].items[j] = monkeys[i].op(monkeys[i].items[j]);
			printf("\t\tNew worry level is %d.\n", monkeys[i].items[j]);
			monkeys[i].inspected++;
			/* bore */
			monkeys[i].items[j] /= 3;
			printf("\t\tMonkey gets bored with item. Worry level is divided by 3 to %d.\n", monkeys[i].items[j]);
			/* test */
			if (monkeys[i].items[j] % monkeys[i].div_by) {
				/* not div */
				printf("\t\tCurent worry level not divisible by %d, throwing to monkey %d.\n", monkeys[i].div_by, monkeys[i].m_false);
				throw(monkeys, i, monkeys[i].m_false, j);
			} else {
				/* div */
				printf("\t\tCurent worry level divisible by %d, throwing to monkey %d.\n", monkeys[i].div_by, monkeys[i].m_true);
				throw(monkeys, i, monkeys[i].m_true, j);
			}
			monkeys[i].items[j] = 0;
		}
		monkeys[i].nitems = 0;
	}
}

int
main(void)
{
	Monkey monkeys[N_MONKEYS] = {0};
	int i;

	init(monkeys);
	for (i = 0; i < N_ROUNDS; i++) {
		do_round(monkeys);
	}

	for (i = 0; i < N_MONKEYS; i++) {
		printf("Monkey %d inspected items %d times.\n", i, monkeys[i].inspected);
	}

	return 0;
}
