#include <stdio.h>
#include <stdlib.h>
#define TERM_SIZE 100

void printArray(int source[], char desc[], int offset) { // offset: ������ (�ε����� 0������, ���ڴ� 1���Ͷ�)
	int count = 0;
	printf("[ %s ]\n", desc);

	for (int i = 0; i < TERM_SIZE; i++) {
		printf("[%d] %d", i + offset, source[i]);
		if (i % 10 == 0) printf("\n");
		else printf("\t");
		count++;
	}
	printf("\n=> %d��\n\n", count);
}

void countingSort(int a[]) {
	// row_terms: �� ������ ����, starting_pos: �� ������ ���� ��ġ, sorted: ���� a�� ������ �迭
	int row_terms[TERM_SIZE]; int starting_pos[TERM_SIZE]; int sorted[TERM_SIZE];

	for (int i = 0; i < TERM_SIZE; i++) { // �迭 �ʱ�ȭ
		row_terms[i] = 0;
		starting_pos[i] = 0;
	}

	for (int i = 0; i < TERM_SIZE; i++) // �迭 a�� ���� ���� (1�� 0��° �ε����� �����, 2�� 1��°, ...)
		row_terms[a[i] - 1]++;
	printArray(row_terms, "�� ������ ���� (row_Terms �迭)", 1);

	starting_pos[0] = 0; // ����1�� ������ġ
	for (int i = 1; i < TERM_SIZE; i++) // 1 ~ 100���� �� ���� ������ġ ���
		starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
	printArray(starting_pos, "�� ������ ������ġ (starting_pos �迭)", 1); // 100��° �ε������ʹ�.. �ش� ���ڰ� �������� ����

	for (int i = 0; i < TERM_SIZE; i++) { // �迭 a�� ���� sorted�� �ű��
		sorted[starting_pos[a[i] - 1]++] = a[i];
	}
		
	printArray(sorted, "���ĵ� ������ a (sorted �迭)", 0);
}

int main(void) {
	int a[TERM_SIZE]; // 100���� ������ ������ �迭
	srand((unsigned int)time(NULL)); // ���� ���� �ʱ�ȭ
	for (int i = 0; i < TERM_SIZE; i++) // �迭 �ʱ�ȭ
		a[i] = (rand() % TERM_SIZE) + 1; // 1~100 ������ ������ �ʱ�ȭ
	printArray(a, "ó�� ������ a (a �迭)", 0);
	countingSort(a);
}