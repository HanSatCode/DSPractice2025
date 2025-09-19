#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

void sortReversed(int[], int); /* selection sort (reversed) */
int is_sorted(int[], int); /* check sorted list */

void main(void) {
	int n; // �迭 ũ��
	clock_t start;
	double duration;

	printf("n\t�ð�\t���Ļ���\n");
	for (int x = 100; x <= 100000; x *= 10) {
		int millionGen = (x == 100000) ? 10 : 9; // 10�� ���������� 100������, �� �ܿ��� 1~9����
		for (int i = 1; i <= millionGen; i++) {
			n = x * i; // 100, 200, ..., 900, 1000, 2000, ..., 9000, ..., 90000, 100000, 200000, ..., 1000000
			
			int* list = (int*) malloc (sizeof(int) * n); // ���� �Ҵ�
			if (list == NULL) {
				printf("[����] �޸� �Ҵ翡 �����Ͽ����ϴ�... �ٽ� �õ����ּ���.\n");
				return;
			}

			for (int i = 0; i < n; i++) {
				list[i] = (rand() % n) + 1;
			}
			
			start = clock();
			sortReversed(list, n);
			duration = ((double) (clock() - start)) / CLOCKS_PER_SEC;

			printf("%d\t%.3f\t%s\n", n, duration, is_sorted(list, n) ? "���ĵ�!" : "���Ľ���...");

			free(list); // ���� �Ҵ� ����
		}
	}
}

void sortReversed(int list[], int n) {
	int i, j, max, temp;
	for (i = 0; i < n - 1; i++) {
		max = i;
		for (j = i + 1; j < n; j++) {
			if (list[j] > list[max]) {
				max = j;
			}
		}
		SWAP(list[i], list[max], temp);
	}
}

int is_sorted(int A[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (A[i] < A[i + 1]) return 0;
	}
	return 1;
}
