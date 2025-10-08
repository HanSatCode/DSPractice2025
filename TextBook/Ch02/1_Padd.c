#include <stdio.h>
#define MAX_TERMS 101
#define COMPARE(x, y) ( (x) < (y) ? -1 : ( (x) == (y) ? 0 : 1 ) )

typedef struct {
	int coef;
	int expon;
} polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;

void attach(int coefficient, int exponent) {
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) {
	*startD = avail;
	while (startA <= finishA && startB <= finishB) {
		switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
			case -1:
				attach(terms[startB].coef, terms[startB].expon);
				startB++; break;
			case 0:
				int coefficient = terms[startA].coef + terms[startB].coef;
				if (coefficient) attach(coefficient, terms[startA].expon);
				startA++; startB++; break;
			case 1:
				attach(terms[startA].coef, terms[startA].expon);
				startA++;
		}
	}

	for(; startA <= finishA; startA++)
		attach(terms[startA].coef, terms[startA].expon);
	for (; startB <= finishB; startB++)
		attach(terms[startB].coef, terms[startB].expon);
	
	*finishD = avail - 1;
}

int main(void) {
	int startA = 0, finishA, startB = 0, finishB, startD, finishD;
	int coef, expon, i = 0;
	while (1) {
		printf("[idx = %d] A에 넣을 지수와 계수를 내림차순으로 입력해주세요 : " , i);
		scanf("%d %d", &coef, &expon);
		if (coef == -1) {
			finishA = i - 1;
			break;
		}
		terms[i].coef = coef;
		terms[i++].expon = expon;
	}

	startB = i;
	while (1) {
		printf("[idx = %d] B에 넣을 지수와 계수를 내림차순으로 입력해주세요 : ", i);
		scanf("%d %d", &coef, &expon);
		if (coef == -1) {
			finishB = i - 1;
			break;
		}
		terms[i].coef = coef;
		terms[i++].expon = expon;
	}
	padd(startA, finishA, startB, finishB, &startD, &finishD);
	for (int i = startD; i <= finishD; i++) {
		printf("[지수] %d  [계수] %d\n", terms[i].coef, terms[i].expon);
	}
}