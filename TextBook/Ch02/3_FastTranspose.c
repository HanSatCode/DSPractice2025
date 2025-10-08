#include <stdio.h>
#define MAX_COL 50
#define MAX_TERMS 101
typedef struct {
	int row;
	int col;
	int value;
} term;
term a[MAX_TERMS], b[MAX_TERMS];

void fastTranspose(term a[], term b[]) {
	int rowTerms[MAX_COL];
	int startingPos[MAX_COL];
	int numCols = a[0].col; int numTerms = a[0].value;

	b[0].row = numCols;
	b[0].col = a[0].row;
	b[0].value = numTerms;

	if (numTerms > 0) {
		for (int i = 0; i < numCols; i++) {
			rowTerms[i] = 0;
		}

		for (int i = 1; i <= numTerms; i++) {
			rowTerms[a[i].col]++;
		}

		startingPos[0] = 1;
		for (int i = 1; i < numCols; i++) {
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		}

		for (int i = 1; i <= numTerms; i++) {
			int j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

int main(void) {
	int row, col, value;
	printf("행렬의 행, 열, 0이 아닌 항의 개수를 입력하세요 : ");
	scanf("%d %d %d", &row, &col, &value);
	a[0].row = row; a[0].col = col; a[0].value = value;

	for (int i = 1; i <= a[0].value; i++) {
		printf("[%d번째] 행, 열, 값을 입력하세요 : ", i);
		scanf("%d %d %d", &row, &col, &value);
		a[i].row = row; a[i].col = col; a[i].value = value;
	}
	fastTranspose(a, b);

	for (int i = 1; i <= b[0].value; i++)
		printf("%d, %d, %d\n", b[i].row, b[i].col, b[i].value);
}