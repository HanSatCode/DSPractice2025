#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define COMPARE(x,y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MAX_SIZE 100000

int binsearch(int[], int, int, int);	// 이진 검색
void sort(int[], int);
int is_sorted(int[], int);

void main(void) {
	int list[MAX_SIZE];

	printf("100,000개의 정수형 난수를 생성합니다. ");
	for (int i = 0; i < MAX_SIZE; i++) {
		list[i] = (rand() % MAX_SIZE) + 1;
	}
	printf(">>> 완료되었습니다.\n");
	
	printf("이전에 생성한 100,000개의 정수형 난수 배열을 정렬합니다. ");
	sort(list , MAX_SIZE);
	printf(">>> 완료되었습니다.\n");
	
	printf("정렬이 정상적으로 완료되었는지 확인합니다. ");
	if (is_sorted(list, MAX_SIZE)) {
		printf(">>> 정렬이 잘 되었습니다!!!\n\n\n");
	}
	else {
		printf(">>> 정렬이 잘못되었습니다...다시 시도해주세요.\n\n\n");
		return;
	}

	int select;
	while (1) {
		printf("검색할 데이터 (1 ~ 100000, 종료는 -1) : ");
		scanf("%d", &select);
		if (select == -1) break;
		int cnt = binsearch(list, select, 0, MAX_SIZE - 1);
		printf("검색 데이터 : %d\t검색 횟수 : %d\n", select, cnt);
	}
	printf("검색을 종료합니다.");
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