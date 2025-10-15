#include <stdio.h>
#include <stdlib.h>
#define TERM_SIZE 100

void printArray(int source[], char desc[], int offset) { // offset: 오프셋 (인덱스는 0이지만, 숫자는 1부터라서)
	int count = 0;
	printf("[ %s ]\n", desc);

	for (int i = 0; i < TERM_SIZE; i++) {
		printf("[%d] %d", i + offset, source[i]);
		if (i % 10 == 0) printf("\n");
		else printf("\t");
		count++;
	}
	printf("\n=> %d개\n\n", count);
}

void countingSort(int a[]) {
	// row_terms: 각 숫자의 개수, starting_pos: 각 숫자의 시작 위치, sorted: 정렬 a를 저장할 배열
	int row_terms[TERM_SIZE]; int starting_pos[TERM_SIZE]; int sorted[TERM_SIZE];

	for (int i = 0; i < TERM_SIZE; i++) { // 배열 초기화
		row_terms[i] = 0;
		starting_pos[i] = 0;
	}

	for (int i = 0; i < TERM_SIZE; i++) // 배열 a의 갯수 세기 (1은 0번째 인덱스에 저장됨, 2는 1번째, ...)
		row_terms[a[i] - 1]++;
	printArray(row_terms, "각 숫자의 갯수 (row_Terms 배열)", 1);

	starting_pos[0] = 0; // 숫자1의 시작위치
	for (int i = 1; i < TERM_SIZE; i++) // 1 ~ 100까지 각 행의 시작위치 계산
		starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
	printArray(starting_pos, "각 숫자의 시작위치 (starting_pos 배열)", 1); // 100번째 인덱스부터는.. 해당 숫자가 존재하지 않음

	for (int i = 0; i < TERM_SIZE; i++) { // 배열 a의 값을 sorted에 옮기기
		sorted[starting_pos[a[i] - 1]++] = a[i];
	}
		
	printArray(sorted, "정렬된 상태의 a (sorted 배열)", 0);
}

int main(void) {
	int a[TERM_SIZE]; // 100개의 정수를 저장할 배열
	srand((unsigned int)time(NULL)); // 난수 생성 초기화
	for (int i = 0; i < TERM_SIZE; i++) // 배열 초기화
		a[i] = (rand() % TERM_SIZE) + 1; // 1~100 사이의 정수로 초기화
	printArray(a, "처음 상태의 a (a 배열)", 0);
	countingSort(a);
}