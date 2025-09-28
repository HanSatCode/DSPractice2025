#include <stdio.h>
#include <stdlib.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

typedef struct {
	float coef; // ��� (�Ǽ�)
	int expon; // ���� (���� ����)
} polynomial;

int main(void) {
	polynomial* A = (polynomial*)malloc(10 * sizeof(polynomial));
	polynomial* B = (polynomial*)malloc(10 * sizeof(polynomial));
	polynomial* D = (polynomial*)malloc(10 * sizeof(polynomial));

	int tempCoef, tempExpon; int sizeA = 0; int sizeB = 0; int M = 0;

	while (1) {
		printf("[%d��°] A(x)�� ����� ������ ������� �Է��ϼ���. (����� -1 -1) : ", sizeA + 1);
		scanf("%d %d", &tempCoef, &tempExpon);
		if (sizeA > 10) realloc(A, (sizeA + 1) * sizeof(polynomial)); // 10�� �ʰ��� �޸� ���Ҵ�
		A[sizeA].coef = tempCoef;
		A[sizeA].expon = tempExpon;
		if (tempCoef == -1 && tempExpon == -1) break; // -1 -1 �Է½� ����
		sizeA++;
	}

	while (1) {
		printf("[%d��°] B(x)�� ����� ������ ������� �Է��ϼ���. (����� -1 -1) : ", sizeB + 1);
		scanf("%d %d", &tempCoef, &tempExpon);
		if (sizeB > 10) realloc(B, (sizeB + 1) * sizeof(polynomial)); // 10�� �ʰ��� �޸� ���Ҵ�
		B[sizeB].coef = tempCoef;
		B[sizeB].expon = tempExpon;
		if (tempCoef == -1 && tempExpon == -1) break; // -1 -1 �Է½� ����
		sizeB++;
	}

	M = MAX(sizeA, sizeB);
	if (M > 10) realloc(D, M * sizeof(polynomial)); // 10�� �ʰ��� �޸� ���Ҵ�

	printf("[A(x)]\tcoef\texpon\n");
	for (int i = 0; i < 10; i++) {
		if (A[i].expon == -1) break;
		printf("\t%.2f\t%d\n", A[i].coef, A[i].expon);
	}

	printf("[B(x)]\tcoef\texpon\n");
	for (int i = 0; i < 10; i++) {
		if (B[i].expon == -1) break;
		printf("\t%.2f\t%d\n", B[i].coef, B[i].expon);
	}
}