#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define ERROR -444.4444

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

polynomial* psub(polynomial* A, polynomial* B) { /* A(x)와 B(x)를 빼서 새 D(x)를 생성 */
	float coefficient; int startA = 0, startB = 0; avail = 0;

	tempResult = (polynomial*)malloc((finishA + finishB) * sizeof(polynomial));

	while (startA <= finishA && startB <= finishB) {
		switch (COMPARE(A[startA].expon, B[startB].expon)) {
		case -1: /* a의 차수가 b의 차수보다 작은 경우*/
			attach(-B[startB].coef, B[startB].expon); startB++;
			break;
		case 0: /* 차수가 같은 경우 */
			coefficient = A[startA].coef - B[startB].coef;
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
		attach(-B[startB].coef, B[startB].expon);
	}
	
	tempResult[avail].coef = -1;
	tempResult[avail].expon = -1;
	return tempResult;
}

double peval(polynomial* D, double b) { // 미지수의 b값을 넣어 계산하기
	int startA = 0; double result = 0;
	while (D[startA].coef != -1) {
		result += D[startA].coef * pow(b, D[startA].expon);
		startA++;
	}
	return result;
}

double bisection(polynomial* D, double a, double b, double TOL) { // 이분법으로 항 찾기
	double c = 0;
	if (peval(D, a) * peval(D, b) >= 0) {
		return ERROR; // 오류로 가정
	}
	while ((b - a) >= TOL) {
		c = (a + b) / 2;
		
		if (abs(peval(D, c)) == 0.000000) { // 소수점 정밀도
			break;
		}
		else if (peval(D, a) * peval(D, c) > 0) {
			a = c;
		}
		else {
			b = c;
		}
	}
	return c;
}

int main(void) {
	polynomial* A = (polynomial*)malloc(10 * sizeof(polynomial));
	polynomial* B = (polynomial*)malloc(10 * sizeof(polynomial));

	printf("[다항식 생성]\n");

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

	printf("\n[다항식 D (A - B)]\n");

	polynomial* D = psub(A, B);

	printf("[D(x)]\tcoef\texpon\n");
	for (int i = 0; i <= avail - 1; i++) {
		printf("\t%.2f\t%d\n", D[i].coef, D[i].expon);
	}

	// ==========================================================

	printf("\n[다항식 D의 해 계산 범위 (a, b, TOL 순으로 입력)] ");
	double a, b, TOL; scanf("%lf %lf %lf", &a, &b, &TOL);
	double endOfResult = bisection(D, a, b, TOL);
	if (endOfResult == -444.4444) {
		printf("\n[다항식 D의 해] 오류가 발생하였습니다!\n");
	}
	else {
		printf("\n[다항식 D의 해] %lf\n", endOfResult);
	}
	
}