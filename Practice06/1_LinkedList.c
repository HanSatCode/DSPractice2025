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

void insert_front(Node** first, int data) {
    temp = (Node*)malloc(sizeof(Node)); // 새로운 노드 동적 할당
    temp->data = data; // 데이터 저장
    temp->next = *first; // 새로운 노드의 다음 노드를 현재 리스트의 시작 노드로 설정
    *first = temp; // 리스트의 시작 노드를 새로운 노드로 업데이트
}

void print_list(Node* A) {
    ptr = A;
    printf("[리스트] Head -> ");
    while (ptr != NULL) {
        printf("%d -> ", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n\n");
}

void insert_last(Node** first, int data) {
    temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    if (*first == NULL) {
        *first = temp;
        return;
    }
    ptr = *first;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = temp;
}

int search(Node* A, int data) {
    ptr = A;
	int position = 0;
    while (ptr != NULL) {
        if (ptr->data == data) {
            return position;
        }
        ptr = ptr->next;
        position++;
    }
    return ERROR; // 데이터 미발견
}

int delete_front(Node** first) {
    if (*first == NULL) {
        return ERROR; // 리스트가 비어있음
    }
    temp = *first;
    int data = temp->data;
    *first = (*first)->next;
    free(temp);
    return data;
}

int delete_(Node** first, int data) {
    if (*first == NULL) {
        return ERROR; // 리스트가 비어있음
    }
    if ((*first)->data == data) {
        return delete_front(first);
    }
    ptr = *first;
    while (ptr->next != NULL && ptr->next->data != data) {
        ptr = ptr->next;
    }
    if (ptr->next == NULL) {
        return ERROR;
    }
    temp = ptr->next;
    int deleted_data = temp->data;
    ptr->next = temp->next;
    free(temp);
    return deleted_data;
}

int main() {
    int select; int data; int result;
    while (1) {
        printf("0. print list\n"); printf("1. insert front\n");
        printf("2. insert last\n"); printf("3. delete front\n");
        printf("4. delete\n"); printf("5. search\n"); printf("-1. exit\n");
        printf("수행할 기능 >> "); scanf("%d", &select);
        switch (select) {
        case 0: print_list(A); break;
        case 1:
            printf("데이터 : "); scanf("%d", &data);
            insert_front(&A, data);
            print_list(A);
            break;
        case 2:
            printf("데이터 : "); scanf("%d", &data);
            insert_last(&A, data);
            print_list(A);
            break;
        case 3:
            result = delete_front(&A);
			printf("삭제된 데이터 : %d\n", result);
            print_list(A);
            break;
        case 4:
            printf("데이터 : "); scanf("%d", &data);
            result = delete_(&A, data);
			printf("삭제된 데이터 : %d\n", result);
            print_list(A);
            break;
        case 5:
            printf("데이터 : "); scanf("%d", &data);
            result = search(A, data);
			printf("위치 : %d\n", result);
            print_list(A);
            break;
        case -1:
            return 0;
        default:
            printf("잘못된 선택입니다.\n");
        }
    }
}