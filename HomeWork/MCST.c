#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100	// 노드 배열 크기를 충분히 늘림
#define MAX_EDGES 200	// 엣지 배열 크기를 충분히 늘림

typedef struct edge {
	int node1, node2; // 엣지의 두 끝점
	int weight; // 엣지의 가중치
} Edge;

int numNodes; 			// 입력받은 총 노드의 개수
int totalEdges = 0; 	// 입력받은 총 간선의 개수 (이후 변경되지 않음)
int heapSize = 0; 		// 현재 최소 힙에 들어있는 간선의 개수
int parent[MAX_NODES]; 	// union-find 부모 배열

Edge edges[MAX_EDGES]; 	// 입력된 모든 엣지 배열
Edge minHeap[MAX_EDGES + 1]; // 최소 힙 배열 (1부터 시작)

int mstEdgesCount = 0; // 실제로 MST에 포함된 간선의 개수
Edge mstEdges[MAX_NODES - 1]; // MST 간선은 최대 (n-1)개

// [Union - Find] ---------------------------------------------------------------- //

int findSet(int v) {	// 집합의 부모를 찾음
	if (parent[v] == -1) return v;	// 자신이 부모 노드인 경우
	return parent[v] = findSet(parent[v]);	// 경로 압축 (나중에 부모를 쉽게 찾기 위해)
}

int unionSet(int node1, int node2) {
	node1 = findSet(node1);	// node1의 부모 찾기
	node2 = findSet(node2);	// node2의 부모 찾기
	if (node1 != node2) {	// 만약, 서로 다른 집합인 경우?
		parent[node2] = node1;	// 집합 합치기 (node2를 node1로 붙임)
		return 1;	// 합집합 성공을 알림
	}
	return 0;	// 사이클 발생을 알림
}

// [MinHeap] ---------------------------------------------------------------- //

void insertMinHeap(Edge edge) {
	int index = ++heapSize;	// 힙 크기 증가 및 삽입 위치 설정 (일단 마지막에 붙이기)
	while (index != 1 && edge.weight < minHeap[index / 2].weight) {	// 부모 노드보다 작으면
		minHeap[index] = minHeap[index / 2];	// 부모 노드를 아래로 내림
		index /= 2;	// 부모 인덱스로 이동
	}
	minHeap[index] = edge;	// 그 자리에 새로운 엣지 정보 삽입
}

Edge deleteMinHeap() {
	Edge minEdge = minHeap[1];	// 최소 엣지 (루트 노드)
	Edge lastEdge = minHeap[heapSize--];	// 힙 크기 감소
	int parentIndex = 1; int childIndex = 2; // 루트에서부터 시작

	while (childIndex <= heapSize) { // 더 작은 자식 노드 찾기
		if (childIndex < heapSize && minHeap[childIndex].weight > minHeap[childIndex + 1].weight) childIndex++;	// 오른쪽 자식이 더 작으면? 오른쪽 자식으로 이동
		if (lastEdge.weight <= minHeap[childIndex].weight) break; // 만약, 마지막 엣지가 자식보다 작거나 같으면? 위치 확정
		minHeap[parentIndex] = minHeap[childIndex]; // 자식 노드를 부모 위치로 올림
		parentIndex = childIndex; // 아래로 이동
		childIndex *= 2; // 왼쪽 자식 인덱스로 이동
	}
	minHeap[parentIndex] = lastEdge; // 마지막 엣지를 그 자리에 삽입
	return minEdge; // 최소 엣지 반환
}

void printMinHeap() {
	printf("\nMinHeap = [");
	if (heapSize == 0) {
		printf("]\n");
		return;
	}

	for (int i = 1; i <= heapSize; i++) {
		printf("(%d,%d|%d)", minHeap[i].node1, minHeap[i].node2, minHeap[i].weight);
		if (i < heapSize) { // 마지막 원소가 아니면 콤마 출력
			printf(", ");
		}
	}
	printf("]\n");
}

// [MCST * Kruskal] ---------------------------------------------------------------- //

void MST() {
	int mstCost = 0;
	int edgesCount = 0;

	for (int i = 0; i < numNodes; parent[i++] = -1);	// 각 노드를 자신을 부모(-1)로 하는 집합으로 초기화
	for (int i = 0; i < totalEdges; insertMinHeap(edges[i++])); // 간선 수만큼 반복하여 최소 힙에 삽입

	while (heapSize > 0 && edgesCount < numNodes - 1) { // 힙의 크기가 0이 아니거나, MST 간선 수보다 작을 때까지 반복
		printMinHeap(); // 최소 힙 상태 출력
		Edge currentEdge = deleteMinHeap();	// 최소 엣지 추출
		if (unionSet(currentEdge.node1, currentEdge.node2)) {	// 사이클 확인 (Union-Find)
			printf("엣지 (%d, %d)가 선택되었습니다!\n", currentEdge.node1, currentEdge.node2); // MST 엣지로 채택
			mstEdges[mstEdgesCount++] = currentEdge; // MST 엣지 배열에 추가
			mstCost += currentEdge.weight;
			edgesCount++;
		}
		else {
			printf("==> 엣지 (%d, %d)가 무시되었습니다...\n", currentEdge.node1, currentEdge.node2);
		}
	}

	printf("\n%d개의 노드와 %d개의 엣지로 최소 비용 신장 트리를 찾았습니다!\n", numNodes, edgesCount);
	printf("%d개의 엣지 정보 : ", edgesCount);
	for (int i = 0; i < mstEdgesCount; printf("(%d,%d) ", mstEdges[i].node1, mstEdges[i].node2), i++);
}



int main(void) {
	int node1, node2, weight; 
	printf("총 노드의 개수를 입력하세요. >> "); scanf("%d", &numNodes);
	printf("엣지 정보(A, B, 가중치)를 순서대로 입력하세요. (종료: -1 -1 0)\n");
	while (1) {
		printf(">> "); scanf("%d %d %d", &node1, &node2, &weight);
		if (node1 == -1 && node2 == -1 && weight == 0) break;
		edges[totalEdges].node1 = node1; edges[totalEdges].node2 = node2; edges[totalEdges].weight = weight;
		totalEdges++; // 총 간선 수 증가
	}
	MST();
}