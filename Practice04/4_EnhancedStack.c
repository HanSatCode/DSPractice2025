#include <stdio.h>
#include <stdlib.h>

int *stack;
int max_stack_size = 10; // 현재 스택의 크기
int top = -1;

void push(int item) {
	if (top == max_stack_size - 1) { // 마지막 인덱스는 max_size - 1이기 때문
		max_stack_size *= 2;
		stack = (int*)realloc(stack, max_stack_size * sizeof(int));
		printf("[확장] 스택이 가득차서, %d(으)로 확장하였습니다!\n", max_stack_size);
	}
	stack[++top] = item; // top을 먼저 증가시키고 그 위치에 item 삽입
}
int pop() {
	if (top == -1) { // top이 -1이면 스택이 비어있는 상태
		printf("[실패] 스택이 이미 비워져있습니다...\n");
		return -1;
	}
	return stack[top--]; // top 위치의 item 반환 후 top 감소
}

void printStack() {
	printf("index\t:\titem\n");
	if (top == -1) { // 스택이 비어있는 경우
		printf("(스택이 비어있습니다!!)\n");
		return;
	}
	for (int i = 0; i <= top; i++)
		printf("%d\t:\t%d\n", i, stack[i]);
}

int main(void) {
	int choice = 0;
	stack = (int*)malloc(max_stack_size * sizeof(int));	// 동적 메모리 할당 (기본 10)

	while (choice != -1) {
		printf("[스택] 1. push / 2. pop / -1. 종료 : ");
		scanf("%d", &choice);
		if (choice == 1) {	// 삽입
			int item;
			printf("삽입할 원소 : "); scanf("%d", &item);
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
	free(stack); // 프로그램 종료 전 메모리 해제
}