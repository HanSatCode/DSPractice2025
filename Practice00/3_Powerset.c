#include <stdio.h>
#include <stdlib.h>

void powerset(char* list, char* select, int select_index, int depth, int length) {

	if (depth == length) {
		printf("{ ");
		for (int i = 0; i < select_index; i++) {
			printf("%c", select[i]);
			if (i != select_index - 1) printf(", ");
		}
		printf(" }\n");
		return;
	}

	select[select_index] = list[depth]; // 넣는다고 가정. 근데, 인덱스 안올리면 다음에 또 덮어씌워짐
	powerset(list, select, select_index + 1, depth + 1, length); // 1. 이번에 넣었음
	powerset(list, select, select_index, depth + 1, length); // 2. 이번에 안 넣었음
}

int main(void) {

	printf("숫자를 입력하세요 : "); int n; scanf("%d", &n);
	
	char* origin = (char*) malloc (n * sizeof(char));
	char* target = (char*) malloc (n * sizeof(char));

	for (int i = 0; i < n; i++) {
		origin[i] = 'a' + i;
	}

	powerset(origin, target, 0, 0, n);

	free(origin); free(target);
}