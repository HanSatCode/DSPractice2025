#include <stdio.h>
#include <stdlib.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

int tempCoef, tempExpon; int sizeA = 0; int sizeB = 0; // ���� ����
int avail = 0;

typedef struct {
	float coef; // ��� (�Ǽ�)
	int expon; // ���� (���� ����)
} polynomial;
polynomial* result; // ���� ������ ����

void attach(float confficient, int exponent) { /* ���ο� ���� ���׽Ŀ� �߰��Ѵ�. */
	result[avail].coef = confficient;
	result[avail++].expon = exponent;
}

polynomial* padd(polynomial* A, polynomial* B) { /* A(x)�� B(x)�� ���Ͽ� �� D(x)�� ���� */
	float coefficient;
	int startA = 0, startB = 0; int finishA = sizeA - 1, finishB = sizeB - 1;

	result = (polynomial*)malloc((sizeA + sizeB) * sizeof(polynomial)); // ���� ������ ���ƺ��� A + B

	while (startA <= finishA && startB <= finishB) {
		switch (COMPARE(A[startA].expon, B[startB].expon)) {
		case -1: /* a�� ������ b�� �������� ���� ���*/
			attach(B[startB].coef, B[startB].expon);
			startB++;
			break;
		case 0: /* ������ ���� ��� */
			coefficient = A[startA].coef + B[startB].coef;
			if (coefficient) attach(coefficient, A[startA].expon); // ����� 0�� �ƴϸ�
			startA++;
			startB++;
			break;
		case 1:  /* a�� ������ b�� �������� ū ���*/
			attach(A[startA].coef, A[startA].expon);
			startA++;
		}
	}
	for (; startA <= finishA; startA++) // A(x)�� ���� �׵��� D(x)�� ÷��
		attach(A[startA].coef, A[startA].expon);
	for (; startB <= finishB; startB++) // B(x)�� ���� �׵��� D(x)�� ÷��
		attach(B[startB].coef, B[startB].expon);
	return result;
}

int main(void) {
	// ���� ��ü�� ������ ������������ ������ �� (�������� ���� ���� ���ص���)
	polynomial* A = (polynomial*)malloc(10 * sizeof(polynomial));
	polynomial* B = (polynomial*)malloc(10 * sizeof(polynomial));

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

	polynomial* D = padd(A, B);

	printf("[D(x)]\tcoef\texpon\n");
	for (int i = 0; i < avail; i++) {
		if (D[i].expon == -1) break;
		printf("\t%.2f\t%d\n", D[i].coef, D[i].expon);
	}
}