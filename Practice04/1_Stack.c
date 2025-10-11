#include <stdio.h>
#define MAX_SIZE 10

int stack[MAX_SIZE];
int top = -1;

void push(int item) {
	if (top == MAX_SIZE -1) {
		printf("[����] ������ �̹� ����á���ϴ�...\n");
		return;
	}
	stack[++top] = item;
}
int pop() {
	if (top == -1) {
		printf("[����] ������ �̹� ������ֽ��ϴ�...\n");
		return -1;
	}
	return stack[top--];
}

void printStack() {
	printf("index\t:\titem\n");
	if (top == -1) {
		printf("(������ ����ֽ��ϴ�!!)\n");
		return;
	}
	for (int i = 0; i <= top; i++)
		printf("%d\t:\t%d\n", i, stack[i]);
}

int main(void) {
	int choice = 0;
	while (choice != -1) {
		printf("[����] 1. push / 2. pop / -1. ���� : ");
		scanf("%d", &choice);
		if (choice == 1) {	// ����
			int item;
			printf("������ ���� : ");
			scanf("%d", &item);
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
}