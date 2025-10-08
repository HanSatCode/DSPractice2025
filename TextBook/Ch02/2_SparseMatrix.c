#include <stdio.h>
#define MAX_TERMS 101
typedef struct {
	int row;
	int col;
	int value;
} term;
term a[MAX_TERMS], b[MAX_TERMS];

void transpose(term a[], term b[]) {
	int count = a[0].value;
	b[0].row = a[0].col;
	b[0].col = a[0].row;
	b[0].value = count;

	if (count > 0) {
		int currentB = 1;
		for (int i = 0; i < a[0].col; i++) {
			for (int j = 1; j <= count; j++) {
				if (i == a[j].col) {
					b[currentB].row = a[j].col;
					b[currentB].col = a[j].row;
					b[currentB++].value = a[j].value;
				}
			}
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
	transpose(a, b);

	for(int i = 1; i <= b[0].value; i++)
		printf("%d, %d, %d\n", b[i].row, b[i].col, b[i].value);
}