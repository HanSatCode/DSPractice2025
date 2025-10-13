#include <stdio.h>
#include <stdlib.h>
#define TERM_SIZE 100

void printArray(int source[], char desc[], int type) {
	printf("[ %s ]\n", desc);

	if (type) {
		for (int i = 0; i < TERM_SIZE + 1; i++) {
			printf("[%d] %d", i, source[i]);
			if (i % 10 == 0) printf("\n");
			else printf("\t");
		}
		printf("\n\n");
		return;
	}

	for (int i = 0; i < TERM_SIZE; i++) {
		printf("[%d] %d", i, source[i]);
		if (i % 10 == 0) printf("\n");
		else printf("\t");
	}
	printf("\n\n");
}

void countingSort(int a[]) {
	// row_terms: 각 행의 항의 개수, starting_pos: 각 행의 시작 위치 (0부터 100까지 = 101개)
	// sorted: 정렬된 상태의 a를 저장할 배열
	int row_terms[TERM_SIZE + 1]; int starting_pos[TERM_SIZE + 1]; int sorted[TERM_SIZE];

	for (int i = 0; i < TERM_SIZE + 1; i++) { // 배열 초기화
		row_terms[i] = 0;
		starting_pos[i] = 0;
	}

	for (int i = 0; i < TERM_SIZE; i++) // 배열 a의 갯수 세기 (원소 100개에 대해 101개의 숫자를 카운팅)
		row_terms[a[i]]++;
	printArray(row_terms, "각 숫자의 갯수 (rowTerms 배열)", 1);

	starting_pos[0] = 0; // 0번의 시작위치는 0 부터
	for (int i = 1; i < TERM_SIZE + 1; i++) // 0~100까지 각 행의 시작위치 계산 (101개)
		starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
	printArray(starting_pos, "각 행의 시작위치 (starting_pos 배열)", 1);

	for (int i = 0; i < TERM_SIZE; i++) { // 배열 a의 값을 sorted에 옮기기
		sorted[starting_pos[a[i]]++] = a[i];
	}
		
	printArray(sorted, "정렬된 상태의 a (sorted 배열)", 0);
}

int main(void) {
	int a[TERM_SIZE]; // 100개의 정수를 저장할 배열
	srand((unsigned int)time(NULL)); // 난수 생성 초기화
	for (int i = 0; i < TERM_SIZE; i++) // 배열 초기화
		a[i] = rand() % (TERM_SIZE + 1); // 0~100 사이의 난수로 초기화
	printArray(a, "처음 상태의 a (a 배열)", 0);
	countingSort(a);
}