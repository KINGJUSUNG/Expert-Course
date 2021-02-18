#ifndef _LIST_H_
#define _LIST_H_

// circular_doublely_linked_list
// ����� ���� ����Ʈ

// ����� ���� �ڷ���(����ü)�� ��尡 ���ԵǾ��ִ� ������ ����Ʈ
// void* �� ����� ���ϱ� ���� �����
// ����Ʈ�� ������ ���� ��带 ���ؼ��� �̷����
// primitiveŸ���� �����͸� ������ �� ���ٴ� �Ѱ谡 ����
// inline�Լ��ۿ� ���Ƿ� �Լ� ����, ���Ǹ� ��� ������Ͽ��� ��
// ÷�ε� �׸��� Ȯ���ϸ� �����ϱ� ����


typedef struct Node {
	struct Node* prev;
	struct Node* next;
} Node;


// head��带 ���� �� prev�� next�� �ʱ�ȭ
// �� ��, prev�� next��� head��� �ڽ��� ����Ű���� �ʱ�ȭ
// �����ؾ� �� ���� head�� �����Ͱ� �ƴ� ����� ����
#define LIST_HEAD(name) \
    Node name = {&(name), &(name)}

// �켱 �ش� ��ũ�ΰ� �ʿ��� ������ �����غ���
// ����Ʈ�� ������ ���� ��带 ���ؼ��� �̷������
// ����� next, prev�� ���� ��������� �����ּ�, ��������� �����ּҸ� ������ �ִ�
// ���� ����� �����ּҸ� Ȱ���ؼ� ��尡 ����ִ� ����ü�� �����ּҸ� �����ؾ���
// ptr�� ����� �����ּ�, type�� ��尡 ���ԵǾ��ִ� ����ü�� Ÿ��, 
// member�� ����ü�������� ����� �������̴�
// ÷�ε� �׸����� Ȯ���ϸ� �����ϱ� ����
#define list_entry(ptr, type, member) \
    (type*)((char*)ptr - (char*)&((type*)0)->member)

// ��� Ž���� ��ũ��
#define list_foreach(node, head) \
    for (node = (head)->next; node != (head); node = node->next) 
#define list_foreach_reverse(node, head) \
    for (node = (head)->prev; node != (head); node = node->prev)


// prev �տ� ��� ����
inline void addNode(Node* prev, Node* node) {

	node->next = prev->next;
	prev->next->prev = node;

    prev->next = node;
    node->prev = prev;
}


// ����Ʈ �ǳ��� ������ �߰�
inline void listAdd(Node* head, Node* node) {
	addNode(head->prev, node);
}


// ����Ʈ �Ǿտ� ������ �߰�
inline void listAddHead(Node* head, Node* node) {
	addNode(head, node);
}


// node�� ����Ű�� ��� ����
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

