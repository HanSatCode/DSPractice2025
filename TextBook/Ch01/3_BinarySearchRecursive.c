#include <stdio.h>
#define COMPARE(x,y) ( (x) < (y) ? -1 : ( (x) == (y) ? 0 : 1 ) )

int binsearch(int[], int, int, int);

int main(void) {
	int n, list[20];

	for (int i = 0; i < 20; i++) {
		list[i] = i * 5;
		printf("%d ", list[i]);
	}

	printf("\n숫자를 입력해주세요 : ");
	scanf_s("%d", &n);

	int result = binsearch(list, n, 0, 19);
	printf(result == -1 ? "찾는 숫자가 없습니다.\n" : "찾는 숫자는 list[%d]에 있습니다.\n", result);
}

int binsearch(int list[], int searchnum, int left, int right) {
	int mid;
	if (left <= right) {
		mid = (left + right) / 2;
		switch (COMPARE(list[mid], searchnum)) {
			case -1:
				return binsearch(list, searchnum, mid + 1, right);
			case 0:
				return mid;
			case 1:
				return binsearch(list, searchnum, left, mid - 1);
		}
	}
	return -1;
}