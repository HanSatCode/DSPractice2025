#include <stdio.h>
#define MAX_SIZE 10

int queue[MAX_SIZE];
int front = 4;
int rear = 4;

void add_cq(int item) {
	rear = (rear + 1) % MAX_SIZE;
	if (front == rear) {
		printf("[실패] 큐가 이미 가득찼습니다...\n");
	}
	queue[rear] = item;
}

int delete_cq() {
	if (front == rear) {
		printf("[실패] 큐가 이미 비워져있습니다...\n");
	}
	front = (front + 1) % MAX_SIZE;
	return queue[front];
}

void printCircleQueue() {
	printf("index\t:\titem\n");
	if(front > rear) { // rear가 뒤로 돌아 초기로 돌아간 경우
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
}




// 모듈러 연산을 하고... ADD하면 REAR을 증가하고, DELETE하면 FORNT를 증가시키는 방식
// front rear은 웬만하면 마지막 인덱스가 좋다.