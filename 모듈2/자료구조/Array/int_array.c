#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "int_array.h"

typedef struct Array {
	int* buf;
	int size;
	int count;
}Array;


// 지연된 초기화(lazy initialization)을 할 것이므로 
// 배열 메모리는 여기서 할당하지 않음
Array* arrayCreate() {

	// calloc()은 할당된 메모리공간을 모두 0으로 초기화하므로
	// size, count변수를 별도로 초기화 할 필요없음
	Array* tmp = calloc(1, sizeof(Array));
	if (tmp == NULL) {
		perror("arrayCreate");
		return NULL;
	}
	return tmp;
}


// 배열 메모리 해제
// 동적 배열 구조체 해제 
void arrayDestroy(Array* arr) {
	if (arr == NULL) {
		return;
	}
	else {
		free(arr->buf);
		free(arr);
	}
}


static int increaseSize(Array* arr, int size) {
	
	if (arr == NULL) {
		fprintf(stderr, "increaseSize: argument is null\n");
		return -1;
	}
	if (size <= 0) {
		fprintf(stderr, "increaseSize: size is zero or negative\n");
		return -1;
	}
	if (size < arr->size) {
		return 0;
	}

	// 지연된 초기화(lazy initialization)
	// 배열의 크기가 0일 경우 newSize를 INITIAL_SIZE로 초기화
	// 그렇지 않을 경우 일단은 newSize를 배열의 크기로 초기화
	int newSize = (arr->size == 0) ? INITIAL_SIZE : arr->size;

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

	int* newBuf = NULL;

	// 배열 초기화 
	// buf가 NULL이므로 buf에 메모리를 newSize만큼 새로 할당
	if (arr->buf == NULL) {
		newBuf = calloc(newSize, sizeof(int));
		if (newBuf == NULL) {
			perror("increaseSize");
			return -1;
		}
	}
	// 배열 확장
	// buf가 NULL이 아니므로 buf에 메모리를 newSize만큼 재할당 
	else {
		newBuf = realloc(arr->buf, sizeof(int) * newSize);
		if (newBuf == NULL) {
			perror("increaseSize");
			return -1;
		}
	}

	arr->buf = newBuf;
	arr->size = newSize;
	return 0;
}


// 배열의 맨 뒤에 데이터 추가
// 따라서 memmove()를 통해 메모리를 이동할 필요없음
int arrayAdd(Array* arr, int data) {
	if (arr == NULL) {
		fprintf(stderr, "arrayAdd: argument is null\n");
		return -1;
	}

	if (increaseSize(arr, arr->count + 1) == -1) {
		fprintf(stderr, "arrayAdd: memory allocation failed\n");
		return -1;
	}

	arr->buf[arr->count] = data;
	(arr->count)++;
	return 0;
}


int arrayInsert(Array* arr, int index, int data) {
	if (arr == NULL) {
		fprintf(stderr, "arrayInsert: argument is null\n");
		return -1;
	}
	if (index < 0 || index >= arr->count) {
		fprintf(stderr, "arrayInsert: out of index\n");
		return -1;
	}

	if (increaseSize(arr, arr->count + 1) == -1) {
		fprintf(stderr, "arrayAdd: allocation failed\n");
		return -1;
	}

	// 배열의 중간에 데이터를 삽입하는 것이므로
	// 메모리 공간의 이동이 필요함
	memmove(
		arr->buf + index + 1,
		arr->buf + index,
		(arr->count - index) * sizeof(int)
	);

	arr->buf[index] = data;
	arr->count++;
	return 0;
}


// 인덱스 기반의 삭제이므로 사용시 유의해야함
int arrayRemove(Array* arr, int index, int* delData) {
	if (arr == NULL || delData == NULL) {
		fprintf(stderr, "arrayRemove: argument is null\n");
		return -1;
	}
	if (index < 0 || index >= arr->count) {
		fprintf(stderr, "arrayRemove: do not remove data out of index\n");
		return -1;
	}
	if (arr->count == 0) {
		fprintf(stderr, "arrayRemove: array is empty\n");
		return -1;
	}

	*delData = arr->buf[index];

	// 배열의 데이터가 중간에서 삭제되므로
	// 메모리의 이동이 필요함
	memmove(
		arr->buf + index,
		arr->buf + index + 1,
		(arr->count - index - 1) * sizeof(int)
	);
	(arr->count)--;
	return 0;
}


int arraySet(Array* arr, int index, int newData, int* oldData) {
	if (arr == NULL || oldData == NULL) {
		fprintf(stderr, "arraySet: argument is null\n");
		return -1;
	}

	if (index < 0 || index >= arr->count) {
		fprintf(stderr, "arraySet: out of index\n");
		return -1;
	}
	*oldData = arr->buf[index];
	arr->buf[index] = newData;
	return 0;
}


int arrayGet(const Array* arr, int index, int* outData) {
	if (arr == NULL || outData == NULL) {
		fprintf(stderr, "arrayGet: argument is null\n");
		return -1;
	}
	if (index < 0 || index >= arr->count) {
		fprintf(stderr, "arrayGet: out of index\n");
		return -1;
	}
	*outData = arr->buf[index];
	return 0;
}


void arrayDisplay(Array* arr) {
	for (int i = 0; i < arr->count; i++) {
		printf("%d ", arr->buf[i]);
	}
	printf("\n");
}


int arrayCount(const Array* arr) {
	if (arr == NULL) {
		fprintf(stderr, "arrayCount: argument is null\n");
		return -1;
	}
	return arr->count;
}

