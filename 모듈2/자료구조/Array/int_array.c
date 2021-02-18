#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "int_array.h"

typedef struct Array {
	int* buf;
	int size;
	int count;
}Array;


// ������ �ʱ�ȭ(lazy initialization)�� �� ���̹Ƿ� 
// �迭 �޸𸮴� ���⼭ �Ҵ����� ����
Array* arrayCreate() {

	// calloc()�� �Ҵ�� �޸𸮰����� ��� 0���� �ʱ�ȭ�ϹǷ�
	// size, count������ ������ �ʱ�ȭ �� �ʿ����
	Array* tmp = calloc(1, sizeof(Array));
	if (tmp == NULL) {
		perror("arrayCreate");
		return NULL;
	}
	return tmp;
}


// �迭 �޸� ����
// ���� �迭 ����ü ���� 
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

	// ������ �ʱ�ȭ(lazy initialization)
	// �迭�� ũ�Ⱑ 0�� ��� newSize�� INITIAL_SIZE�� �ʱ�ȭ
	// �׷��� ���� ��� �ϴ��� newSize�� �迭�� ũ��� �ʱ�ȭ
	int newSize = (arr->size == 0) ? INITIAL_SIZE : arr->size;

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

	int* newBuf = NULL;

	// �迭 �ʱ�ȭ 
	// buf�� NULL�̹Ƿ� buf�� �޸𸮸� newSize��ŭ ���� �Ҵ�
	if (arr->buf == NULL) {
		newBuf = calloc(newSize, sizeof(int));
		if (newBuf == NULL) {
			perror("increaseSize");
			return -1;
		}
	}
	// �迭 Ȯ��
	// buf�� NULL�� �ƴϹǷ� buf�� �޸𸮸� newSize��ŭ ���Ҵ� 
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


// �迭�� �� �ڿ� ������ �߰�
// ���� memmove()�� ���� �޸𸮸� �̵��� �ʿ����
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

	// �迭�� �߰��� �����͸� �����ϴ� ���̹Ƿ�
	// �޸� ������ �̵��� �ʿ���
	memmove(
		arr->buf + index + 1,
		arr->buf + index,
		(arr->count - index) * sizeof(int)
	);

	arr->buf[index] = data;
	arr->count++;
	return 0;
}


// �ε��� ����� �����̹Ƿ� ���� �����ؾ���
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

	// �迭�� �����Ͱ� �߰����� �����ǹǷ�
	// �޸��� �̵��� �ʿ���
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

