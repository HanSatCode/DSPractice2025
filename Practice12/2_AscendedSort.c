#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#define MAX_SIZE 1000001
#define SWAP(x,y,t) { (t) = (x), (x) = (y), (y) = (t); }

void selectionSort(float[], int);
void insertionSort(float[], int);
void insert(float, float[], int);
void startQuickSort(float[], int);
void quickSort(float[], int, int);
void checker(float[], int);

void main(void) {
	int n;
	float A[MAX_SIZE];
	float B[MAX_SIZE];	// 정렬 복사 배열
	clock_t start;
	double duration;

	for (int i = 0; i < 4; i++) { // 4번 시도
		printf("원소 수를 입력하세요 : ");
		scanf("%d", &n);
		if (n < 1 || n > MAX_SIZE) {
			fprintf(stderr, "적절하지 않은 값입니다.\n");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < n; i++) {
			A[i] = (rand() / (0x7fff * 1.0)) * 10000000;
		}
		startQuickSort(A, n); // 사전 오름차순 정렬

		memcpy(B, A, sizeof(float) * n);
		start = clock(); selectionSort(B, n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("Selection Sort Time: %.6f\n", duration);

		memcpy(B, A, sizeof(float) * n);
		start = clock(); insertionSort(B, n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("Insertion Sort Time: %.6f\n", duration);

		memcpy(B, A, sizeof(float) * n);
		start = clock(); startQuickSort(B, n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("Quick Sort Time: %.6f\n", duration);
	}
}

void selectionSort(float list[], int n) {
	int i, j, min; float temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min])
				min = j;
		SWAP(list[i], list[min], temp);
	}
	checker(list, n);
}

void insert(float item, float list[], int i) {
	while (item < list[i]) {
		list[i + 1] = list[i];
		i--;
	}
	list[i + 1] = item;
}

void insertionSort(float list[], int n) {
	int j;
	for (j = 1; j < n; j++) { // 책에는 왜 1-Base 인가??
		float temp = list[j];
		insert(temp, list, j - 1);
	}
	checker(list, n);
}

void startQuickSort(float list[], int n) {
	quickSort(list, 0, n - 1);
	checker(list, n);
}

void quickSort(float list[], int left, int right) {
	int i, j;
	float pivot, temp;
	if (left < right) {
		i = left; j = right + 1;
		pivot = list[left];
		do {
			do i++; while (list[i] < pivot);
			do j--; while (list[j] > pivot);
			if (i < j) SWAP(list[i], list[j], temp);
		} while (i < j);
		SWAP(list[left], list[j], temp);
		quickSort(list, left, j - 1);
		quickSort(list, j + 1, right);
	}
}

void checker(float list[], int n) {
	int i;
	for (i = 0; i < n - 1; i++) {
		if (list[i] > list[i + 1]) {
			printf("[경고] 정렬에 실패하였습니다...\n");
			return;
		}
	}
}