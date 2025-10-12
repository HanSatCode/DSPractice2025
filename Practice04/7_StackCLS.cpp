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
		stack = (int*) malloc (max_stack_size * sizeof(int));	// 동적 메모리 할당
		top = -1; // 스택이 비어있는 상태
	}

	~Stack() {
		free(stack); // 소멸자에서 메모리 해제
	}

	void push(int item) {
		if (top == max_stack_size - 1) { // 마지막 인덱스는 MAX_SIZE - 1이기 때문
			max_stack_size *= 2;
			stack = (int*)realloc(stack, max_stack_size * sizeof(int));
			cout << "[확장] 스택이 가득차서, " << max_stack_size << "(으)로 확장하였습니다!" << endl << endl;
		}
		stack[++top] = item; // top을 먼저 증가시키고 그 위치에 item 삽입
	}
	int pop() {
		if (top == -1) { // top이 -1이면 스택이 비어있는 상태
			cout << "[실패] 스택이 이미 비워져있습니다..." << endl;
			return -1;
		}
		return stack[top--]; // top 위치의 item 반환 후 top 감소
	}

	void printStack() {
		cout << "index\t:\titem" << endl;
		if (top == -1) { // 스택이 비어있는 경우
			cout << "(스택이 비어있습니다!!)" << endl << endl;
			return;
		}
		for (int i = 0; i <= top; i++)
			cout << i << "\t:\t" << stack[i] << endl;
		cout << endl;
	}
};

int main(void) {
	Stack myStack;
	srand((unsigned int)time(NULL)); // 랜덤 시드 설정
	for (int i = 0; i < 1000; i++) { // 1000번 수행
		cout << "[" << i + 1 << "번째 수행]" << endl;
		int randomValue = rand() % 2;
		switch (randomValue) {
		case 0:
			myStack.push(i);
			break;
		case 1:
			cout << "삭제된 원소 : " << myStack.pop() << endl;
		}
		myStack.printStack();
	}
}