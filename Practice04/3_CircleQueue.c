#include <stdio.h>
#define MAX_SIZE 10

int queue[MAX_SIZE];
int front = 4;
int rear = 4;

void add_cq(int item) {
	rear = (rear + 1) % MAX_SIZE;
	if (front == rear) {
		printf("[����] ť�� �̹� ����á���ϴ�...\n");
	}
	queue[rear] = item;
}

int delete_cq() {
	if (front == rear) {
		printf("[����] ť�� �̹� ������ֽ��ϴ�...\n");
	}
	front = (front + 1) % MAX_SIZE;
	return queue[front];
}

void printCircleQueue() {
	printf("index\t:\titem\n");
	if(front > rear) { // rear�� �ڷ� ���� �ʱ�� ���ư� ���
		for(int i = front + 1; i < MAX_SIZE; i++)
			printf("%d\t:\t%d\n", i, queue[i]);
		for(int i = 0; i <= rear; i++)
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
}




// ��ⷯ ������ �ϰ�... ADD�ϸ� REAR�� �����ϰ�, DELETE�ϸ� FORNT�� ������Ű�� ���
// front rear�� �����ϸ� ������ �ε����� ����.