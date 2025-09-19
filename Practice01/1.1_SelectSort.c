#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZE 100000
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
void sort(int[], int); /* selection sort */
int is_sorted(int[], int);

void main(void) {
	int i, n = 100000;
	int A[MAX_SIZE];
	printf("�������� 10������ ���ڸ� �����մϴ� : \n");
	for (i = 0; i < n; i++) {
		A[i] = (rand() % MAX_SIZE) + 1;
		printf("%d ", A[i]);
	}
	sort(A, n);
	printf("\n10������ ���ڸ� ������ ����Դϴ�. : \n");
	for (i = 0; i < n; i++) {	/* print out sorted numbers */
		printf("%d ", A[i]);
	}
	
	if (is_sorted(A, n)) {
		printf("\n������ �� �Ǿ����ϴ�!!!\n");
	}
	else {
		printf("\n������ �߸��Ǿ����ϴ�...\n");
	}
}

void sort(int list[], int n) {
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (list[j] < list[min]) {
				min = j;
			}
		}
		SWAP(list[i], list[min], temp);
	}
}

int is_sorted(int A[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (A[i] > A[i + 1]) return 0;
	}
	return 1;
}
