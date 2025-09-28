#include <stdio.h>
#include <stdlib.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

typedef struct {
	float coef; // 계수 (실수)
	int expon; // 차수 (양의 정수)
} polynomial;

int main(void) {
	polynomial* A = (polynomial*)malloc(10 * sizeof(polynomial));
	polynomial* B = (polynomial*)malloc(10 * sizeof(polynomial));
	polynomial* D = (polynomial*)malloc(10 * sizeof(polynomial));

	int tempCoef, tempExpon; int sizeA = 0; int sizeB = 0; int M = 0;

	while (1) {
		printf("[%d번째] A(x)의 계수와 차수를 순서대로 입력하세요. (종료는 -1 -1) : ", sizeA + 1);
		scanf("%d %d", &tempCoef, &tempExpon);
		if (sizeA > 10) realloc(A, (sizeA + 1) * sizeof(polynomial)); // 10개 초과시 메모리 재할당
		A[sizeA].coef = tempCoef;
		A[sizeA].expon = tempExpon;
		if (tempCoef == -1 && tempExpon == -1) break; // -1 -1 입력시 종료
		sizeA++;
	}

	while (1) {
		printf("[%d번째] B(x)의 계수와 차수를 순서대로 입력하세요. (종료는 -1 -1) : ", sizeB + 1);
		scanf("%d %d", &tempCoef, &tempExpon);
		if (sizeB > 10) realloc(B, (sizeB + 1) * sizeof(polynomial)); // 10개 초과시 메모리 재할당
		B[sizeB].coef = tempCoef;
		B[sizeB].expon = tempExpon;
		if (tempCoef == -1 && tempExpon == -1) break; // -1 -1 입력시 종료
		sizeB++;
	}

	M = MAX(sizeA, sizeB);
	if (M > 10) realloc(D, M * sizeof(polynomial)); // 10개 초과시 메모리 재할당

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