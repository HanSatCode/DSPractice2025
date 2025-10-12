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
		queue = (int*) malloc (max_queue_size * sizeof(int));	// ���� �޸� �Ҵ�
		front = 4;
		rear = 4;
	}

	~CircleQueue() {
		free(queue); // �Ҹ��ڿ��� �޸� ����
	}

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
			cout << "[Ȯ��] ť�� ��������, " << max_queue_size << "(��)�� Ȯ���Ͽ����ϴ�!" << endl;
			// �翬�ѰŰ�����... x�ڷ� ���縦 �ؼ� �ε����� ó������ �ʱ�ȭ�ȴ�.
		}
		queue[rear] = item;
	}

	int delete_cq() {
		if (front == rear) {
			cout << "[����] ť�� �̹� ������ֽ��ϴ�..." << endl;
		}
		front = (front + 1) % max_queue_size;
		return queue[front];
	}

	void printCircleQueue() {
		cout << "index\t:\titem" << endl;
		if (front > rear) { // rear�� �ڷ� ���� �ʱ�� ���ư� ���
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
	srand((unsigned int)time(NULL)); // ���� �õ� ����
	for (int i = 0; i < 1000; i++) { // 1000�� ����
		cout << "[" << i + 1 << "��° ����]" << endl;
		int randomValue = rand() % 2;
		switch (randomValue) {
		case 0:
			myCircleQueue.add_cq(i);
			break;
		case 1:
			cout << "������ ���� : " << myCircleQueue.delete_cq() << endl;
		}
		myCircleQueue.printCircleQueue();
	}
}
