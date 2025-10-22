#include <stdio.h>
#include <stdlib.h>

void solve(bool* list, int start, int n) {
	if (start == n) {
		printf("< ");
		for (int i = 0; i < n; i++) {
			printf("%s", list[i] ? "true" : "false");
			if (i < n - 1) {
				printf(", ");
			}
		}
		printf(" >\n"); return;
	}
	list[start] = false;
	solve(list, start + 1, n);
	list[start] = true;
	solve(list, start + 1, n);
}


int main(void) {
	int n; bool * list;
	scanf("%d", &n);
	list = (bool*) malloc (n * sizeof(bool));

	for (int i = 0; i < n - 1; i++) {
		list[i] = true;
	}

	solve(list, 0, n);
	free(list);
}