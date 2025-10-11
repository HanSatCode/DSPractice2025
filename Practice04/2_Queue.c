#include <stdio.h>
#define MAX_SIZE 10

int queue[MAX_SIZE];
int front = -1;
int rear = -1;

void add_q(int item) {
	if (rear == MAX_SIZE - 1) {
		printf("[실패] 큐가 이미 가득찼습니다...\n");
		return;
	}
	queue[++rear] = item;
}

int delete_q() {
	if (front == rear) {
		printf("[실패] 큐가 이미 비워져있습니다...\n");
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
		printf("[큐] 1. addQueue / 2. deleteQueue / -1. 종료 : ");
		scanf("%d", &choice);
		if (choice == 1) {	// 삽입
			int item;
			printf("삽입할 원소 : ");
			scanf("%d", &item);
			add_q(item);
			printQueue();
		}
		else if (choice == 2) { // 삭제
			printf("삭제된 원소 : %d\n", delete_q());
			printQueue();
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