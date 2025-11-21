#include <stdio.h>	// 표준 입출력 라이브러리
#include <stdlib.h>	// 동적 메모리 할당을 위한 라이브러리
#include <time.h>	// 시간 관련 함수 라이브러리
#define SIZE 20 // 일반 정수 배열의 크기 설정
#define SWAP(x,y,t) { (t) = (x), (x) = (y), (y) = (t); } // 두 변수의 값을 교환하는 매크로 함수를 정의

typedef struct node { // 노드 구조체 정의
	int data; // 연결 리스트의 데이터 부분
	struct node* link; // 다음 노드를 가리키는 포인터
} Node; // 노드 구조체 타입을 Node라고 정의

typedef Node* NodePointer;	// Node 구조체를 가리키는 포인터 타입 정의

void selectionArraySort(int list[], int n); // 선택 정렬 함수 선언
void printLinkedList(NodePointer list); // 연결 리스트 출력 함수 선언
void printArrayList(int list[], int n); // 배열 출력 함수 선언

int main(void) {
	// 1. 20개의 공간을 가지는 배열을 선언하고, 1~1000 사이의 정수를 랜덤으로 20개를 할당하라.
	int arr[SIZE];						// 20개의 정수를 저장할 배열 선언
	srand(time(NULL));					// 난수 생성 초기화 (현재 시간을 시드로 사용)
	for (int i = 0; i < SIZE; i++) {	// 배열의 각 요소(20개)에 대해 반복
		arr[i] = rand() % 1000 + 1;		// 1~1000 사이의 랜덤 정수 할당
	}
	printf("[1. 20개의 공간을 가지는 배열 생성 및 랜덤 값 할당]\n");	// 타이틀 출력
	printArrayList(arr, SIZE); // 배열의 내용 출력



	// 2. 이 배열을 선택 정렬로 오름차순으로 정렬하라.
	printf("[2. 배열을 선택 정렬로 오름차순으로 정렬]\n");	// 타이틀 출력
	selectionArraySort(arr, SIZE);		// 배열을 선택 정렬로 오름차순 정렬
	printArrayList(arr, SIZE);			// 정렬된 배열의 내용 출력



	// 3. 정렬된 배열의 내용을 정렬된 연결 리스트로 구성하고(연결 리스트 변수는 a), 리스트의 각 노드를 순서대로 출력하라.
	NodePointer a = NULL;			// 연결 리스트의 이름이자 첫 번째 노드를 가리키는 포인터
	NodePointer tail = NULL;		// 연결 리스트의 마지막 노드를 가리키는 포인터
	for (int i = 0; i < SIZE; i++) {
		NodePointer newNode = (NodePointer) malloc (sizeof(Node));	// 새 노드 동적 할당
		newNode->data = arr[i];										// 새 노드에 배열 값 할당
		newNode->link = NULL;										// 새 노드의 링크를 NULL로 설정
		if (a) tail->link = newNode;								// a가 NULL이 아니라면? 현재 마지막 노드의 링크가 새 노드를 가리키도록 설정
		else a = newNode;											// a가 NULL이라면(첫 번째 노드 생성), a가 첫 번째 노드를 가리키도록 설정
		tail = newNode;												// tail이 새 노드를 가리키도록 설정
	}
	printf("[3. 정렬된 배열을 연결 리스트로 구성]\n");	// 타이틀 출력
	printLinkedList(a); // 연결 리스트 a의 각 노드를 순서대로 출력



	// 4. 연결 리스트 b를 구성하고, 리스트의 각 노드를 순서대로 출력하라(1, 2, 3단계를 반복함).
	for (int i = 0; i < SIZE; i++) {	// 배열의 각 요소(20개)에 대해 반복
		arr[i] = rand() % 1000 + 1;		// 1~1000 사이의 랜덤 정수 할당
	}
	printf("[4-1. 20개의 공간을 가지는 배열 생성 및 랜덤 값 할당]\n");	// 타이틀 출력
	printArrayList(arr, SIZE); // 배열의 내용 출력

	printf("[4-2. 배열을 선택 정렬로 오름차순으로 정렬]\n");	// 타이틀 출력
	selectionArraySort(arr, SIZE);									// 배열을 선택 정렬로 오름차순 정렬
	printArrayList(arr, SIZE);										// 정렬된 배열의 내용 출력

	NodePointer b = NULL;											// 연결 리스트의 이름이자 첫 번째 노드를 가리키는 포인터
	tail = NULL;													// 연결 리스트의 마지막 노드를 가리키는 포인터
	for (int i = 0; i < SIZE; i++) {
		NodePointer newNode = (NodePointer) malloc (sizeof(Node));	// 새 노드 동적 할당
		newNode->data = arr[i];										// 새 노드에 배열 값 할당
		newNode->link = NULL;										// 새 노드의 링크를 NULL로 설정
		if (b) tail->link = newNode;								// b가 NULL이 아니라면? 현재 마지막 노드의 링크가 새 노드를 가리키도록 설정
		else b = newNode;											// b가 NULL이라면(첫 번째 노드), b가 첫 번째 노드를 가리키도록 설정
		tail = newNode;												// tail이 새 노드를 가리키도록 설정
	}
	printf("[4-3. 정렬된 배열을 연결 리스트로 구성]\n");	// 타이틀 출력
	printLinkedList(b);	// 연결 리스트 b의 각 노드를 순서대로 출력



	// 5. a와 b의 연결 리스트를 합병하여 하나로 정렬된 40개의 연결 리스트 d를 구성하고, d 리스트의 각 노드를 순서대로 출력하라.
	NodePointer d = NULL;							// 합병된 연결 리스트의 첫 번째 노드를 가리키는 포인터
	tail = NULL;									// 합병된 연결 리스트의 마지막 노드를 가리키는 포인터
	while (a != NULL && b != NULL) {				// a와 b의 끝까지 반복
		if (a->data < b->data) {					// a의 데이터가 b의 데이터보다 작으면?
			if (d) tail->link = a;					// 만약 d가 NULL이 아니라면? 현재 마지막 노드의 링크가 a를 가리키도록 설정
			else d = a;								// d가 NULL이라면(첫 번째 노드 생성), d가 a를 가리키도록 설정
			tail = a;								// tail을 마지막 노드로 갱신함
			a = a->link;							// a를 다음 노드로 이동
		}
		else {										// 그렇지 않으면? (만약 b의 데이터가 더 작거나 같으면)
			if (d) tail->link = b;					// 만약 d가 NULL이 아니라면? 현재 마지막 노드의 링크가 a를 가리키도록 설정
			else d = b;								// d가 NULL이라면(첫 번째 노드 생성), d가 a를 가리키도록 설정
			tail = b;								// tail을 마지막 노드로 갱신함
			b = b->link;							// a를 다음 노드로 이동
		}
	}

	if (a != NULL) tail->link = a; // (a 혹은 b의 NULL로 인해 while문이 끝난 시점) b 노드가 NULL이라면? a의 나머지를 d 끝과 연결
	else tail->link = b;  // (a 혹은 b의 NULL로 인해 while문이 끝난 시점) a 노드가 NULL이라면? b의 나머지를 d 끝과 연결

	printf("[5. a와 b의 연결 리스트를 합병하여 d 구성]\n");	// 타이틀 출력
	printLinkedList(d);		// 연결 리스트 d의 각 노드를 순서대로 출력

	return 0;	// 프로그램 종료
}

