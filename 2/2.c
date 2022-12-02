#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	A - rock, B- paper, C- scissor,
	X - rock 1, Y- paper 2, Z- scissors 3,
	lost - 0, draw - 3, win - 6
*/

int
decode1(char oponent, char me)
{
	switch(oponent) {
	case 'A': {
		switch(me) {
		case 'Y': {
			return 8;
		}
		case 'X': {
			return 4;
		}
		case 'Z': {
			return 3;
		}
		default:
			break;
		}
	}
	case 'B': {
		switch(me) {
		case 'Y': {
			return 5;
		}
		case 'X': {
			return 1;
		}
		case 'Z': {
			return 9;
		}
		default:
			break;
		}
	}
	case 'C': {
		switch(me) {
		case 'Y': {
			return 2;
		}
		case 'X': {
			return 7;
		}
		case 'Z': {
			return 6;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
	return -1;
}

int
decode2(char oponent, char me)
{
	switch(oponent) {
	case 'A': {
		switch(me) {
		case 'Y': {
			return 4;
		}
		case 'X': {
			return 3;
		}
		case 'Z': {
			return 8;
		}
		default:
			break;
		}
	}
	case 'B': {
		switch(me) {
		case 'Y': {
			return 5;
		}
		case 'X': {
			return 1;
		}
		case 'Z': {
			return 9;
		}
		default:
			break;
		}
	}
	case 'C': {
		switch(me) {
		case 'Y': {
			return 6;
		}
		case 'X': {
			return 2;
		}
		case 'Z': {
			return 7;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
	return -1;
}

int
main(void)
{
	FILE *f = fopen("in.txt", "r");
	if (!f) {
		return 1;
	}

	char oponent = 0, me = 0;
	int score1 = 0, score2 = 0;
	while (fscanf(f, "%c %c\n", &oponent, &me) != EOF) {
		score1 += decode1(oponent, me);
		score2 += decode2(oponent, me);
	}
	printf("%d\n", score1);
	printf("%d\n", score2);

	return 0;
}
