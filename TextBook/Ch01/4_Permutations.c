#include <stdio.h>
#define SWAP(x, y, t) ( (t) = (x), (x) = (y), (y) = (t) )

void perm(char*, int, int);

int main(void) {
	char list[4] = { 'A', 'B', 'C', 'D'};
	perm(list, 0, 3);
}

void perm(char* list, int i, int n) {
	int temp;
	if (i == n) {
		for (int i = 0; i <= n; i++) {
			printf("%c ", list[i]);
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