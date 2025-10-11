#include <stdio.h>
#define MAX_SIZE 10

int queue[MAX_SIZE];
int front = -1;
int rear = -1;

void add_q(int item) {
	if (rear == MAX_SIZE - 1) {
		printf("[����] ť�� �̹� ����á���ϴ�...\n");
		return;
	}
	queue[++rear] = item;
}

int delete_q() {
	if (front == rear) {
		printf("[����] ť�� �̹� ������ֽ��ϴ�...\n");
		return -1;
	}
	return queue[++front];
}

void printQueue() {
	printf("index\t:\titem\n");
	for(int i = front + 1; i <= rear; i++)
		printf("%d\t:\t%d\n", i, queue[i]);
}

int main(void) {
	int choice = 0;
	while (choice != -1) {
		printf("[ť] 1. addQueue / 2. deleteQueue / -1. ���� : ");
		scanf("%d", &choice);
		if (choice == 1) {	// ����
			int item;
			printf("������ ���� : ");
			scanf("%d", &item);
			add_q(item);
			printQueue();
		}
		else if (choice == 2) { // ����
			printf("������ ���� : %d\n", delete_q());
			printQueue();
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