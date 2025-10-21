#include <iostream>
#include <cstdlib>
#define MAX_TERMS 100
#define ERROR -444 // 절대로 넣지 않을 수

using namespace std;

typedef enum {
	plus, minus, times, divide, mod, eos,
	operand, err_code
} precedence;

class Stack {
private:
	int* stack; // 스택을 동적 메모리로 할당
	int top;

public:
	Stack() {
		stack = (int*)malloc(MAX_TERMS * sizeof(int));	// 동적 메모리 할당
		top = -1; // 스택이 비어있는 상태
	}

	~Stack() {
		free(stack); // 소멸자에서 메모리 해제
	}

	int getTop() {
		return top;
	}

	void push(int item) {
		if (top >= MAX_TERMS - 1) { // 마지막 인덱스는 MAX_SIZE - 1이기 때문
			return;
		}
		stack[++top] = item; // top을 먼저 증가시키고 그 위치에 item 삽입
	}

	int pop() {
		if (top == -1) { // top이 -1이면 스택이 비어있는 상태
			return ERROR;
		}
		return stack[top--]; // top 위치의 item 반환 후 top 감소
	}

	void printStack() {
		for (int i = 0; i <= top; i++)
			cout << stack[i] << " "; // 스택에 저장된 모든 항목 출력
		cout << "\t";
	}
};

precedence getToken(char* expr, char* symbol, int* n) { // 토큰을 enum 형태로 반환
	*symbol = expr[(*n)++];
	switch (*symbol) {
		case '+': return precedence::plus;
		case '-': return precedence::minus;
		case '*': return precedence::times;
		case '/': return precedence::divide;
		case '%': return precedence::mod;
		case ' ': return precedence::eos;
		default: return precedence::operand; // 숫자
	}
}

void printToken(precedence token) { // 토큰 출력
	switch (token) {
		case precedence::plus: printf("+\t"); break;
		case precedence::minus:	printf("-\t"); break;
		case precedence::times: printf("*\t"); break;
		case precedence::divide: printf("/\t"); break;
		case precedence::mod: printf("%%\t"); break;
	}
}

int eval(char* expr) {
	Stack myStack; int top = -1;
	char symbol; int op1, op2;
	int n = 0; // 식을 탐색할 인덱스

	precedence token = getToken(expr, &symbol, &n);
	while (token != eos) { // 토큰이 eos가 아닐 때까지 (스페이스 나올때까지)
		if (token == operand) { // 토큰이 숫자라면
			myStack.push(symbol - '0'); // 문자 -> 정수 변환
			cout << symbol - '0' << "\t";
		}
		else {
			op2 = myStack.pop(); op1 = myStack.pop(); // LIFO라서 늦게 들어간게 op2
			switch (token) {
			case precedence::plus:
				myStack.push(op1 + op2);
				break;
			case precedence::minus :
				myStack.push(op1 - op2);
				break;
			case precedence::times:
				myStack.push(op1 * op2);
				break;
			case precedence::divide:
				myStack.push(op1 / op2);
				break;
			case precedence::mod:
				myStack.push(op1 % op2);
			}
			printToken(token);
		}
		myStack.printStack();
		cout << myStack.getTop() - 1 << endl;
		token = getToken(expr, &symbol, &n);
	}
	return myStack.pop(); // 최종 결과 반환
}

int main(void) {
	// 아이디어 : 스택에 숫자를 넣는데, 만약에 연산자가 나오면 스택에서 숫자 2개를 pop로 꺼낸 후,
	// 꺼낸 숫자 2개와 연산자로 연산 후, 다시 스택에 넣는다.
	// 그리고, 마지막에 스택에 남아있는 숫자가 최종 결과가 된다.

	char expr[] = "62/3-42*+53*- "; // 후위표기식. 뒤에 공백을 넣어야한다. (eos 때문)
	printf("Postfix: %s\nEval of Postfix:\n", expr);
	printf("Token\tStack\tTop\n");
	int result = eval(expr);
	printf("Eval: %d", result);
}