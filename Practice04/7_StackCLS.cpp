#include <iostream>
#include <cstdlib>

using namespace std;

class Stack {
private:
	int* stack;
	int max_stack_size;
	int top;

public:
	Stack(int size = 10) {
		max_stack_size = size;
		stack = (int*) malloc (max_stack_size * sizeof(int));	// ���� �޸� �Ҵ�
		top = -1; // ������ ����ִ� ����
	}

	~Stack() {
		free(stack); // �Ҹ��ڿ��� �޸� ����
	}

	void push(int item) {
		if (top == max_stack_size - 1) { // ������ �ε����� MAX_SIZE - 1�̱� ����
			max_stack_size *= 2;
			stack = (int*)realloc(stack, max_stack_size * sizeof(int));
			cout << "[Ȯ��] ������ ��������, " << max_stack_size << "(��)�� Ȯ���Ͽ����ϴ�!" << endl << endl;
		}
		stack[++top] = item; // top�� ���� ������Ű�� �� ��ġ�� item ����
	}
	int pop() {
		if (top == -1) { // top�� -1�̸� ������ ����ִ� ����
			cout << "[����] ������ �̹� ������ֽ��ϴ�..." << endl;
			return -1;
		}
		return stack[top--]; // top ��ġ�� item ��ȯ �� top ����
	}

	void printStack() {
		cout << "index\t:\titem" << endl;
		if (top == -1) { // ������ ����ִ� ���
			cout << "(������ ����ֽ��ϴ�!!)" << endl << endl;
			return;
		}
		for (int i = 0; i <= top; i++)
			cout << i << "\t:\t" << stack[i] << endl;
		cout << endl;
	}
};

int main(void) {
	Stack myStack;
	srand((unsigned int)time(NULL)); // ���� �õ� ����
	for (int i = 0; i < 1000; i++) { // 1000�� ����
		cout << "[" << i + 1 << "��° ����]" << endl;
		int randomValue = rand() % 2;
		switch (randomValue) {
		case 0:
			myStack.push(i);
			break;
		case 1:
			cout << "������ ���� : " << myStack.pop() << endl;
		}
		myStack.printStack();
	}
}