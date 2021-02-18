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


// ������ �ʱ�ȭ(lazy initialization)�� �� ���̹Ƿ� 
// �迭 �޸𸮴� ���⼭ �Ҵ����� ����
Array* arrayCreate(FreeFn freeFn) {

	// calloc()�� �Ҵ�� �޸𸮰����� ��� 0���� �ʱ�ȭ�ϹǷ�
	// size, count������ ������ �ʱ�ȭ �� �ʿ����
	Array* array = calloc(1, sizeof(Array));
	if (array == NULL) {
		perror("arrayCreate");
		return NULL;
	}

	// ����ڰ� �ڽ��� ������ Ÿ���� �����͸� 
	// �����ϱ� ���� �Լ��� ����� �� ����
	if (freeFn != NULL) {
		array->freeFn = freeFn;
	}
	return array;
}


// �����Ͱ� �����Ҵ�� �޸��� ��� ����
// �迭 �޸� ����
// ���� �迭 ����ü ���� 
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

	// ������ �ʱ�ȭ(lazy initialization)
	// �迭�� ũ�Ⱑ 0�� ��� newSize�� INITIAL_SIZE�� �ʱ�ȭ
	// �׷��� ���� ��� �ϴ��� newSize�� �迭�� ũ��� �ʱ�ȭ
	int newSize = (array->size == 0) ? INITIAL_SIZE : array->size;

	// newSize�� size(��ǥ ������)���� Ŀ�������� 
	// newSize�� ũ�⸦ 2�辿 ������Ŵ
	while (newSize < size) {
		newSize *= 2;

		// ������Ű�� �������� newSize�� MAX_SIZE�� �Ѱų�
		// newSize�� 0�Ǵ� ������ ��� 
		// newSize�� MAX_SIZE�� �ʱ�ȭ
		if (newSize > MAX_SIZE || newSize <= 0) {
			newSize = MAX_SIZE;
		}
	}

	// newSize �ʱ�ȭ �Ϸ� 
	// �Ʒ������� �迭 ���� ó�� ���� 

	void** newContents = NULL;

	// �迭 �ʱ�ȭ 
	if (array->contents == NULL) {
		newContents = calloc(newSize, sizeof(void*));
		if (newContents == NULL) {
			perror("increaseSize");
			return -1;
		}
	}
	// �迭 Ȯ��
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


// �迭�� �� �ڿ� ������ �߰�
// ���� memmove()�� ���� �޸𸮸� �̵��� �ʿ����
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

	// �迭�� �߰��� �����͸� �����ϴ� ���̹Ƿ�
	// �޸� ������ �̵��� �ʿ���
	memmove(
		array->contents + index + 1, 
		array->contents + index,
		sizeof(void*) * (array->count - index)
	);

	array->contents[index] = newData;
	(array->count)++;
	return 0;
}


// �ε��� ����� �����̹Ƿ� ���� �����ؾ���
// ����ڿ��� ������ �����͸� ��ȯ
// �����Ҵ�� �������� ��� ����ڰ� ��ȯ���� �� ���� �����ؾ���
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

	// ������ �����͸� ����
	void* outData = array->contents[index];

	// ���� ������ �ε����� �ִ� �����͸� �����ϴ� �����
	// ���ʿ��ϰ� �޸𸮸� �̵���ų �ʿ䰡 ����
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


// ����ڰ� ������ �������� Ÿ���� �� �� �����Ƿ�
// ������ ��� �Լ��� ����ڷκ��� �޾ƾ���
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

