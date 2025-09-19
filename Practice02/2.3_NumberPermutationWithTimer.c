#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )


void perm(int* list, int i, int n);

int main() {
	double duration[10];
	for (int n = 0; n < 10; n++) {
		int* num = (int*)malloc(sizeof(int) * (n+1));

		if (num == NULL) {
			printf("[����] �޸� �Ҵ翡 �����Ͽ����ϴ�... �ٽ� �õ����ּ���.\n");
			return;
		}

		for (int i = 0; i <= n; i++) {
			num[i] = i; // 0~9 => 10��
		}

		int start = clock();
		perm(num, 0, n);
		printf("\n");
		duration[n] = ((double)(clock() - start)) / CLOCKS_PER_SEC;

		free(num);
	}

	printf("���Ұ���\t����ð�\n");
	for (int i = 0; i < 10; i++) {
		printf("%d\t\t%.3f\n", i + 1, duration[i]);
	}
}

void perm(int* list, int i, int n) {
	int temp;
	if (i == n) {
		for (int j = 0; j <= n; j++) {
			printf("%d", list[j]);
		}
		printf("\t");
	}
	else {
		for (int j = i; j <= n; j++) {
			SWAP(list[i], list[j], temp);
			perm(list, i + 1, n);
			SWAP(list[i], list[j], temp);
		}
	}
}