void selectionArraySort(int list[], int n) {	// 선택 정렬 함수 정의
	int min, temp;								// 최소값의 인덱스와 임시 변수 선언
	for (int i = 0; i < n - 1; i++) {			// 배열의 각 요소에 대해 반복
		min = i;								// 현재 위치를 최소값의 인덱스로 설정
		for (int j = i + 1; j < n; j++)			// 나머지 요소들에 대해 반복
			if (list[j] < list[min])			// 현재 최소값보다 작은 값이 있으면?
				min = j;						// -> 최소값의 인덱스 갱신
		SWAP(list[i], list[min], temp);			// 현재 위치와 최소값 위치의 값을 교환
	}
}

void printArrayList(int list[], int n) {	// 배열 출력 함수 정의
	for (int i = 0; i < n; i++) {			// 배열의 각 요소에 대해 반복
		printf("%d ", list[i]);				// 현재 요소 출력
	}
	printf("\n\n");							// 줄 바꿈
}

void printLinkedList(NodePointer list) {	// 연결 리스트 출력 함수 정의
	NodePointer p = list;					// 현재 노드를 가리키는 포인터 초기화
	printf("START→");						// 시작 표시 출력
	while (p != NULL) {						// 연결 리스트의 끝까지 반복
		printf("%d→", p->data);				// 현재 노드의 데이터 출력
		p = p->link;						// 다음 노드로 이동
	}
	printf("NULL\n\n");						// 줄 바꿈
}