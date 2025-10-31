#include <stdio.h>
#include <stdlib.h> // malloc, free를 위해 필요
#define ERROR -999

typedef struct node {
    int data;
    struct node* next; // 다음 노드를 가리키는 포인터
} Node;

Node* A = NULL; // 리스트의 시작 노드를 가리키는 포인터
Node* temp = NULL; // 임시 노드 포인터
Node* ptr = NULL; // 현재 노드를 가리키는 포인터

void print_list(Node* A) {
    ptr = A;
    printf("[현재 리스트] Head -> ");
    while (ptr != NULL) {
        printf("%d -> ", ptr->data);
        ptr = ptr->next;
    }
    printf("Null\n\n");
}

void push(Node** first, int data) {
    temp = (Node*)malloc(sizeof(Node)); // 새로운 노드 동적 할당
    temp->data = data; // 데이터 저장
    temp->next = *first; // 새로운 노드의 다음 노드를 현재 리스트의 시작 노드로 설정
    *first = temp; // 리스트의 시작 노드를 새로운 노드로 업데이트
}

int pop(Node** first) {
    if (*first == NULL) {
        return ERROR; // 리스트가 비어있음
    }
    temp = *first;
    int data = temp->data;
    *first = (*first)->next;
    free(temp);
    return data;
}

int main() {
    int select; int data; int result;
    while (1) {
        printf("[ 1. push / 2. pop / -1. exit ] ");
        printf("수행할 기능 >> "); scanf("%d", &select);
        switch (select) {
        case 1: // push
            printf("Push할 데이터 >> "); scanf("%d", &data);
            push(&A, data);
            print_list(A);
            break;
		case 2: // pop
            data = pop(&A);
            if (data != ERROR) printf("Pop한 데이터 >> %d\n", data);
            else printf("스택이 비어 있습니다.\n");
            print_list(A);
            break;
		case -1: // exit
            return 0;
        default: printf("잘못된 선택입니다.\n");
        }
    }
}