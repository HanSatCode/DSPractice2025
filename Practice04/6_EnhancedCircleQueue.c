#include <stdio.h>
#include <stdlib.h>

int *queue;
int max_queue_size = 10;
int front = 4;
int rear = 4;

void add_cq(int item) {
	rear = (rear + 1) % max_queue_size;
	if (front == rear) {
		
		int* temp = (int*)malloc(max_queue_size * 2 * sizeof(int)); // ���ο� ť ����
		
		int tempIndex = 0;
		for (int right = front + 1; right < max_queue_size; right++) // ������ ����
			temp[tempIndex++] = queue[right];
		for (int left = 0; left <= rear; left++) // ���� ����
			temp[tempIndex++] = queue[left];

		max_queue_size *= 2; // ť ũ�� Ȯ�� (�̸� Ȯ���ϸ� right ���翡�� ������)
		front = max_queue_size - 1; // front �ʱ�ȭ
		rear = tempIndex - 1; // rear �ʱ�ȭ

		free(queue); // ���� ť �޸� ����
		queue = temp; // ť ��ü
		printf("[Ȯ��] ť�� ��������, %d(��)�� Ȯ���Ͽ����ϴ�!\n", max_queue_size);
		// �翬�ѰŰ�����... x�ڷ� ���縦 �ؼ� �ε����� ó������ �ʱ�ȭ�ȴ�.
	}
	queue[rear] = item;
}

int delete_cq() {
	if (front == rear) {
		printf("[����] ť�� �̹� ������ֽ��ϴ�...\n");
	}
	front = (front + 1) % max_queue_size;
	return queue[front];
}

void printCircleQueue() {
	printf("index\t:\titem\n");
	if (front > rear) { // rear�� �ڷ� ���� �ʱ�� ���ư� ���
		for (int i = front + 1; i < max_queue_size; i++)
			printf("%d\t:\t%d\n", i, queue[i]);
		for (int i = 0; i <= rear; i++)
			printf("%d\t:\t%d\n", i, queue[i]);
		return;
	}
	else {
		for (int i = front + 1; i <= rear; i++)
			printf("%d\t:\t%d\n", i, queue[i]);
	}
}

int main(void) {
	int choice = 0;
	queue = (int*)malloc(max_queue_size * sizeof(int));	// ���� �޸� �Ҵ� (�⺻ 10)
	
	while (choice != -1) {
		printf("[����ť] 1. addCircleQueue / 2. deleteCircleQueue / -1. ���� : ");
		scanf("%d", &choice);
		if (choice == 1) {	// ����
			int item;
			printf("������ ���� : ");
			scanf("%d", &item);
			add_cq(item);
			printCircleQueue();
		}
		else if (choice == 2) { // ����
			printf("������ ���� : %d\n", delete_cq());
			printCircleQueue();
		}
		else if (choice == -1) { // ����
			printf("���α׷��� �����մϴ�.\n");
		}
		else {
			printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
		}
		printf("\n");
	}
	free(queue); // ���α׷� ���� ���� �޸� ����
}
