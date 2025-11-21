#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
	if(!((p) = malloc(s))) {\
		fprintf(stderr, "메모리가 충분하지 않습니다!");\
		exit(EXIT_FAILURE);\
	}

// [베이스] --------------------------------------------------------

typedef struct node {
	int data; // 실제 데이터
	struct node* lchild; // 왼쪽 자식
	struct node* rchild; // 오른쪽 자식
} Node;

typedef Node* treePointer;	// 노드 구조체를 가리키는 포인터 타입

void inorder(treePointer);

// [트리 생성] --------------------------------------------------------

treePointer make_tree_by_code() {
	treePointer root = (treePointer) malloc (sizeof(Node)); // 루트 노드
	treePointer lchild = (treePointer) malloc (sizeof(Node)); // 왼쪽 자식 노드
	treePointer rchild = (treePointer) malloc (sizeof(Node)); // 오른쪽 자식 노드
	treePointer llchild = (treePointer) malloc (sizeof(Node)); // 왼쪽-왼쪽 자식 노드
	treePointer lrchild = (treePointer) malloc (sizeof(Node)); // 왼쪽-오른쪽 자식 노드

	root->data = 5; lchild->data = 3; rchild->data = 8; llchild->data = 1; lrchild->data = 4;
	root->lchild = lchild; root->rchild = rchild;
	lchild->lchild = llchild; lchild->rchild = lrchild;
	llchild->lchild = NULL; llchild->rchild = NULL;
	lrchild->lchild = NULL; lrchild->rchild = NULL;
	rchild->lchild = NULL; rchild->rchild = NULL;

	return root;
}

// [트리 일치 검사] --------------------------------------------------------

int equal(treePointer first, treePointer second) {
	return ((!first && !second) || (first && second &&
		(first->data == second->data) &&
		equal(first->lchild, second->lchild) &&
		equal(first->rchild, second->rchild)));
}

// [트리 복사] --------------------------------------------------------

treePointer copy(treePointer original) {
	treePointer temp;
	if (original) {
		MALLOC(temp, sizeof(*temp));
		temp->lchild = copy(original->lchild);
		temp->rchild = copy(original->rchild);
		temp->data = original->data;
		return temp;
	}
	return NULL;
}

// [트리 스왑] --------------------------------------------------------

treePointer swap(treePointer original) {
	treePointer temp;
	if (original) {
		MALLOC(temp, sizeof(*temp));
		temp->lchild = swap(original->rchild);
		temp->rchild = swap(original->lchild);
		temp->data = original->data;
		return temp;
	}
	return NULL;
}

// [랜덤 트리 제작] --------------------------------------------------------
void generate(treePointer* root, int cur, int max) { // 알고리즘 최적화 필요
	// 넣는 노드가 데이터가 n보다 작거나 같을 때까지 반복
	treePointer curNode = *root;
	treePointer temp;
	while (cur <= max) {					// 2부터 max까지 반복을 하는데, 늘 루트부터 시작을 함
		int binary = rand() % 2;
		if (binary) { // 왼쪽
			while (1) {
				binary = rand() % 2;
				if (binary) { // 왼쪽
					if (curNode->lchild == NULL) {
						temp = (treePointer)malloc(sizeof(Node));
						temp->data = cur++; temp->lchild = NULL; temp->rchild = NULL;
						curNode->lchild = temp; // 노드 연결
						break;
					}
					curNode = curNode->lchild;	// 그 노드의 왼쪽 자식으로 이동
				}
				else {
					if (curNode->rchild == NULL) {
						temp = (treePointer)malloc(sizeof(Node));
						temp->data = cur++; temp->lchild = NULL; temp->rchild = NULL;
						curNode->rchild = temp; // 노드 연결
						break;
					}
					curNode = curNode->rchild;	// 그 노드의 오른쪽 자식으로 이동
				}
			}
		}
		else { // 오른쪽
			while (1) {	// 자식이 없을 때까지 때까지 반복함
				binary = rand() % 2; // 왼쪽 오른쪽 선택하기
				if (binary) { // 왼쪽
					if (curNode->lchild == NULL) {
						temp = (treePointer)malloc(sizeof(Node));
						temp->data = cur++; temp->lchild = NULL; temp->rchild = NULL;
						curNode->lchild = temp; // 노드 연결
						break;
					}
					curNode = curNode->lchild;	// 그 노드의 왼쪽 자식으로 이동
				}
				else {
					if (curNode->rchild == NULL) {
						temp = (treePointer)malloc(sizeof(Node));
						temp->data = cur++; temp->lchild = NULL; temp->rchild = NULL;
						curNode->rchild = temp; // 노드 연결
						break;
					}
					curNode = curNode->rchild;	// 그 노드의 오른쪽 자식으로 이동
				}
			}
		}
	}
}

