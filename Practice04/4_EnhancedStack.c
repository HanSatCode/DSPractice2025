#include <stdio.h>
#include <stdlib.h>

int *stack;
int max_stack_size = 10; // ���� ������ ũ��
int top = -1;

void push(int item) {
	if (top == max_stack_size - 1) { // ������ �ε����� max_size - 1�̱� ����
		max_stack_size *= 2;
		stack = (int*)realloc(stack, max_stack_size * sizeof(int));
		printf("[Ȯ��] ������ ��������, %d(��)�� Ȯ���Ͽ����ϴ�!\n", max_stack_size);
	}
	stack[++top] = item; // top�� ���� ������Ű�� �� ��ġ�� item ����
}
int pop() {
	if (top == -1) { // top�� -1�̸� ������ ����ִ� ����
		printf("[����] ������ �̹� ������ֽ��ϴ�...\n");
		return -1;
	}
	return stack[top--]; // top ��ġ�� item ��ȯ �� top ����
}

void printStack() {
	printf("index\t:\titem\n");
	if (top == -1) { // ������ ����ִ� ���
		printf("(������ ����ֽ��ϴ�!!)\n");
		return;
	}
	for (int i = 0; i <= top; i++)
		printf("%d\t:\t%d\n", i, stack[i]);
}

int main(void) {
	int choice = 0;
	stack = (int*)malloc(max_stack_size * sizeof(int));	// ���� �޸� �Ҵ� (�⺻ 10)

	while (choice != -1) {
		printf("[����] 1. push / 2. pop / -1. ���� : ");
		scanf("%d", &choice);
		if (choice == 1) {	// ����
			int item;
			printf("������ ���� : "); scanf("%d", &item);
			push(item);
			printStack();
		}
		else if (choice == 2) { // ����
			printf("������ ���� : %d\n", pop());
			printStack();
		}
		else if (choice == -1) { // ����
			printf("���α׷��� �����մϴ�.\n");
		}
		else {
			printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
		}
		printf("\n");
	}
	free(stack); // ���α׷� ���� �� �޸� ����
}