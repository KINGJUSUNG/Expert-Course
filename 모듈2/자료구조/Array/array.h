#ifndef _ARRAY_H_
#define _ARRAY_H_

// 정보 은닉을 위해 불완전한 구조체로 만듬
typedef struct Array Array;

#define INITIAL_SIZE	(4)
#define MAX_SIZE	(4096)

Array* arrayCreate();
void arrayDestroy(Array* array);
int arrayAdd(Array* array, void* data);
int arrayInsert(Array* array, int index, void* newData);
void* arrayRemove(Array* array, int index);
void* arraySet(Array* array, int index, void* newData);
void* arrayGet(const Array* array, int index);
void arrayDisplay(const Array* array, const char* (*display)(const void*));
int arrayCount(const Array* array); 

#endif