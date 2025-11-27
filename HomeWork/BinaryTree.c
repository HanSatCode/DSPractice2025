#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct node {
	char data;	// 노드의 데이터 필드
	struct node* leftChild;	// 왼쪽 자식 노드 포인터
	struct node* rightChild; // 오른쪽 자식 노드 포인터
} Node;

int nodeCount = 0;	// 노드의 개수를 세기 위한 전역 변수
int leafCount = 0;	// 리프 노드의 개수를 세기 위한 전역 변수
int level = 0;		// 현재 레벨을 기록하기 위한 전역 변수
int maxLevel = 0;	// 트리의 최대 레벨을 기록하기 위한 전역 변수

typedef Node* NodePointer;	// 노드 포인터

void generateTree(NodePointer, int, int);	// 임의의 트리를 생성하는 메소드
void createTree(NodePointer);	// 그림과 같은 트리를 생성하는 메소드
void preorder(NodePointer);		// 전위 순환을 하는 메소드
void inorder(NodePointer);		// 중위 순환을 하는 메소드
void postorder(NodePointer);	// 후위 순환을 하는 메소드

void travelTree(NodePointer node) {	// DFS 방식으로 트리를 순회합니다. (재귀 사용)
	if (node != NULL) {	// 방문한 노드가 NULL이 아닐 경우에만 진행합니다. (없는 노드이기 때문)
		nodeCount++; // 노드 카운트를 증가시킵니다. (전위 순회에서 노드 방문시 바로 출력하는 것과 같음)
		level++;	// 레벨 카운트를 증가시킵니다. (전위 순회처럼, 자식 노드를 방문하였으면 증가합니다.)
		if (level > maxLevel) maxLevel = level;	// 만약에 현재 레벨이 지금까지 살펴봤던 레벨보다 클 경우에는 최대 레벨을 현재의 레벨로 갱신합니다.
		if (node->leftChild == NULL && node->rightChild == NULL) {
			leafCount++; // 현재 노드의 왼쪽 자식 및 오른쪽 자식이 없는 경우, 즉 리프 노드인 경우 리프 카운트를 증가시킵니다.
		}
		travelTree(node->leftChild);	// 왼쪽 자식 노드를 재귀적으로 방문합니다.
		travelTree(node->rightChild);	// 오른쪽 자식 노드를 재귀적으로 방문합니다.
		level--;	// 해당 노드의 자식 방문이 끝나고 부모 노드 쪽(위로)으로 빠져 나가는 경우, 현재 레벨을 감소시킵니다.
	}
}

int main(void) {
	printf("[1. 임의의 이진 트리의 노드 갯수, 높이, 리프 노드 개수를 구하기]\n");
	NodePointer root = (NodePointer)malloc(sizeof(Node));	// 루트 노드를 동적 할당합니다.
	srand(time(NULL)); // 현재 시간을 시드로 사용하여 난수 생성기 초기화합니다.
	int value = rand() % 10 + 3; // 트리의 노드 갯수를 임의로 선택합니다.
	root->data = 'A'; root->leftChild = NULL; root->rightChild = NULL; // 처음에 트리의 루트를 생성합니다.
	generateTree(root, 2, value);

	printf("임의 트리의 전위 순환 : "); preorder(root); printf("\n");	// 트리의 전위 순환을 실시합니다.
	printf("임의 트리의 중위 순환 : "); inorder(root); printf("\n");	// 트리의 중위 순환을 실시합니다.
	printf("임의 트리의 후위 순환 : "); postorder(root); printf("\n");	// 트리의 후위 순환을 실시합니다.

	travelTree(root);	// 임의의 트리 트레블을 시작합니다.
	// 높이는 최대 레벨의 -1 한 값과 같으므로, maxLevel에서 1을 뺀 값을 출력합니다.
	printf("노드의 개수 : %d | 트리의 높이 : %d | 트리의 리프 노드 개수 : %d\n", nodeCount, maxLevel - 1, leafCount);

	// --------------------------------------------------------------------------------
	nodeCount = maxLevel = leafCount = 0;	// 새로운 트리를 계산하기 위해 값을 초기화합니다.

	printf("\n[2. 그림에 나와있는 트리를 이용하여 트리의 높이를 계산]\n");
	root = (NodePointer)malloc(sizeof(Node));	// 루트 노드를 동적 할당합니다.
	createTree(root);	// 트리를 그림과 같이 생성합니다.
	travelTree(root);	// 트리 트레블을 시작합니다.
	// 높이는 최대 레벨의 -1 한 값과 같으므로, maxLevel에서 1을 뺀 값을 출력합니다.
	printf("노드의 개수 : %d | 트리의 높이 : %d | 트리의 리프 노드 개수 : %d\n", nodeCount, maxLevel - 1, leafCount);

}


