#include <iostream>
#include <cstdlib>

using namespace std;

class CircleQueue {
private:
	int* queue;
	int max_queue_size;
	int front;
	int rear;

public:
	CircleQueue(int size = 10) {
		max_queue_size = size;
		queue = (int*) malloc (max_queue_size * sizeof(int));	// 동적 메모리 할당
		front = 4;
		rear = 4;
	}

	~CircleQueue() {
		free(queue); // 소멸자에서 메모리 해제
	}

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
			cout << "[확장] 큐가 가득차서, " << max_queue_size << "(으)로 확장하였습니다!" << endl;
			// 당연한거겠지만... x자로 복사를 해서 인덱스는 처음부터 초기화된다.
		}
		queue[rear] = item;
	}

	int delete_cq() {
		if (front == rear) {
			cout << "[실패] 큐가 이미 비워져있습니다..." << endl;
		}
		front = (front + 1) % max_queue_size;
		return queue[front];
	}

	void printCircleQueue() {
		cout << "index\t:\titem" << endl;
		if (front > rear) { // rear가 뒤로 돌아 초기로 돌아간 경우
			for (int i = front + 1; i < max_queue_size; i++)
				cout << i << "\t:\t" << queue[i] << endl;
			for (int i = 0; i <= rear; i++)
				cout << i << "\t:\t" << queue[i] << endl;
			return;
		}
		else {
			for (int i = front + 1; i <= rear; i++)
				cout << i << "\t:\t" << queue[i] << endl;
		}
	}
};

int main(void) {
	CircleQueue myCircleQueue;
	srand((unsigned int)time(NULL)); // 랜덤 시드 설정
	for (int i = 0; i < 1000; i++) { // 1000번 수행
		cout << "[" << i + 1 << "번째 수행]" << endl;
		int randomValue = rand() % 2;
		switch (randomValue) {
		case 0:
			myCircleQueue.add_cq(i);
			break;
		case 1:
			cout << "삭제된 원소 : " << myCircleQueue.delete_cq() << endl;
		}
		myCircleQueue.printCircleQueue();
	}
}
