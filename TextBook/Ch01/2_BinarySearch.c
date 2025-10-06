#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) ( (x) < (y) ? -1 : ( (x) == (y) ? 0 : 1 ) )

int binsearch(int[], int, int, int);

int main(void) {
	int n, list[20];

	for (int i = 0; i < 20; i++) {
		list[i] = i * 5;
		printf("%d ", list[i]);
	}

	printf("\n���ڸ� �Է����ּ��� : ");
	scanf_s("%d", &n);

	int result = binsearch(list, n, 0, 19);
	printf(result == -1 ? "ã�� ���ڰ� �����ϴ�.\n" : "ã�� ���ڴ� list[%d]�� �ֽ��ϴ�.\n", result);
}

int binsearch(int list[], int searchnum, int left, int right) {
	int mid;
	while (left <= right) {
		mid = (left + right) / 2;
		switch (COMPARE(list[mid], searchnum)) {
		case -1:
			left = mid + 1;
			break;
		case 0:
			return mid;
		case 1:
			right = mid - 1;
			break;
		}
	}
	return -1;
}