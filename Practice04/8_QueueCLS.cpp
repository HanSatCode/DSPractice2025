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
		queue = (int*)malloc(max_queue_size * sizeof(int));	// ���� �޸� �Ҵ�
		int front = -1; // ť�� ����ִ� ����
		int rear = -1;
	}

	~Queue() {
		free(queue); // �Ҹ��ڿ��� �޸� ����
	}

	void add_q(int item) {
		if (rear == max_queue_size - 1) {
			max_queue_size *= 2;
			queue = (int*)realloc(queue, max_queue_size * sizeof(int));
			cout << "[Ȯ��] ť�� ��������, " << max_queue_size << "(��)�� Ȯ���Ͽ����ϴ�!" << endl << endl;
		}
		queue[++rear] = item;
	}

	int delete_q() {
		if (front == rear) {
			cout << "[����] ť�� �̹� ������ֽ��ϴ�..." << endl;
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
	srand((unsigned int)time(NULL)); // ���� �õ� ����
	for (int i = 0; i < 1000; i++) { // 1000�� ����
		cout << "[" << i + 1 << "��° ����]" << endl;
		int randomValue = rand() % 2;
		switch (randomValue) {
		case 0:
			myStack.add_q(i);
			break;
		case 1:
			cout << "������ ���� : " << myStack.delete_q() << endl;
		}
		myStack.printQueue();
	}
}