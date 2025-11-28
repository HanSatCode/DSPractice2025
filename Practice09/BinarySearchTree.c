#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int key;
	double value;
	struct node* lchild;
	struct node* rchild;
} Node;

typedef Node* treePointer;

treePointer tree = NULL;
void insert(treePointer, int);
void inorder(treePointer);
void search(treePointer, int, int);
treePointer modified_search(treePointer, int);	// 넣을 자리의 부모를 반환
treePointer make_bst(int, double*);

int count_node(treePointer);
int count_depth(treePointer ptr);
int count_leaf(treePointer ptr);

void travelTree(treePointer, int*, int*, int*, int*);

int main(void) {
	int a; double duration;
	int data[12] = { 10, 6, 15, 8, 18, 12, 3, 14, 9, 20, 5, 2 };

	printf("[1-1. 12개의 (key, value) 쌍을 생성하여 이진 탐색 트리 생성]\n");
	for (int i = 0; i < 12; insert(&tree, data[i++]));
	printf("성공적으로 노드 추가를 완료하였습니다!\n");

	printf("\n[1-2. inorder 알고리즘으로 생성된 이진 탐색 트리를 출력]\n");
	inorder(tree);

	printf("\n[2. 생성된 이진 검색 트리에서 key값을 활용한 검색]\n");
	while (1) {
		printf("검색할 key값을 입력하세요 (종료: -1) : "); scanf("%d", &a);
		if (a == -1) break;
		search(tree, a, 1);
	}

	printf("\n[3. 이진 검색 트리 생성 ]\n");
	while (1) {
		printf("n 값을 입력하세요. (종료: -1) : "); scanf("%d", &a);
		if (a == -1) break;
		treePointer B = make_bst(a, &duration);
		int nodeCount = count_node(B); int leafCount = count_leaf(B); int depth = count_depth(B);
		printf("이진 검색 트리의 생성 시간 : %f\n", duration);
		printf("노드 수 : %d | 트리 높이 : %d | 단말 노드 수 : %d\n", nodeCount, depth, leafCount);
	}
}

treePointer modified_search(treePointer tree, int key) {
	treePointer parent = NULL;
	treePointer current = tree;

	while (current != NULL) {
		if (key == current->key) return NULL;	// 중복된 key값 발견 시 NULL 반환
		parent = current;
		if (key < current->key) current = current->lchild;	// 왼쪽 서치
		else if (key > current->key) current = current->rchild;	// 오른쪽 서치
	}
	return parent;
}

void insert(treePointer* tree, int key) {
	treePointer newNode, temp = modified_search(*tree, key);	// 삽입할 위치의 부모 노드

	if (temp || !(*tree)) {	// 트리가 비어있거나, 삽입할 위치의 부모 노드가 존재할 때
		newNode = (treePointer)malloc(sizeof(Node));
		newNode->key = key; newNode->value = 1.0 / key;
		newNode->lchild = NULL; newNode->rchild = NULL;

		if (*tree) {	// 트리가 비어있지 않을 때
			if (key < temp->key) temp->lchild = newNode;	// 왼쪽 자식으로 삽입
			else temp->rchild = newNode;	// 오른쪽 자식으로 삽입
		}
		else {	// 트리가 비어있을 때
			*tree = newNode;
		}
	}
}

void inorder(treePointer tree) {	// LVR
	if (tree != NULL) {
		inorder(tree->lchild);
		printf("Key : %d | Value : %f\n", tree->key, tree->value);
		inorder(tree->rchild);
	}
}

void search(treePointer tree, int key, int cnt) {
	if (tree == NULL) {
		printf("△ 검색 실패 - key : %d (을)를 찾지 못하였습니다.\n"); return;
	}
	if (tree != NULL) {
		if (key < tree->key) search(tree->lchild, key, ++cnt);	// 왼쪽 서치
		else if (key > tree->key) search(tree->rchild, key, ++cnt);	// 오른쪽 서치
		else {
			printf("♥ 검색 성공 - key : %d | value : %f | count : %d\n", key, tree->value, cnt);
			return;
		}
	}
}

treePointer make_bst(int count, double* duration) {
	clock_t start = clock();
	treePointer myTree = NULL;
	for (int i = 0; i < count; i++) {
		
		int key = (rand() / (0x7ffff * 1.0)) * 100000000;
		insert(&myTree, key);
	}
	*duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
	return myTree;
}

void travelTree(treePointer node, int* nodeCount, int* leafCount, int* level, int* maxLevel) {
	if (node != NULL) {
		(*nodeCount)++; (*level)++;
		if (*level > *maxLevel) *maxLevel = *level;	
		if (node->lchild == NULL && node->rchild == NULL) {
			(*leafCount)++;
		}
		travelTree(node->lchild, nodeCount, leafCount, level, maxLevel);
		//printf("Key : %d | value : %f\n", node->key, node->value);
		travelTree(node->rchild, nodeCount, leafCount, level, maxLevel);
		(*level)--;
	}
}

int count_node(treePointer ptr) {
	if (ptr == NULL) return 0;
	else return 1 + count_node(ptr->lchild) + count_node(ptr->rchild);
}

int count_depth(treePointer ptr) {
	if (ptr == NULL) return 0;	// 빈 트리의 깊이는 0
	else {
		int leftDepth = count_depth(ptr->lchild);
		int rightDepth = count_depth(ptr->rchild);
		if (leftDepth > rightDepth) return leftDepth + 1;
		else return rightDepth + 1;
	}
}

int count_leaf(treePointer ptr) {
	if (ptr == NULL) return 0;	// 빈 트리는 단말 노드가 없음!
	if (ptr->lchild == NULL && ptr->rchild == NULL) return 1;	// 단말 노드 발견
	else return count_leaf(ptr->lchild) + count_leaf(ptr->rchild);
}