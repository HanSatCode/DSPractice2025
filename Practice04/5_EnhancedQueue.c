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
		printf("[확장] 큐가 가득차서, %d(으)로 확장하였습니다!\n", max_queue_size);
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
	for (int i = front + 1; i <= rear; i++)
		printf("%d\t:\t%d\n", i, queue[i]);
}

int main(void) {
	int choice = 0;
	queue = (int*)malloc(max_queue_size * sizeof(int));	// 동적 메모리 할당 (기본 10)

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
	free(queue); // 프로그램 종료 전 메모리 해제
}