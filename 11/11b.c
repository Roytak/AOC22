#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N_MONKEYS 8
#define N_ROUNDS 10000
//#define LCM 19 * 3 * 13 * 7 * 5 * 11 * 17 * 2
#define LCM 9699690

typedef struct monkey {
	unsigned long long items[512];
	int nitems;
	unsigned long long (*op)(unsigned long long old);
	int div_by;
	int m_true;
	int m_false;
	unsigned long long inspected;
} Monkey;

unsigned long long
m0(unsigned long long old)
{
	return old * 7;
}

unsigned long long
m1(unsigned long long old)
{
	return old * 11;
}

unsigned long long
m2(unsigned long long old)
{
	return old + 8;
}

unsigned long long
m3(unsigned long long old)
{
	return old + 7;
}

unsigned long long
m4(unsigned long long old)
{
	return old + 5;
}

unsigned long long
m5(unsigned long long old)
{
	return old + 4;
}

unsigned long long
m6(unsigned long long old)
{
	return old * old;
}

unsigned long long
m7(unsigned long long old)
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
			printf("\tMonkey inspects an item with a worry level of %llu.\n", monkeys[i].items[j]);
			monkeys[i].items[j] = monkeys[i].op(monkeys[i].items[j]);
			if (monkeys[i].items[j] > LCM) {
				monkeys[i].items[j] = monkeys[i].items[j] % LCM;
			}
			printf("\t\tNew worry level is %llu.\n", monkeys[i].items[j]);
			monkeys[i].inspected++;
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

void
monkey_bussiness(Monkey monkeys[N_MONKEYS])
{
	int i;
	unsigned long long max1 = 0, max2 = 0;

	for (i = 0; i < N_MONKEYS; i++) {
		if (monkeys[i].inspected > max1) {
			max1 = monkeys[i].inspected;
		}
	}

	for (i = 0; i < N_MONKEYS; i++) {
		if ((monkeys[i].inspected > max2) && (monkeys[i].inspected != max1)) {
			max2 = monkeys[i].inspected;
		}
	}

	printf("Max inspected values are: %llu and %llu, making the monkey bussiness value of: %llu\n", max1, max2, max1*max2);
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
		printf("Monkey %d inspected items %llu times.\n", i, monkeys[i].inspected);
	}

	monkey_bussiness(monkeys);

	return 0;
}
