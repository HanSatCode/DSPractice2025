#include <iostream>
#include <cstdlib>

using namespace std;

class Queue {
private:
	int* queue;
	int max_queue_size;
	int front = -1;
	int rear = -1;

public:
	Queue(int size = 10) {
		max_queue_size = size;
		queue = (int*)malloc(max_queue_size * sizeof(int));	// 동적 메모리 할당
		int front = -1; // 큐가 비어있는 상태
		int rear = -1;
	}

	~Queue() {
		free(queue); // 소멸자에서 메모리 해제
	}

	void add_q(int item) {
		if (rear == max_queue_size - 1) {
			max_queue_size *= 2;
			queue = (int*)realloc(queue, max_queue_size * sizeof(int));
			cout << "[확장] 큐가 가득차서, " << max_queue_size << "(으)로 확장하였습니다!" << endl << endl;
		}
		queue[++rear] = item;
	}

	int delete_q() {
		if (front == rear) {
			cout << "[실패] 큐가 이미 비워져있습니다..." << endl;
			return -1;
		}
		return queue[++front];
	}

	void printQueue() {
		cout << "index\t:\titem" << endl;
		for (int i = front + 1; i <= rear; i++)
			cout << i << "\t:\t" << queue[i] << endl;
		cout << endl;
	}
};

int main(void) {
	Queue myStack;
	srand((unsigned int)time(NULL)); // 랜덤 시드 설정
	for (int i = 0; i < 1000; i++) { // 1000번 수행
		cout << "[" << i + 1 << "번째 수행]" << endl;
		int randomValue = rand() % 2;
		switch (randomValue) {
		case 0:
			myStack.add_q(i);
			break;
		case 1:
			cout << "삭제된 원소 : " << myStack.delete_q() << endl;
		}
		myStack.printQueue();
	}
}