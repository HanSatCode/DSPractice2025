#include <iostream>
#include <cstdlib>
#define MAX_TERMS 100
#define ERROR -999

using namespace std;

typedef enum {
	plus, minus, times, divide, mod, eos,
	operand, err_code
} precedence;

class Stack {
private:
	int* stack;

public:
	int top;

	Stack() {
		stack = (int*)malloc(MAX_TERMS * sizeof(int));	// ���� �޸� �Ҵ�
		top = -1; // ������ ����ִ� ����
	}

	~Stack() {
		free(stack); // �Ҹ��ڿ��� �޸� ����
	}

	void push(int item) {
		if (top >= MAX_TERMS - 1) { // ������ �ε����� MAX_SIZE - 1�̱� ����
			return;
		}
		stack[++top] = item; // top�� ���� ������Ű�� �� ��ġ�� item ����
	}

	int pop() {
		if (top == -1) { // top�� -1�̸� ������ ����ִ� ����
			return -999;
		}
		return stack[top--]; // top ��ġ�� item ��ȯ �� top ����
	}

	void printStack() {
		for (int i = 0; i <= top; i++)
			cout << stack[i] << " ";
		cout << "\t";
	}
};

precedence getToken(char* expr, char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '+': return precedence::plus;
	case '-': return precedence::minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case ' ': return eos;
	default: return operand; // �ǿ�����
	}
}

void printToken(precedence token) {
	switch (token) {
	case precedence::plus:   printf("+\t"); break;
	case precedence::minus:  printf("-\t"); break;
	case times:  printf("*\t"); break;
	case divide: printf("/\t"); break;
	case mod:    printf("%%\t"); break;
	}
}

int eval(char* expr) {
	Stack myStack;

	precedence token;
	char symbol;
	int op1, op2;
	int top = -1;
	int n = 0;
	token = getToken(expr, &symbol, &n);
	while (token != eos) {
		if (token == operand) {
			myStack.push(symbol - '0');
			cout << symbol - '0' << "\t";
		}
		else {
			op2 = myStack.pop();
			op1 = myStack.pop();
			switch (token) {
			case precedence::plus:
				myStack.push(op1 + op2);
				break;
			case precedence::minus :
				myStack.push(op1 - op2);
				break;
			case times:
				myStack.push(op1 * op2);
				break;
			case divide:
				myStack.push(op1 / op2);
				break;
			case mod:
				myStack.push(op1 % op2);
			}
			printToken(token);
		}
		myStack.printStack();
		cout << myStack.top << endl;
		token = getToken(expr, &symbol, &n);
	}
	return myStack.pop();
}

int main(void) {
	char expr[] = "62/3-42*+53*- ";
	printf("Postfix: %s\nEval of Postfix:\n", expr);
	printf("Token\tStack\tTop\n");
	int result = eval(expr);
	printf("Eval: %d", result);
}