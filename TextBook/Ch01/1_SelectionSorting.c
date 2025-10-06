#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101
#define SWAP(x, y, t) ( (t) = (x), (x) = (y), (y) = (t))

void sort(int[], int);

int main(void) {
	int n, list[MAX_SIZE];
	printf("숫자를 입력하세요 : ");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		list[i] = rand() % 1000;
		printf("%d ", list[i]);
	}

	printf("\n");
	sort(list, n);

	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}
}

void sort(int list[], int n) {
	int min, temp;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i; j < n; j++) {
			if (list[j] < list[min]) {
				min = j;
			}
		}
		SWAP(list[i], list[min], temp);
	}
}