#include <stdio.h>
#include <stdlib.h>

int *queue;
int max_queue_size = 10;
int front = 4;
int rear = 4;

void add_cq(int item) {
	rear = (rear + 1) % max_queue_size;
	if (front == rear) {
		
		int* temp = (int*)malloc(max_queue_size * 2 * sizeof(int)); // 새로운 큐 생성
		
		int tempIndex = 0;
		for (int right = front + 1; right < max_queue_size; right++) // 오른쪽 복사
			temp[tempIndex++] = queue[right];
		for (int left = 0; left <= rear; left++) // 왼쪽 복사
			temp[tempIndex++] = queue[left];

		max_queue_size *= 2; // 큐 크기 확장 (미리 확장하면 right 복사에서 오류남)
		front = max_queue_size - 1; // front 초기화
		rear = tempIndex - 1; // rear 초기화

		free(queue); // 기존 큐 메모리 해제
		queue = temp; // 큐 교체
		printf("[확장] 큐가 가득차서, %d(으)로 확장하였습니다!\n", max_queue_size);
		// 당연한거겠지만... x자로 복사를 해서 인덱스는 처음부터 초기화된다.
	}
	queue[rear] = item;
}

int delete_cq() {
	if (front == rear) {
		printf("[실패] 큐가 이미 비워져있습니다...\n");
	}
	front = (front + 1) % max_queue_size;
	return queue[front];
}

void printCircleQueue() {
	printf("index\t:\titem\n");
	if (front > rear) { // rear가 뒤로 돌아 초기로 돌아간 경우
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
	queue = (int*)malloc(max_queue_size * sizeof(int));	// 동적 메모리 할당 (기본 10)
	
	while (choice != -1) {
		printf("[원형큐] 1. addCircleQueue / 2. deleteCircleQueue / -1. 종료 : ");
		scanf("%d", &choice);
		if (choice == 1) {	// 삽입
			int item;
			printf("삽입할 원소 : ");
			scanf("%d", &item);
			add_cq(item);
			printCircleQueue();
		}
		else if (choice == 2) { // 삭제
			printf("삭제된 원소 : %d\n", delete_cq());
			printCircleQueue();
		}
		else if (choice == -1) { // 종료
			printf("프로그램을 종료합니다.\n");
		}
		else {
			printf("잘못된 입력입니다. 다시 시도하세요.\n");
		}
		printf("\n");
	}
	free(queue); // 프로그램 종료 전에 메모리 해제
}
