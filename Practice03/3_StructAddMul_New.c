#include <stdio.h>
#include <stdlib.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

float tempCoef; int tempExpon;

typedef struct {
	float coef; // 계수 (실수)
	int expon; // 차수 (양의 정수)
} polynomial;

polynomial* result; // 최종 리턴
polynomial* tempResult;		// 중간 결과 저장

int avail = 0; // D(x)의 현재 인덱스
int finishA = -1, finishB = -1; // 전역 변수. 끝 인덱스

void attach(float confficient, int exponent) { /* 새로운 항을 다항식에 추가한다. */
	tempResult[avail].coef = confficient;
	tempResult[avail++].expon = exponent;
}

polynomial* padd(polynomial* A, polynomial* B) { /* A(x)와 B(x)를 더하여 새 D(x)를 생성 */
	float coefficient; int startA = 0, startB = 0; avail = 0;

	tempResult = (polynomial*)malloc((finishA + finishB) * sizeof(polynomial));

	while (startA <= finishA && startB <= finishB) {
		switch (COMPARE(A[startA].expon, B[startB].expon)) {
		case -1: /* a의 차수가 b의 차수보다 작은 경우*/
			attach(B[startB].coef, B[startB].expon); startB++;
			break;
		case 0: /* 차수가 같은 경우 */
			coefficient = A[startA].coef + B[startB].coef;
			if (coefficient) attach(coefficient, A[startA].expon); // 계수가 0이 아니면
			startA++; startB++;
			break;
		case 1:  /* a의 차수가 b의 차수보다 큰 경우 */
			attach(A[startA].coef, A[startA].expon); startA++;
		}
	}

	for (; startA <= finishA; startA++) { // A(x)의 남은 항들을 D(x)에 첨가
		attach(A[startA].coef, A[startA].expon);
	}
	for (; startB <= finishB; startB++) { // B(x)의 남은 항들을 D(x)에 첨가
		attach(B[startB].coef, B[startB].expon);
	}

	avail--; // 마지막에 증가된 avail 보정
	return tempResult;
}

polynomial* single_mul(polynomial Ai, polynomial* B) {	// A(x)와 B(x)를 곱하여 새 Ci(x)를 생성. Ai가 기준임 !!!
	polynomial* singleMulTemp = (polynomial*)malloc(finishB * sizeof(polynomial));

	int mulCnt = 1;
	printf("[C%d(x)]\tcoef\texpon\n", mulCnt++);
	for (int i = 0; i <= finishB; i++) {
		singleMulTemp[i].coef = Ai.coef * B[i].coef;
		singleMulTemp[i].expon = Ai.expon + B[i].expon;
		printf("\t%.2f\t%d\n", singleMulTemp[i].coef, singleMulTemp[i].expon);
	}
	return singleMulTemp;
}

polynomial* pmul(polynomial* A, polynomial* B) {
	int ACount = finishA;
	for (int i = 0; i <= ACount; i++) {
		polynomial* Ci = single_mul(A[i], B); // A를 기준으로 곱해야 됨
		if (i == 0) {
			result = Ci; finishA = finishB; // 첫번째 결과의 끝 인덱스는 B의 끝 인덱스
			continue; // 첫번째는 그냥 대입
		}
		result = padd(result, Ci); // 더하기
		finishA = avail; // 더하기 전에 finishA를 result의 마지막 인덱스로 설정
	}
	return result;
}

int main(void) {
	polynomial* A = (polynomial*)malloc(10 * sizeof(polynomial));
	polynomial* B = (polynomial*)malloc(10 * sizeof(polynomial));

	printf("[3.1 다항식 생성]\n");

	while (1) {
		printf("[%d번째] A(x)의 계수와 차수를 순서대로 입력하세요. (종료는 -1 -1) : ", finishA + 1); scanf("%f %d", &tempCoef, &tempExpon);
		if (finishA > 10) realloc(A, (finishA + 1) * sizeof(polynomial));	// 10개 초과시 메모리 크기 재할당
		A[++finishA].coef = tempCoef; A[finishA].expon = tempExpon;
		if (tempCoef == -1 && tempExpon == -1) {  // -1 -1 입력시 종료
			--finishA; break;
		}
	}

	printf("[A(x)]\tcoef\texpon\n");
	for (int i = 0; ; i++) {
		if (A[i].expon == -1) break;
		printf("\t%.2f\t%d\n", A[i].coef, A[i].expon);
	}

	while (1) {
		printf("[%d번째] B(x)의 계수와 차수를 순서대로 입력하세요. (종료는 -1 -1) : ", finishB + 1); scanf("%f %d", &tempCoef, &tempExpon);
		if (finishB > 10) realloc(B, (finishB + 1) * sizeof(polynomial));	// 10개 초과시 메모리 크기 재할당
		B[++finishB].coef = tempCoef; B[finishB].expon = tempExpon;
		if (tempCoef == -1 && tempExpon == -1) {	// -1 -1 입력시 종료
			--finishB; break; 
		}
	}

	printf("[B(x)]\tcoef\texpon\n");
	for (int i = 0; ; i++) {
		if (B[i].expon == -1) break;
		printf("\t%.2f\t%d\n", B[i].coef, B[i].expon);
	}

	// ==========================================================

	printf("\n[3.2 다항식의 덧셈]\n");
	result = (polynomial*)malloc((finishA * finishB) * sizeof(polynomial));

	polynomial* D = padd(A, B);
	

	printf("[D(x)]\tcoef\texpon\n");
	for (int i = 0; i <= avail; i++) {
		printf("\t%.2f\t%d\n", D[i].coef, D[i].expon);
	}

	// ==========================================================

	printf("\n[3.3 다항식의 곱셈]\n");
	free(result); avail = 0;
	result = (polynomial*)malloc((finishA * finishB) * sizeof(polynomial));
	
	D = pmul(A, B);

	printf("[D(x)]\tcoef\texpon\n");
	for (int i = 0; i <= avail; i++) {
		printf("\t%.2f\t%d\n", D[i].coef, D[i].expon);
	}
}