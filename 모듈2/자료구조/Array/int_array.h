#ifndef _INT_ARRAY_H_
#define _INT_ARRAY_H_

#define INITIAL_SIZE (4)
#define MAX_SIZE	(4096)

// Integer타입의 데이터를 저장하는 동적 배열 구조체
// 데이터의 은닉을 위해 불완전한 구조체 선언을 활용
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