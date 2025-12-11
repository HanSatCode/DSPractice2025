#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
} Node;

// 신장 트리란? 사이클을 끊어낸 그래프. (트리 모양)

Node* graph = NULL;	// 그래프 인접 리스트 (배열로 구현)

int* visited; // 방문 여부 확인 배열
int* queue;	// 큐 배열
void dfs(int);	// 깊이 우선 탐색
void bfs(int);	// 너비 우선 탐색
void dfsWithSpanningTree(int);	// 깊이 우선 탐색 신장 트리
void bfsWithSpanningTree(int);	// 너비 우선 탐색	신장 트리


void addq(int, int*, int*);	// 큐에 원소 추가
int deleteq(int*, int*);	// 큐에서 원소 삭제

int main(void) {
	int nodeCnt, i, j;
	printf("[1-1. 인접 리스트 형태의 무방향성 그래프 생성]\n");
	printf("노드의 갯수 >> "); scanf("%d", &nodeCnt);
	graph = (Node*) calloc (nodeCnt, sizeof(Node));	// 인접 리스트 공간을 할당
	visited = (int*) calloc (nodeCnt, sizeof(int));	// 방문 여부 확인 배열 공간 할당
	for (int i = 0; i < nodeCnt; visited[i++] = 0);
	for (int i = 0; i < nodeCnt; graph[i].data = i, graph[i].next = NULL, i++);	// 배열 초기화

	while (1) {
		printf("엣지 정보 (vi vj) >> "); scanf("%d %d", &i, &j);
		if (i == -1 && j == -1) break;
		Node* temp1 = (Node*)malloc(sizeof(Node)); temp1->data = j; temp1->next = graph[i].next; // i -> j (무방향성)
		Node* temp2 = (Node*)malloc(sizeof(Node)); temp2->data = i; temp2->next = graph[j].next; // j -> i (무방향성)
		graph[i].next = temp1; graph[j].next = temp2;
	}

	printf("\n[1-2. 인접 리스트를 이용한 그래프]\n");
	int degreeMaxCnt = 0; int degreeMaxNode = 0;
	for (int i = 0; i < nodeCnt; i++) {
		int degreeCnt = 0;
		Node* curNode = graph[i].next;
		printf("[%d] : ", i);
		while (curNode != NULL) {
			printf("%d -> ", curNode->data);
			curNode = curNode->next;
			degreeCnt++;
		}
		if (degreeCnt > degreeMaxCnt) {
			degreeMaxCnt = degreeCnt;
			degreeMaxNode = i;
		}
		printf("end\n");
	}

	printf("\n[1-3. degree가 가장 큰 노드와 degree 값\n");
	printf("노드 번호 : %d | dgree 값 : %d | ", degreeMaxNode, degreeMaxCnt);
	Node* curNode = graph[degreeMaxNode].next;
	while (curNode != NULL) {
		printf("%d -> ", curNode->data);
		curNode = curNode->next;
	}
	printf("end\n");

	printf("\n[2-1. 깊이 우선 탐색 (DFS)]\n");
	printf("시작 노드 0 : "); dfs(0); printf("\n"); for (int i = 0; i < nodeCnt; visited[i++] = 0);
	printf("시작 노드 2 : "); dfs(2);	 printf("\n"); for (int i = 0; i < nodeCnt; visited[i++] = 0);
	printf("시작 노드 4 : "); dfs(4);	 printf("\n"); for (int i = 0; i < nodeCnt; visited[i++] = 0);


	printf("\n[2-2. 너비 우선 탐색 (BFS)]\n");
	queue = (int*) malloc (100 * sizeof(int));	// 큐 배열 공간 할당
	printf("시작 노드 1 : "); bfs(1); printf("\n"); for (int i = 0; i < nodeCnt; visited[i++] = 0);
	printf("시작 노드 3 : "); bfs(3); printf("\n"); for (int i = 0; i < nodeCnt; visited[i++] = 0);
	printf("시작 노드 5 : "); bfs(5); printf("\n"); for (int i = 0; i < nodeCnt; visited[i++] = 0);

	printf("\n[3-1. DFS 신장 트리]\n");
	printf("시작 노드 0 : "); dfsWithSpanningTree(0); printf("\n"); for (int i = 0; i < nodeCnt; visited[i++] = 0);
	printf("시작 노드 2 : "); dfsWithSpanningTree(2); printf("\n"); for (int i = 0; i < nodeCnt; visited[i++] = 0);
	printf("시작 노드 4 : "); dfsWithSpanningTree(4); printf("\n"); for (int i = 0; i < nodeCnt; visited[i++] = 0);
	
	printf("\n[3-2. BFS 신장 트리]\n");
	printf("시작 노드 1 : "); bfsWithSpanningTree(1); printf("\n"); for (int i = 0; i < nodeCnt; visited[i++] = 0);
	printf("시작 노드 3 : "); bfsWithSpanningTree(3); printf("\n"); for (int i = 0; i < nodeCnt; visited[i++] = 0);
	printf("시작 노드 5 : "); bfsWithSpanningTree(5); printf("\n");
}

void dfs(int v) {
	visited[v] = 1; printf("%d ", v);
	for (Node* w = graph[v].next; w != NULL; w = w->next) {
		if (!visited[w->data]) dfs(w->data);
	}
}

void bfs(int v) {
	int front = 0, rear = 0;
	visited[v] = 1; printf("%d ", v);
	addq(v, &front, &rear);
	while (front != rear) {
		v = deleteq(&front, &rear);
		for (Node* w = graph[v].next; w != NULL; w = w->next) {
			if (!visited[w->data]) {
				printf("%d ", w->data);
				addq(w->data, &front, &rear);
				visited[w->data] = 1;
			}
		}
	}
}

void addq(int value, int* front, int* rear) {
	queue[(*rear)++] = value;
}

int deleteq(int* front, int* rear) {
	return queue[(*front)++];
}


void dfsWithSpanningTree(int v) {
	visited[v] = 1;
	for (Node* w = graph[v].next; w != NULL; w = w->next) {
		if (!visited[w->data]) {
			printf("(%d, %d) ", v, w->data); // 신장 트리 엣지 출력
			dfsWithSpanningTree(w->data);
		}
	}
}

void bfsWithSpanningTree(int v) {
	int front = 0, rear = 0;
	visited[v] = 1;
	addq(v, &front, &rear);
	while (front != rear) {
		v = deleteq(&front, &rear);
		for (Node* w = graph[v].next; w != NULL; w = w->next) {
			if (!visited[w->data]) {
				printf("(%d, %d) ", v, w->data);
				addq(w->data, &front, &rear);
				visited[w->data] = 1;
			}
		}
	}
}