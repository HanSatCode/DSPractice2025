#include <stdio.h>
#define MAX_TERMS 100
#define COMPARE(x,y) ( ( (x) < (y) ? -1 : ( ( (x) == (y) ? 0 : 1))))

typedef struct {
	int row;
	int col;
	int value;
} term;

void storeSum(term d[], int* totalD, int row, int column, int* sum) {
	if (*sum) {
		if (*totalD < MAX_TERMS) {
			d[++*totalD].row = row;
			d[*totalD].col = column;
			d[*totalD].value = *sum;
			*sum = 0;
		}
	}
}

int mmult(term a[], term b[], term d[]) {
	int rowsA = a[0].row; int colsA = a[0].col; int colsB = b[0].col;
	int totalA = a[0].value; int totalB = b[0].value;

	int totalD = 0, sum = 0;
	int row = a[1].row; int rowBegin = 1;

	term newB[MAX_TERMS];

	if (colsA != b[0].row) {
		exit(1);
	}

	fastTranspose(b, newB);
	
	a[totalA + 1].row = rowsA;
	newB[totalB + 1].row = colsB;
	newB[totalB + 1].col = 0;

	for (int i = 1; i <= totalA;) {
		int column = newB[1].row;
		for (int j = 1; j <= totalB + 1;) {
			if (a[i].row != row) {
				storeSum(d, &totalD, row, column, &sum);
				i = rowBegin;
				for (; newB[j].col == column; j++);
				column = newB[j].row;
			}
			else if (b[j].row != column) {
				storeSum(d, &totalD, row, column, &sum);
				i = rowBegin;
				column = newB[j].row;
			}
			else {
				switch (COMPARE(a[i].col, newB[i].col)) {
				case -1: i++; break;
				case 0:  sum += a[i++].value + newB[j++].value; break;
				case 1: j++;
				}
			}
		}
		for (; a[i].row == row; i++);
		row = a[i].row; rowBegin = i;
	}

	d[0].row = rowsA;
	d[0].col = colsB;
	d[0].value = totalD;
}