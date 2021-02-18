#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

typedef void(*FreeFn)(void*);

typedef struct Array {
	void** contents;	
	int size;
	int count;
	FreeFn freeFn;
} Array;


// 지연된 초기화(lazy initialization)을 할 것이므로 
// 배열 메모리는 여기서 할당하지 않음
Array* arrayCreate(FreeFn freeFn) {

	// calloc()은 할당된 메모리공간을 모두 0으로 초기화하므로
	// size, count변수를 별도로 초기화 할 필요없음
	Array* array = calloc(1, sizeof(Array));
	if (array == NULL) {
		perror("arrayCreate");
		return NULL;
	}

	// 사용자가 자신이 정의한 타입의 데이터를 
	// 해제하기 위한 함수를 등록할 수 있음
	if (freeFn != NULL) {
		array->freeFn = freeFn;
	}
	return array;
}


// 데이터가 동적할당된 메모리일 경우 해제
// 배열 메모리 해제
// 동적 배열 구조체 해제 
void arrayDestroy(Array* array) {
	
	if (array == NULL) {
		return;
	}

	if (array->freeFn != NULL) {
		for (int i = 0; i < array->count; i++) {
			array->freeFn(array->contents[i]);
		}
	}

	free(array->contents);
	free(array);
}


static int increaseSize(Array* array, int size) {
	
	if (array == NULL) {
		fprintf(stderr, "increaseSize: argument is null\n");
		return -1;
	}
	if (size <= 0) {
		fprintf(stderr, "increaseSize: size is zero or negative\n");
		return -1;
	}
	if (size < array->size) {
		return 0;
	}

	// 지연된 초기화(lazy initialization)
	// 배열의 크기가 0일 경우 newSize를 INITIAL_SIZE로 초기화
	// 그렇지 않을 경우 일단은 newSize를 배열의 크기로 초기화
	int newSize = (array->size == 0) ? INITIAL_SIZE : array->size;

	// newSize가 size(목표 사이즈)보다 커질때까지 
	// newSize의 크기를 2배씩 증가시킴
	while (newSize < size) {
		newSize *= 2;

		// 증가시키는 과정에서 newSize가 MAX_SIZE를 넘거나
		// newSize가 0또는 음수일 경우 
		// newSize를 MAX_SIZE로 초기화
		if (newSize > MAX_SIZE || newSize <= 0) {
			newSize = MAX_SIZE;
		}
	}

	// newSize 초기화 완료 
	// 아래에서는 배열 관련 처리 진행 

	void** newContents = NULL;

	// 배열 초기화 
	if (array->contents == NULL) {
		newContents = calloc(newSize, sizeof(void*));
		if (newContents == NULL) {
			perror("increaseSize");
			return -1;
		}
	}
	// 배열 확장
	else {
		newContents = realloc(array->contents, sizeof(void*) * newSize);
		if (newContents == NULL) {
			perror("increaseSize");
			return -1;
		}
	}

	array->contents = newContents;
	array->size = newSize;
	return 0;
}


// 배열의 맨 뒤에 데이터 추가
// 따라서 memmove()를 통해 메모리를 이동할 필요없음
int arrayAdd(Array* array, void* data) {
	
	if (array == NULL) {
		fprintf(stderr, "arrayAdd: argument is null\n");
		return -1;
	}
	if (increaseSize(array, array->count + 1) == -1) {
		fprintf(stderr, "arrayAdd: memory allocation failed\n");
		return -1;
	}

	array->contents[array->count] = data;
	(array->count)++;
	return 0;
}


int arrayInsert(Array* array, int index, void* newData) {
	
	if (array == NULL) {
		fprintf(stderr, "arrayInsert: argument is null\n");
		return -1;
	}
	if (increaseSize(array, array->count + 1) == -1) {
		fprintf(stderr, "arrayInsert: memory allocation failed\n");
		return -1;
	}

	// 배열의 중간에 데이터를 삽입하는 것이므로
	// 메모리 공간의 이동이 필요함
	memmove(
		array->contents + index + 1, 
		array->contents + index,
		sizeof(void*) * (array->count - index)
	);

	array->contents[index] = newData;
	(array->count)++;
	return 0;
}


// 인덱스 기반의 삭제이므로 사용시 유의해야함
// 사용자에게 삭제한 데이터를 반환
// 동적할당된 데이터일 경우 사용자가 반환받은 뒤 직접 해제해야함
void* arrayRemove(Array* array, int index) {
	
	if (array == NULL) {
		fprintf(stderr, "arrayRemove: argument is null\n");
		return NULL;
	}
	if (array->count == 0) {
		fprintf(stderr, "arrayRemove: array is empty\n");
		return NULL;
	}
	if (index < 0 || index >= array->count) {
		fprintf(stderr, "arrayRemove: out of index\n");
		return NULL;
	}

	// 삭제할 데이터를 저장
	void* outData = array->contents[index];

	// 만약 마지막 인덱스에 있는 데이터를 삭제하는 경우라면
	// 불필요하게 메모리를 이동시킬 필요가 없음
	if (index != (array->count - 1)) {
		memmove(
			array->contents + index, 
			array->contents + index + 1,
			sizeof(void*) * ((array->count - 1) - index)
		);
	}

	(array->count)--;
	return outData;
}


void* arraySet(Array* array, int index, void* newData) {
	
	if (array == NULL) {
		fprintf(stderr, "arraySet: argument is null\n");
		return NULL;
	}
	if (index < 0 || index >= array->count) {
		fprintf(stderr, "arraySet: out of index\n");
		return NULL;
	}

	void* oldData = array->contents[index];
	array->contents[index] = newData;
	return oldData;
}


void* arrayGet(const Array* array, int index) {
	
	if (array == NULL) {
		fprintf(stderr, "arrayGet: argument is null\n");
		return NULL;
	}
	if (index < 0 || index >= array->count) {
		fprintf(stderr, "arrayGet: out of index\n");
		return NULL;
	}
	return  array->contents[index];
}


// 사용자가 정의한 데이터의 타입을 알 수 없으므로
// 데이터 출력 함수를 사용자로부터 받아야함
void arrayDisplay(const Array* array, const char* (*display)(const void*)) {

	if (array == NULL || display == NULL) {
		fprintf(stderr, "arrayDisplay: argument is null\n");
		return;
	}

	for (int i = 0; i < array->count; i++) {
		printf("%s ", display(array->contents[i]));
	}
	printf("\n");
}


int arrayCount(const Array* array) {
	if (array == NULL) {
		fprintf(stderr, "arrayCount: argument is null\n");
		return -1;
	}
	return array->count;
}

