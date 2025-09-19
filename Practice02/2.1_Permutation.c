#include <stdio.h>
#include <string.h>
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )

void perm(char* list, int i, int n);

int main() {
	char A[][10] = { "GO", "BOY", "GIRL", "GIRLS" };
	for (int i = 0; i < 4; i++) {
		printf("[%s ¼ø¿­] ", A[i]);
		perm(A[i], 0, strlen(A[i]) - 1);
		printf("\n");
	}
}

void perm(char* list, int i, int n) {
	int temp; 
	if (i == n) {
		for (int j = 0; j <= n; j++) {
			printf("%c", list[j]);
		}
		printf("  ");
	}
	else {
		for (int j = i; j <= n; j++) {
			SWAP(list[i], list[j], temp);
			perm(list, i + 1, n);
			SWAP(list[i], list[j], temp);
		}
	}
}