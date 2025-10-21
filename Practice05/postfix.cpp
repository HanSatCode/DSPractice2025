#include <iostream>
#include <cstdlib>
#define MAX_TERMS 100

using namespace std;

typedef enum {
    lparen, rparen, 
    plus, minus, times, divide, mod, eos,
    operand, err_code
} precedence;

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 }; // 있을 때 우선순위
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 }; // 들어올 때 우선순위

char printToken(precedence);

// ============================================================

class Stack {
private:
    int top;
    precedence* stack;
public:
    Stack() {
		stack = (precedence*)malloc(MAX_TERMS * sizeof(precedence)); // 동적 메모리 할당
		top = -1; // 스택이 비어있는 상태
    }

	~Stack() { free(stack); } // 소멸자에서 메모리 해제

    int getTop() {
        return top;
    }

    void push(precedence item) {
        if (top >= MAX_TERMS - 1) return;
        stack[++top] = item;
    }

    precedence pop() {
        if (top == -1) return err_code;
        return stack[top--];
    }

    void printStack() {
        for (int i = 0; i <= top; i++) {
            cout << printToken(stack[i]);
        }
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
        case '(': return precedence::lparen;
        case ')': return precedence::rparen;
        case ' ': return precedence::eos;
        default:  return operand;
    }
}

char printToken(precedence token) { // 토큰 출력
    switch (token) {
        case precedence::plus: return '+';
        case precedence::minus: return '-';
        case precedence::times: return '*';
        case precedence::divide: return '/';
        case precedence::mod: return '%';
        case precedence::lparen: return '(';
        case precedence::rparen: return ')';
        case precedence::eos: return ' ';
        default: return '?';
    }
}

void postfix(char* expr, char* new_expr) {
    Stack stack; stack.push(eos); // 초기값
    int exprIdx = 0, newExprIdx = 0; char symbol;
    precedence op;

    precedence token = getToken(expr, &symbol, &exprIdx);
    while (token != eos) {
        if (token != rparen)    // 오른쪽 괄호가 아닐때만 출력
            cout << symbol << "\t";

        if (token == operand) { // 토큰이 숫자라면
            new_expr[newExprIdx++] = symbol;    // 스택에 바로 넣기
        }
		else if (token == rparen) { // 토큰이 오른쪽 괄호라면
            // '(' 나올 때까지 pop
            while ((op = stack.pop()) != lparen) {
                new_expr[newExprIdx++] = printToken(op);
            }
        }
		else { // 토큰이 연산자라면
            // 그러니까, 우선순위가 높은 연산자가 먼저 들어가야 하니까
			// 만약에 넣으려는 연산자보다 우선순위가 낮거나 같은게 있으면
			// 그 연산자들을 다 빼내고 넣어야함
            while (true) {
                if (stack.getTop() < 0) break; // 스택이 비었으면 종료
                op = stack.pop();
				if (isp[op] < icp[token]) { // 만약 넣을려고 하는 연산자가 우선순위가 더 높다면
                    stack.push(op); // 다시 넣고, 높은 연산자를 먼저 넣음 (122번줄)
                    break;
                }
                new_expr[newExprIdx++] = printToken(op);
            }
            stack.push(token);
        }

        // 토큰이 오른쪽 괄호가 아니면 (출력용)
        if (token != rparen) {
			stack.printStack(); // 스택 출력
			printf("%d\t", stack.getTop() - 1); // 탑 출력
            for (int i = 0; i < newExprIdx; i++)
                cout << new_expr[i] << " "; // postfix 식 출력
            cout << "\n";
        }

        token = getToken(expr, &symbol, &exprIdx);
    }

	// 스택에 남은 연산자 처리
    while ((op = stack.pop()) != eos) {
		new_expr[newExprIdx++] = printToken(op); // postfix 식에 추가
    }
    cout << "\t\t" << stack.getTop() - 1 << "\t";
    for (int i = 0; i < newExprIdx; i++)
        cout << new_expr[i] << " ";
    cout << "\n";
}


int main(void) {
    char expr[] = "((((6/2)-3+(4*2))-5*3)) "; // 뒤에 공백 넣어야함
    char new_expr[MAX_TERMS];

    printf("Infix: %s\nInfix to Postfix:\n", expr);
    printf("Token\tStack\tTop\tOutput\n");

    postfix(expr, new_expr);
}
