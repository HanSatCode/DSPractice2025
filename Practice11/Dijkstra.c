#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 99999 // 간선이 없음을 나타내는 값

int** G;	// 2차원 인접 행렬
int n; // 노드 수
int* distance; short int* found;
int** allDistances;

// 크루스칼 알고리즘은 그래프의 모든 정보를 안다는 가정 하에 동작함
// -> 가장 작은 간선부터 계속 선택하고... 사이클이 생기지 않도록 선택 -> 모든 노드가 연결될 때까지 반복 (n-1개의 간선 선택)

// 프림 알고리즘은 첫 노드에서 시작하여 점차 트리를 확장해 나가는 방식이므로, 인접 리스트로 그래프를 표현
// -> 첫 노드에서 시작하여 가장 작은 간선을 선택 -> 선택된 간선의 도착 노드에서부터 다시 가장 작은 간선을 선택 -> 모든 노드가 연결될 때까지 반복 (n-1개의 간선 선택)

// 디젝스트라 알고리즘은 한 노드에서 다른 모든 노드로의 최단 경로를 찾는 방식임
// -> 시작 노드에서부터 가장 가까운 노드를 선택 -> 선택된 노드를 경유지로 하여 다른 노드들까지의 최단 경로를 갱신 -> 모든 노드에 대해 반복

void shortestPath(int v, int **cost, int distance[], int n, short int found[]) {
	int i, u, w;
	for (i = 0; i < n; i++) {
		found[i] = 0;
		distance[i] = cost[v][i];
	}
	found[v] = 1;
	distance[v] = 0;
	for (i = 0; i < n - 2; i++) {
		u = choose(distance, n, found);
		found[u] = 1;
		for (w = 0; w < n; w++) {
			if (!found[w])
				if (distance[u] + cost[u][w] < distance[w])
					distance[w] = distance[u] + cost[u][w];
		}
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

void allCosts(int **cost, int **distance, int n) {
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			distance[i][j] = cost[i][j];
	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (distance[i][k] + distance[k][j] < distance[i][j])
					distance[i][j] = distance[i][k] + distance[k][j];
}

int main(void) {
	printf("[1-1. 인접 행렬 형태의 방향성 그래프 생성]\n노드 수를 입력해주세요. >> "); scanf("%d", &n); 
	G = (int**) malloc (n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		G[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++) {
			if (i == j) G[i][j] = 0;	// 자기 자신으로의 가중치는 0
			else G[i][j] = MAX_VERTICES;	// 노드가 없음으로 초기화
		}
	}

	printf("엣지 정보를 (From, To, Weight) 형식으로 입력해주세요. (종료 : -1 -1 -1)\n"); int from, to, weight;
	while (1) {
		printf("엣지 정보 >> "); scanf("%d %d %d", &from, &to, &weight);
		if (from == -1 && to == -1 && weight == -1) break;
		G[from][to] = weight;	// 방향성 그래프이므로 한 방향으로만 값 할당
	}
	printf("\n[1-2. 인접 행렬을 이용한 그래프의 구성]\n       ");
	for (int i = 0; i < n; printf(" [%3d]", i++)); printf("\n");
	for (int i = 0; i < n; i++) {
		printf("[%5d] ", i);
		for (int j = 0; j < n; j++) {
			printf("%5d ", G[i][j]);
		}
		printf("\n");
	}

	printf("\n[2. 최단 경로 (단일 출발점)]\n"); int startNode = 0;
	distance = (int*) malloc (n * sizeof(int));
	found = (short int*) malloc (n * sizeof(short int));
	while (1) {
		printf("시작 노드 (v) >> "); scanf("%d", &startNode);
		if (startNode == -1) break;
		if (startNode >= 0 && startNode < n) {
			shortestPath(startNode, G, distance, n, found);
			printf("Distance : ");
			for (int j = 0; j < n; printf("%5d ", distance[j++]));
			printf("\n");
		}
	}

	printf("\n[3. 최단 경로 (모든 경로)]\n");
	allDistances = (int**) malloc (n * sizeof(int*));
	for (int i = 0; i < n; allDistances[i++] = (int*)malloc(n * sizeof(int)));
	allCosts(G, allDistances, n);
	printf("All Path Distance : \n       ");
	for (int i = 0; i < n; printf(" [%3d]", i++)); printf("\n");
	for (int i = 0; i < n; i++) {
		printf("[%5d] ", i);
		for (int j = 0; j < n; j++) {
			printf("%5d ", allDistances[i][j]);
		}
		printf("\n");
	}
}