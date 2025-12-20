#include <stdio.h>
#include <stdlib.h>
#define NONEDGE 1000

typedef struct node {
	int node;
	int weight;
	struct node* next;
} Node;

typedef Node* nodePointer;

int v;
nodePointer* G;
int n;
int* distance;
int** allDistance; 
short int* found; // 최단거리 탐색에서 방문 정점 표시?
int* visited; // 방문 여부

void shortestPath(int v, nodePointer* G, int* distance, int n, short int* found);
void allCosts(nodePointer* G, int** allDistance, int n);

int main(void) {
	printf("정점의 수를 입력하세요 : "); scanf("%d", &n);
	G = (nodePointer*)malloc(n * sizeof(nodePointer));
	visited = (int*) malloc (n * sizeof(int));
	allDistance = (int**)malloc(n * sizeof(int*));

	for (int i = 0; i < n; i++) {
		visited[i] = 0;
		G[i] = NULL;
		allDistance[i] = (int*) malloc (n * sizeof(int));
		for (int j = 0; j < n; j++) {
			allDistance[i][j] = NONEDGE;
		}
	}

	int from, to, weight;
	while (1) {
		scanf("%d %d %d", &from, &to, &weight);
		if (from == -1 && to == -1 && weight == -1) break;
		nodePointer temp = (nodePointer)malloc(sizeof(nodePointer));
		temp->node = to;
		temp->weight = weight;
		temp->next = G[from];
		G[from] = temp;
	}
	
	
	printf("시작 정점 : "); scanf("%d", &v);
	distance = (int*)malloc(n * sizeof(int));
	found = (int*)malloc(n * sizeof(int));
	shortestPath(v, G, distance, n, found);
	printf("가장 짧은 거리 (정점 # %d) >> ", v);
	for (int j = 0; j < n; printf("%d ", distance[j++]));
	printf("\n\n모든 거리에서의 올 코스트\n");
	allCosts(G, allDistance, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) printf("%d ", 0);
			else printf("%d ", allDistance[i][j]);
		}
		printf("\n");
	}

}

int choose(int distance[], int n, short int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void shortestPath(int v, nodePointer* G, int* distance, int n, short int* found) {
	int i, u, w;

	for (i = 0; i < n; i++) {
		found[i] = 0;
		distance[i] = NONEDGE;
	}

	for (nodePointer cur = G[v]; cur != NULL; cur = cur->next) { // 인접한것만 초기화하기.
		distance[cur->node] = cur->weight;
	}
	
	found[v] = 1; // 처음에 방문 처리!
	distance[v] = 0;

	for (i = 0; i < n - 2; i++) {
		u = choose(distance, n, found); // 가장 작은것 선택하기.
		found[u] = 1;
		for (nodePointer cur = G[u]; cur != NULL; cur = cur->next) { // cur != NULL 써야함... 이거 못알아채서 삽질 1시간??
			if (!found[cur->node]) // 다음 노드를 방문하지 않았다면...
				if (distance[u] + cur->weight < distance[cur->node])
					distance[cur->node] = distance[u] + cur->weight;
		}
	}
	
}

void allCosts(nodePointer* G, int** distance, int n) {
	int i, j, k;

	for (i = 0; i < n; i++) {
		for (nodePointer cur = G[i]; cur != NULL; cur = cur->next) {
			// 인접한것만 초기화하기.
			allDistance[i][cur->node] = cur->weight;
		}
	}

	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (allDistance[i][k] + allDistance[k][j] < allDistance[i][j])
					allDistance[i][j] = allDistance[i][k] + allDistance[k][j];
					
}