#include <stdio.h>
#define MAX_SIZE 10

int stack[MAX_SIZE];
int top = -1;

void push(int item) {
	if (top == MAX_SIZE -1) {
		printf("[실패] 스택이 이미 가득찼습니다...\n");
		return;
	}
	stack[++top] = item;
}
int pop() {
	if (top == -1) {
		printf("[실패] 스택이 이미 비워져있습니다...\n");
		return -1;
	}
	return stack[top--];
}

void printStack() {
	printf("index\t:\titem\n");
	if (top == -1) {
		printf("(스택이 비어있습니다!!)\n");
		return;
	}
	for (int i = 0; i <= top; i++)
		printf("%d\t:\t%d\n", i, stack[i]);
}

int main(void) {
	int choice = 0;
	while (choice != -1) {
		printf("[스택] 1. push / 2. pop / -1. 종료 : ");
		scanf("%d", &choice);
		if (choice == 1) {	// 삽입
			int item;
			printf("삽입할 원소 : ");
			scanf("%d", &item);
			push(item);
			printStack();
		}
		else if (choice == 2) { // 삭제
			printf("삭제된 원소 : %d\n", pop());
			printStack();
		}
		else if (choice == -1) { // 종료
			printf("프로그램을 종료합니다.\n");
		}
		else {
			printf("잘못된 입력입니다. 다시 시도하세요.\n");
		}
		printf("\n");
	}
}