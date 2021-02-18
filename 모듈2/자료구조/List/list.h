#ifndef _LIST_H_
#define _LIST_H_

// circular_doublely_linked_list
// 양방향 원형 리스트

// 사용자 정의 자료형(구조체)에 노드가 포함되어있는 형태의 리스트
// void* 의 사용을 피하기 위해 설계됨
// 리스트의 연결은 오직 노드를 통해서만 이루어짐
// primitive타입의 데이터를 연결할 수 없다는 한계가 있음
// inline함수밖에 없므로 함수 선언, 정의를 모두 헤더파일에서 함
// 첨부된 그림을 확인하면 이해하기 쉬움


typedef struct Node {
	struct Node* prev;
	struct Node* next;
} Node;


// head노드를 생성 후 prev와 next를 초기화
// 이 때, prev와 next모두 head노드 자신을 가리키도록 초기화
// 주의해야 할 것은 head가 포인터가 아닌 노드라는 것임
#define LIST_HEAD(name) \
    Node name = {&(name), &(name)}

// 우선 해당 매크로가 필요한 이유를 생각해보자
// 리스트의 연결은 오직 노드를 통해서만 이루어진다
// 노드의 next, prev는 각각 다음노드의 시작주소, 이전노드의 시작주소를 가지고 있다
// 따라서 노드의 시작주소를 활용해서 노드가 들어있는 구조체의 시작주소를 추출해야함
// ptr은 노드의 시작주소, type은 노드가 포함되어있는 구조체의 타입, 
// member는 구조체내에서의 노드의 변수명이다
// 첨부된 그림에서 확인하면 이해하기 쉬움
#define list_entry(ptr, type, member) \
    (type*)((char*)ptr - (char*)&((type*)0)->member)

// 노드 탐색용 매크로
#define list_foreach(node, head) \
    for (node = (head)->next; node != (head); node = node->next) 
#define list_foreach_reverse(node, head) \
    for (node = (head)->prev; node != (head); node = node->prev)


// prev 앞에 노드 생성
inline void addNode(Node* prev, Node* node) {

	node->next = prev->next;
	prev->next->prev = node;

    prev->next = node;
    node->prev = prev;
}


// 리스트 맨끝에 데이터 추가
inline void listAdd(Node* head, Node* node) {
	addNode(head->prev, node);
}


// 리스트 맨앞에 데이터 추가
inline void listAddHead(Node* head, Node* node) {
	addNode(head, node);
}


// node가 가리키는 노드 삭제
inline void listRemove(Node* node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
}


inline void listDisplay(const Node* head, const char*(*display)(void *)) {
    printf("[head]->");
    Node* node;
    list_foreach(node, head) {
        printf("%s->", display(node));
    }
    printf("[head]\n");
}


inline void listDisplayBackwardly(const Node* head, const char*(*display)(void *)) {
    printf("[head]->");
    Node* node;
    list_foreach_reverse(node, head) {
        printf("%s->", display(node));
    }
    printf("[head]\n");
}


#endif

