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
	// row_terms: �� ���� ���� ����, starting_pos: �� ���� ���� ��ġ (0���� 100���� = 101��)
	// sorted: ���ĵ� ������ a�� ������ �迭
	int row_terms[TERM_SIZE + 1]; int starting_pos[TERM_SIZE + 1]; int sorted[TERM_SIZE];

	for (int i = 0; i < TERM_SIZE + 1; i++) { // �迭 �ʱ�ȭ
		row_terms[i] = 0;
		starting_pos[i] = 0;
	}

	for (int i = 0; i < TERM_SIZE; i++) // �迭 a�� ���� ���� (���� 100���� ���� 101���� ���ڸ� ī����)
		row_terms[a[i]]++;
	printArray(row_terms, "�� ������ ���� (rowTerms �迭)", 1);

	starting_pos[0] = 0; // 0���� ������ġ�� 0 ����
	for (int i = 1; i < TERM_SIZE + 1; i++) // 0~100���� �� ���� ������ġ ��� (101��)
		starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
	printArray(starting_pos, "�� ���� ������ġ (starting_pos �迭)", 1);

	for (int i = 0; i < TERM_SIZE; i++) { // �迭 a�� ���� sorted�� �ű��
		sorted[starting_pos[a[i]]++] = a[i];
	}
		
	printArray(sorted, "���ĵ� ������ a (sorted �迭)", 0);
}

int main(void) {
	int a[TERM_SIZE]; // 100���� ������ ������ �迭
	srand((unsigned int)time(NULL)); // ���� ���� �ʱ�ȭ
	for (int i = 0; i < TERM_SIZE; i++) // �迭 �ʱ�ȭ
		a[i] = rand() % (TERM_SIZE + 1); // 0~100 ������ ������ �ʱ�ȭ
	printArray(a, "ó�� ������ a (a �迭)", 0);
	countingSort(a);
}