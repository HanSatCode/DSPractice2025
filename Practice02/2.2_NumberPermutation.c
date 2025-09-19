#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )


void perm(int* list, int i, int n);

int main() {
	int n;
	while (1) {
		printf("1부터 32 사이의 수를 입력해주세요. (종료 -1) >>> "); scanf("%d", &n);

		if (n == -1) break;
		else if (n > 32 || n < 1) {
			printf("[경고] 1부터 32 사이의 수를 입력해주세요.\n");
			continue;
		}

		int* num = (int*)malloc(sizeof(int) * n);
		if (num == NULL) {
			printf("[실패] 메모리 할당에 실패하였습니다... 다시 시도해주세요.\n");
			return;
		}

		for (int i = 0; i < n; i++) {
			num[i] = i + 1;
		}

		int start = clock();
		printf("[1 ~ %d 순열] ", n);
		perm(num, 0, n - 1);
		double duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("\n실행 시간 : %.2f초\n", duration);
		free(num);
	}
	printf("[종료] 프로그램을 종료합니다.\n");
}

void perm(int* list, int i, int n) {
	int temp;
	if (i == n) {
		for (int j = 0; j <= n; j++) {
			printf("%d", list[j]);
		}
		printf(" ");
	}
	else {
		for (int j = i; j <= n; j++) {
			SWAP(list[i], list[j], temp);
			perm(list, i + 1, n);
			SWAP(list[i], list[j], temp);
		}
	}
}