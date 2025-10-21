#include <iostream>
#include <cstdlib>
#define MAX_TERMS 100
#define ERROR -444 // 절대로 넣지 않을 수

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

class PostStack {
private:
    int top;
    precedence* stack;
public:
    PostStack() {
        stack = (precedence*)malloc(MAX_TERMS * sizeof(precedence)); // 동적 메모리 할당
        top = -1; // 스택이 비어있는 상태
    }

    ~PostStack() { free(stack); } // 소멸자에서 메모리 해제

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
    PostStack stack; stack.push(eos); // 초기값
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

	new_expr[newExprIdx++] = ' '; // 식의 끝을 표시하기 위해 공백 문자 추가
	new_expr[newExprIdx] = '\0'; // 문자열 종료 문자 추가

    cout << "\t\t" << stack.getTop() - 1 << "\t";
    for (int i = 0; i < newExprIdx; i++)
        cout << new_expr[i] << " ";
    cout << "\n";
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
            case precedence::minus:
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
            cout << printToken(token) << "\t";
        }
        myStack.printStack();
        cout << myStack.getTop() - 1 << endl;
        token = getToken(expr, &symbol, &n);
    }
    return myStack.pop(); // 최종 결과 반환
}

int main(void) {
    char expr[] = "((((6/2)-3+(4*2))-5*3)) ";
    char new_expr[MAX_TERMS];
    printf("Infix: %s\nInfix to Postfix:\n", expr);
    printf("Token\tStack\tTop\tOutput\n");
    postfix(expr, new_expr);

    printf("\n\n");
    printf("Postfix: %s\nEval of Postfix:\n", new_expr);
    printf("Token\tStack\tTop\n");
    int result = eval(new_expr);
    printf("Eval: %d", result);
}