#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

void sortReversed(int[], int); /* selection sort (reversed) */
int is_sorted(int[], int); /* check sorted list */

void main(void) {
	int n; // 배열 크기
	clock_t start;
	double duration;

	printf("n\t시간\t정렬상태\n");
	for (int x = 100; x <= 100000; x *= 10) {
		int millionGen = (x == 100000) ? 10 : 9; // 10만 단위에서는 100만까지, 그 외에는 1~9까지
		for (int i = 1; i <= millionGen; i++) {
			n = x * i; // 100, 200, ..., 900, 1000, 2000, ..., 9000, ..., 90000, 100000, 200000, ..., 1000000
			
			int* list = (int*) malloc (sizeof(int) * n); // 동적 할당
			if (list == NULL) {
				printf("[실패] 메모리 할당에 실패하였습니다... 다시 시도해주세요.\n");
				return;
			}

			for (int i = 0; i < n; i++) {
				list[i] = (rand() % n) + 1;
			}
			
			start = clock();
			sortReversed(list, n);
			duration = ((double) (clock() - start)) / CLOCKS_PER_SEC;

			printf("%d\t%.3f\t%s\n", n, duration, is_sorted(list, n) ? "정렬됨!" : "정렬실패...");

			free(list); // 동적 할당 해제
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