// [순회 알고리즘] --------------------------------------------------------

void inorder(treePointer node) {
	if (node != NULL) {
		inorder(node->lchild);		// 왼쪽 서브트리 방문
		printf("%d ", node->data);	// 노드 방문
		inorder(node->rchild);		// 오른쪽 서브트리 방문
	}
}

void preorder(treePointer node) {
	if (node != NULL) {
		printf("%d ", node->data);	// 노드 방문
		preorder(node->lchild);		// 왼쪽 서브트리 방문
		preorder(node->rchild);		// 오른쪽 서브트리 방문
	}
}

void postorder(treePointer node) {
	if (node != NULL) {
		postorder(node->lchild);	// 왼쪽 서브트리 방문
		postorder(node->rchild);	// 오른쪽 서브트리 방문
		printf("%d ", node->data);	// 노드 방문
	}
}

// [메인 부] --------------------------------------------------------

int main(void) {
	printf("[1. A 트리 생성하기]\n"); treePointer A = make_tree_by_code();
	printf("Inorder A : "); inorder(A); printf("\n"); // LVR
	printf("Preorder A : "); preorder(A); printf("\n"); // VLR
	printf("Postorder A : "); postorder(A); printf("\n"); // LRV

	printf("\n[2-1. A 트리를 B 트리로 복사하기]\n"); treePointer B = copy(A);
	printf("Inorder B : "); inorder(B); printf("\n"); // LVR
	printf("Preorder B : "); preorder(B); printf("\n"); // VLR
	printf("Postorder B : "); postorder(B); printf("\n"); // LRV

	printf("\n[2-2. A 트리와 B 트리가 같은지 검사하기]\n"); int checker = equal(A, B);
	if (checker) { printf("TRUE (A 트리와 B 트리가 같습니다)\n"); }
	else { printf("FALSE (A 트리와 B 트리가 서로 다릅니다)\n"); }

	printf("\n[2-3. A 트리를 스왑하여 C 트리 만들기]\n"); treePointer C = swap(A);
	printf("Inorder C : "); inorder(C); printf("\n"); // LVR
	printf("Preorder C : "); preorder(C); printf("\n"); // VLR
	printf("Postorder C : "); postorder(C); printf("\n"); // LRV

	printf("\n[2-2. A 트리와 C 트리가 같은지 검사하기]\n"); checker = equal(A, C);
	if (checker) { printf("TRUE (A 트리와 B 트리가 같습니다)\n"); }
	else { printf("FALSE (A 트리와 C 트리가 서로 다릅니다)\n"); }

	printf("\n[3-1. 1부터 N까지의 숫자로 랜덤 트리 만들기]\n");
	printf("숫자를 입력하세요 : "); int n; scanf("%d", &n);
	treePointer R = (treePointer)malloc(sizeof(Node)); 
	R->data = 1; R->lchild = NULL; R->rchild = NULL; generate(&R, 2, n);
	printf("Inorder generated tree : "); inorder(R); printf("\n"); // LVR
	printf("Preorder generated tree : "); preorder(R); printf("\n"); // VLR
	//printf("Postorder generated tree : "); postorder(R); printf("\n"); // VLR
}