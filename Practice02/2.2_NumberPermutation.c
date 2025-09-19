#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )


void perm(int* list, int i, int n);

int main() {
	int n;
	while (1) {
		printf("1���� 32 ������ ���� �Է����ּ���. (���� -1) >>> "); scanf("%d", &n);

		if (n == -1) break;
		else if (n > 32 || n < 1) {
			printf("[���] 1���� 32 ������ ���� �Է����ּ���.\n");
			continue;
		}

		int* num = (int*)malloc(sizeof(int) * n);
		if (num == NULL) {
			printf("[����] �޸� �Ҵ翡 �����Ͽ����ϴ�... �ٽ� �õ����ּ���.\n");
			return;
		}

		for (int i = 0; i < n; i++) {
			num[i] = i + 1;
		}

		int start = clock();
		printf("[1 ~ %d ����] ", n);
		perm(num, 0, n - 1);
		double duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("\n���� �ð� : %.2f��\n", duration);
		free(num);
	}
	printf("[����] ���α׷��� �����մϴ�.\n");
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