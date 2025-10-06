#include <stdio.h>
#include <stdlib.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

int tempCoef, tempExpon; int sizeA = 0; int sizeB = 0; // ���� ����
int resultAvail = 0; int tempAvail = 0; int mulCnt = 0;

typedef struct {
	float coef; // ��� (�Ǽ�)
	int expon; // ���� (���� ����)
} polynomial;
polynomial* result; // ���� ������ ���� (������ ��)
polynomial* temp; // ���� ������ ���� (�ӽ� �����)

void attach(float confficient, int exponent) { /* ���ο� ���� ���׽Ŀ� �߰��Ѵ�. */
	temp[tempAvail].coef = confficient;
	temp[tempAvail++].expon = exponent;
	resultAvail++;
}

polynomial* padd(polynomial* A, polynomial* B) { /* A(x)�� B(x)�� ���Ͽ� �� D(x)�� ���� */
	float coefficient;
	int startA = 0, startB = 0; int finishA = resultAvail - 1, finishB = sizeB - 1;

	temp = (polynomial*)malloc((sizeA + sizeB) * sizeof(polynomial));
	tempAvail = 0; resultAvail = 0;

	while (startA <= finishA && startB <= finishB) {
		switch (COMPARE(A[startA].expon, B[startB].expon)) {
		case -1: /* a�� ������ b�� �������� ���� ���*/
			attach(B[startB].coef, B[startB].expon);
			startB++;
			break;
		case 0: /* ������ ���� ��� */
			coefficient = A[startA].coef + B[startB].coef;
			if (coefficient) attach(coefficient, A[startA].expon); // ����� 0�� �ƴϸ�
			startA++; startB++;
			break;
		case 1:  /* a�� ������ b�� �������� ū ��� */
			attach(A[startA].coef, A[startA].expon);
			startA++;
		}
	}
	
	for (; startA <= finishA; startA++) {
		attach(A[startA].coef, A[startA].expon);
	}
	for (; startB <= finishB; startB++) { // B(x)�� ���� �׵��� D(x)�� ÷��
		attach(B[startB].coef, B[startB].expon);
	}

	return temp;
}

polynomial* single_mul(polynomial* A, polynomial Bi) {
	/* A(x)�� B(x)�� ���Ͽ� �� Ci(x)�� ����. Bi�� ������ !!! */
	float confficient; int exponent;
	int startA = 0, startB = 0, finishB = sizeB - 1;
	polynomial* singleTemp = (polynomial*)malloc(sizeB * sizeof(polynomial));
	
	printf("[C%d(x)]\tcoef\texpon\n", ++mulCnt);
	for (; startB <= finishB; startB++) {
		singleTemp[startB].coef = A[startB].coef * Bi.coef;
		singleTemp[startB].expon = A[startB].expon + Bi.expon;
		printf("\t%.2f\t%d\n", singleTemp[startB].coef, singleTemp[startB].expon);
	}

	return singleTemp;
}

polynomial* pmul(polynomial* A, polynomial* B) {
	if (result == NULL) result = (polynomial*)malloc((sizeA * sizeB) * sizeof(polynomial));

	for (int i = 0; i < sizeA; i++) {
		polynomial* Ci = single_mul(B, A[i]); // A�� �������� ���ؾ� ��
		result = padd(result, Ci); // ���ϱ�
	}
	return result;
}

int main(void) {
	// ���� ��ü�� ������ ������������ ������ �� (�������� ���� ���� ���ص���)
	polynomial* A = (polynomial*)malloc(10 * sizeof(polynomial));
	polynomial* B = (polynomial*)malloc(10 * sizeof(polynomial));

	while (1) {
		printf("[%d��°] A(x)�� ����� ������ ������� �Է��ϼ���. (����� -1 -1) : ", sizeA + 1); scanf("%d %d", &tempCoef, &tempExpon);
		if (sizeA > 10) realloc(A, (sizeA + 1) * sizeof(polynomial));	// 10�� �ʰ��� �޸� ���Ҵ�
		A[sizeA].coef = tempCoef; A[sizeA].expon = tempExpon;
		if (tempCoef == -1 && tempExpon == -1) break; // -1 -1 �Է½� ����
		sizeA++;
	}

	printf("[A(x)]\tcoef\texpon\n");
	for (int i = 0; i < sizeA; i++) {
		if (A[i].expon == -1) break;
		printf("\t%.2f\t%d\n", A[i].coef, A[i].expon);
	}

	while (1) {
		printf("[%d��°] B(x)�� ����� ������ ������� �Է��ϼ���. (����� -1 -1) : ", sizeB + 1); scanf("%d %d", &tempCoef, &tempExpon);
		if (sizeB > 10) realloc(B, (sizeB + 1) * sizeof(polynomial));	// 10�� �ʰ��� �޸� ���Ҵ�
		B[sizeB].coef = tempCoef; B[sizeB].expon = tempExpon;
		if (tempCoef == -1 && tempExpon == -1) break; // -1 -1 �Է½� ����
		sizeB++;
	}

	printf("[B(x)]\tcoef\texpon\n");
	for (int i = 0; i < sizeB; i++) {
		if (B[i].expon == -1) break;
		printf("\t%.2f\t%d\n", B[i].coef, B[i].expon);
	}

	polynomial* D = pmul(A, B);

	printf("[D(x)]\tcoef\texpon\n");
	for (int i = 0; i < resultAvail; i++) {
		printf("\t%.2f\t%d\n", D[i].coef, D[i].expon);
	}
}