void createTree(NodePointer root) {
	root->data = 'A';	// 루트 노드에 데이터 'A'를 저장합니다.
	NodePointer nodeB = (NodePointer)malloc(sizeof(Node));	// 노드 B를 동적 할당합니다.
	nodeB->data = 'B';	// 노드 B에 데이터 'B'를 저장합니다.
	root->leftChild = nodeB;	// 루트 노드의 왼쪽 자식으로 노드 B를 연결합니다.
	NodePointer nodeC = (NodePointer)malloc(sizeof(Node));	// 노드 C를 동적 할당합니다.
	nodeC->data = 'C';	// 노드 C에 데이터 'C'를 저장합니다.
	root->rightChild = nodeC; nodeC->leftChild = NULL; // 루트 노드의 오른쪽 자식으로 노드 C를 연결합니다.
	NodePointer nodeD = (NodePointer)malloc(sizeof(Node));	// 노드 D를 동적 할당합니다.
	nodeD->data = 'D';	// 노드 D에 데이터 'D'를 저장합니다.
	nodeB->leftChild = nodeD; nodeD->leftChild = NULL; nodeD->rightChild = NULL;	// 노드 B의 왼쪽 자식으로 노드 D를 연결합니다.
	NodePointer nodeE = (NodePointer)malloc(sizeof(Node));	// 노드 E를 동적 할당합니다.
	nodeE->data = 'E';	// 노드 E에 데이터 'E'를 저장합니다.
	nodeB->rightChild = nodeE; nodeE->rightChild = NULL; // 노드 B의 오른쪽 자식으로 노드 E를 연결합니다.
	NodePointer nodeF = (NodePointer)malloc(sizeof(Node));	// 노드 F를 동적 할당합니다.
	nodeF->data = 'F';	// 노드 F에 데이터 'F'를 저장합니다.
	nodeC->rightChild = nodeF; nodeF->leftChild = NULL; nodeF->rightChild = NULL;	// 노드 C의 오른쪽 자식으로 노드 F를 연결합니다.
	NodePointer nodeG = (NodePointer)malloc(sizeof(Node));	// 노드 G를 동적 할당합니다.
	nodeG->data = 'G';	// 노드 G에 데이터 'G'를 저장합니다.
	nodeE->leftChild = nodeG; nodeG->leftChild = NULL; nodeG->rightChild = NULL; // 노드 E의 왼쪽 자식으로 노드 G를 연결합니다.
}

void generateTree(NodePointer root, int cur, int max) {
	NodePointer temp;	// 새 노드의 원형을 선언합니다.
	while (cur <= max) {	// max값에 도달할 때까지 노드 생성 및 붙이기를 반복합니다.
		NodePointer curNode = root;		// 트리를 만들 때, 항상 루트부터 내려가도록 합니다.
		temp = (NodePointer) malloc (sizeof(Node));	// 새로운 노드를 생성합니다. (현재값, 자식 노드는 모두 NULL)
		temp->data = 'A' + (cur - 1); temp->leftChild = NULL; temp->rightChild = NULL;
		while (1) { // 자리가 빌 때까지 (NULL) 루트부터 내려오며 탐색합니다.
			int binary = rand() % 2;	// 내려갈 방향을 왼쪽, 오른쪽 중에 무작위로 선택합니다.
			if (binary) { // 왼쪽으로 내려갑니다.
				if (curNode->leftChild == NULL) {	// 만약에 자리가 빌 경우 (자식이 NULL일 경우)
					curNode->leftChild = temp;	// 위에서 새로 만든 노드를 붙입니다.
					break;	// 다음 노드 추가 작업을 하러 이동합니다.
				}
				curNode = curNode->leftChild;	// 왼쪽 자리가 있을 경우 (자식이 있을 경우)에는 그 자식의 노드로 이동합니다.
			}
			else { // 오른쪽으로 내려갑니다.
				if (curNode->rightChild == NULL) {	// 만약에 자리가 빌 경우 (자식이 NULL일 경우)
					curNode->rightChild = temp;	// 위에서 새로 만든 노드를 붙입니다.
					break;	// 다음 노드 추가 작업을 하러 이동합니다.
				}
				curNode = curNode->rightChild;	// 오른쪽 자리가 있을 경우 (자식이 있을 경우)에는 그 자식의 노드로 이동합니다.
			}
		}
		cur++;	// 다음 노드의 데이터를 위해 cur 값을 1 증가합니다.
	}
}

void preorder(NodePointer node) {	// VLR
	if (node != NULL) {		// NULL을 만날 때까지 재귀 방식으로 방문
		printf("%c ", node->data);		// 노드 방문
		preorder(node->leftChild);		// 왼쪽 서브트리 방문
		preorder(node->rightChild);		// 오른쪽 서브트리 방문
	}
}

void inorder(NodePointer node) { // LVR
	if (node != NULL) {		// NULL을 만날 때까지 재귀 방식으로 방문
		inorder(node->leftChild);	// 왼쪽 서브트리 방문
		printf("%c ", node->data);	// 노드 방문
		inorder(node->rightChild);	// 오른쪽 서브트리 방문
	}
}

void postorder(NodePointer node) {	// LRV
	if (node != NULL) {		// NULL을 만날 때까지 재귀 방식으로 방문
		postorder(node->leftChild);		// 왼쪽 서브트리 방문
		postorder(node->rightChild);	// 오른쪽 서브트리 방문
		printf("%c ", node->data);		// 노드 방문
	}
}