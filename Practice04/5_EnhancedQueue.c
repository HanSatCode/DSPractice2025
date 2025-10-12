#include <stdio.h>
#include <stdlib.h>

int* queue;
int max_queue_size = 10;
int front = -1;
int rear = -1;

void add_q(int item) {
	if (rear == max_queue_size - 1) {
		max_queue_size *= 2;
		queue = (int*)realloc(queue, max_queue_size * sizeof(int));
		printf("[Ȯ��] ť�� ��������, %d(��)�� Ȯ���Ͽ����ϴ�!\n", max_queue_size);
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
	for (int i = front + 1; i <= rear; i++)
		printf("%d\t:\t%d\n", i, queue[i]);
}

int main(void) {
	int choice = 0;
	queue = (int*)malloc(max_queue_size * sizeof(int));	// ���� �޸� �Ҵ� (�⺻ 10)

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
	free(queue); // ���α׷� ���� �� �޸� ����
}