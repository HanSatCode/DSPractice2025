#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define COMPARE(x,y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MAX_SIZE 100000

int binsearch(int[], int, int, int);	// ���� �˻�
void sort(int[], int);
int is_sorted(int[], int);

void main(void) {
	int list[MAX_SIZE];

	printf("100,000���� ������ ������ �����մϴ�. ");
	for (int i = 0; i < MAX_SIZE; i++) {
		list[i] = (rand() % MAX_SIZE) + 1;
	}
	printf(">>> �Ϸ�Ǿ����ϴ�.\n");
	
	printf("������ ������ 100,000���� ������ ���� �迭�� �����մϴ�. ");
	sort(list , MAX_SIZE);
	printf(">>> �Ϸ�Ǿ����ϴ�.\n");
	
	printf("������ ���������� �Ϸ�Ǿ����� Ȯ���մϴ�. ");
	if (is_sorted(list, MAX_SIZE)) {
		printf(">>> ������ �� �Ǿ����ϴ�!!!\n\n\n");
	}
	else {
		printf(">>> ������ �߸��Ǿ����ϴ�...�ٽ� �õ����ּ���.\n\n\n");
		return;
	}

	int select;
	while (1) {
		printf("�˻��� ������ (1 ~ 100000, ����� -1) : ");
		scanf("%d", &select);
		if (select == -1) break;
		int cnt = binsearch(list, select, 0, MAX_SIZE - 1);
		printf("�˻� ������ : %d\t�˻� Ƚ�� : %d\n", select, cnt);
	}
	printf("�˻��� �����մϴ�.");
}

int binsearch(int list[], int searchnum, int left, int right) {
	int middle;
	int counter = 0;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], searchnum)) {
			case -1:
				left = middle + 1;
				break;
			case 0:
				return counter;
			case 1:
				right = middle - 1;
		}
		counter++;
	}
	return -1;
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