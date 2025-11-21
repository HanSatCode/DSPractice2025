#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define COMPARE(x,y) (((x)<(y))?-1:((x)==(y)?0:1))
#define MALLOC(p,s)\
	if (!((p) = malloc(s))) {\
		fprintf(stderr, "메모리가 부족합니다.");\
	}

typedef struct polyNode {
	float coef;
	int expon;
	struct polyNode* link; // 다음 노드를 가리키는 포인터
} polyNode;

typedef struct polyNode* polyPointer;
polyPointer avail = NULL; // 전역 가용 리스트

polyPointer getNode(void) { /* 사용할 노드를 제공 */
	polyPointer node;
	if (avail) {
		node = avail;
		avail = avail->link;
	}
	else MALLOC(node, sizeof(*node));
	return node;
}

void retNode(polyPointer node) { /* 가용 리스트에 노드를 반환 */
	node->link = avail;
	avail = node;
}

void cerase(polyPointer* ptr) { /* ptr가 가리키는 원형 리스트를 제거 */
	polyPointer temp;
	if (*ptr) {
		temp = (*ptr)->link;
		(*ptr)->link = avail;
		avail = temp;
		*ptr = NULL;
	}
}

void attach(float coefficient, int exponent, polyPointer* ptr) {
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));

	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

polyPointer cpadd(polyPointer a, polyPointer b) {
	/* 다항식 a와 b는 헤더 노드를 가진 단순 연결 원형 리스트이고,
	a와 b가 합산된 다항식을 반환함 */
	polyPointer startA, c, lastC;
	float sum = 0;
	int done = FALSE;
	startA = a;
	a = a->link;
	b = b->link;
	c = getNode();
	c->expon = -1; lastC = c;
	do {
		switch (COMPARE(a->expon, b->expon)) {
		case -1:
			attach(b->coef, b->expon, &lastC);
			b = b->link;
			break;
		case 0:
			if (startA == a) done = TRUE;
			else {
				sum = a->coef + b->coef;
				if (sum) attach(sum, a->expon, &lastC);
				a = a->link; b = b->link;
			}
			break;
		case 1:
			attach(a->coef, a->expon, &lastC);
			a = a->link;
		}
	} while (!done);
	lastC->link = c;
	return c;
}

polyPointer create_polynomial() {
	polyPointer head, last; 
	float coef; int expon;

	head = getNode();
	head->coef = -1; head->expon = -1;
	head->link = head; last = head;

	for (;;) {
		printf("다항식의 계수와 차수를 순서대로 입력하세요. (-1 -1 종료) >> ");
		scanf("%f %d", &coef, &expon);
		if (coef == -1 && expon == -1) break;
		attach(coef, expon, &last);
	}
	// 원형 연결 리스트 완성
	last->link = head;
	return head;
}

void print_polynomial(polyPointer C) {
	polyPointer temp;
	temp = C->link;
	printf("coef.\texp.\n");
	while (temp != C) {
		printf("%.2f\t%d\n", temp->coef, temp->expon);
		temp = temp->link;
	}
	printf("\n\n");
}

polyPointer single_mul(polyNode Ai, polyPointer B) {
	polyPointer c, lastC;
	c = getNode();
	c->expon = -1; lastC = c;
	polyPointer tempB = B->link;
	while (tempB != B) {
		attach(Ai.coef * tempB->coef, Ai.expon + tempB->expon, &lastC);
		tempB = tempB->link;
	}
	lastC->link = c;
	return c;
}

polyPointer cpmul(polyPointer A, polyPointer B) {
	/* 출력예시는 A <- B의 각 원소 로 곱하지만, 보고서에는 B <- A의 각 원소를 요구함 */
	polyPointer result = NULL;
	polyPointer tempA = A->link;
	int mulCnt = 1;
	while (tempA != A) {
		polyPointer Ci = single_mul(*tempA, B);
		printf("[C%d(x)]\n", mulCnt++);
		print_polynomial(Ci);
		if (result == NULL) {
			result = Ci;
		}
		else {
			polyPointer tempResult = cpadd(result, Ci);
			cerase(&result);
			cerase(&Ci);
			result = tempResult;
		}
		tempA = tempA->link;
	}
	return result;
}

int main(void) {
	printf("[다항식 A(x)]\n");
	polyPointer A = create_polynomial();
	print_polynomial(A);

	printf("[다항식 B(x)]\n");
	polyPointer B = create_polynomial();
	print_polynomial(B);

	polyPointer C = cpadd(A, B);
	printf("[다항식 A(x)와 B(x)의 덧셈]\n");
	print_polynomial(C);

	printf("[다항식 A(x)와 B(x)의 곱셈]\n");
	polyPointer D = cpmul(A, B);
	print_polynomial(D);

	cerase(&A); cerase(&B); cerase(&C); cerase(&D);
	return 0;
}