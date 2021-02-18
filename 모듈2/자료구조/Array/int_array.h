#ifndef _INT_ARRAY_H_
#define _INT_ARRAY_H_

#define INITIAL_SIZE (4)
#define MAX_SIZE	(4096)

// IntegerŸ���� �����͸� �����ϴ� ���� �迭 ����ü
// �������� ������ ���� �ҿ����� ����ü ������ Ȱ��
typedef struct Array Array;


Array* arrayCreate();
void arrayDestroy(Array* arr);
static int increaseSize(Array* arr, int size);
int arrayAdd(Array* arr, int data);
int arrayInsert(Array* arr, int index, int data);
int arrayRemove(Array* arr, int index, int* delData);
int arraySet(Array* arr, int index, int newData, int* oldData);
int arrayGet(const Array* arr, int index, int* outData);
void arrayDisplay(Array* arr);
int arrayCount(const Array* arr);

#endif