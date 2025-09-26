#include <stdio.h>
#include <stdbool.h>s
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

int perm(int*, int, int);

int main(void) {
	int num = 0;
	while (1) {
		printf("n을 입력해주세요 (종료 : -1) >>> ");
		scanf("%d", &num);
		if (num == -1) break;
		int* L = (int*)malloc(sizeof(int) * num);

		for(int i = 0; i < num; i++) {
			L[i] = i;
		}

		printf("[%d 길이의 Boolean 순열] - ", num);
		perm(L, 0, num - 1);
	}
}

int perm(int* list, int i, int n) {
	int temp;
	if (i == n) {
		for (int x = 0; x <= n; x++) {
			printf("%d", list[x]);
		}
		printf("\t");
	}
	else {
		for(int j = i; j <= n; j++) {
			SWAP(list[i], list[j], temp);
			perm(list, i + 1, n);
			SWAP(list[i], list[j], temp);
		}
	}

}