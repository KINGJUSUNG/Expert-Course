#include <stdio.h>
#include <stdlib.h>

#if 0
int main() {

	unsigned int x = 0x1;	// 00 00 00 01
	unsigned char *p = (unsigned char *)&x;

	if (*p == 1) {
		printf("Little endian\n");
	}
	else {
		printf("Big endian\n");
	}

	exit(0);
}
#endif

#if 0
int is_bigEndian() {
	unsigned int x = 0x1;	// 00 00 00 01
	unsigned char *p = (unsigned char *)&x;
	return (*p == 0);
}

int main() {

	if (is_bigEndian()) {
		printf("big endian\n");
	}
	else {
		printf("little endian\n");
	}

	exit(0);
}
#endif


#if 0
static const unsigned int __ENDIAN_VALUE = 0x1;
#define IS_BIGENDIAN() (*((unsigned char*)&__ENDIAN_VALUE) == 0)

int main() {

	if (IS_BIGENDIAN()) {
		printf("big endian\n");
	}
	else {
		printf("little endian\n");
	}

	exit(0);
}
#endif


#if 0
// C99: compound literal(이름없는 객체)
struct Point {
	int x, y;
};

int main() {
	// 1; 	   // OK
	// {1, 2}; // ERROR

	(int[]){1, 2};			// ;을 만나는 순간 사라지는 임시객체
	(struct Point){1, 2};	 

	return 0;
}
#endif


// 이 방식을 많이 사용함
#if 0
#define IS_BIGENDIAN()	\
	(((union {unsigned int i; unsigned char c; }){1}).c == 0)

int main() {

	if (IS_BIGENDIAN()) {
		printf("big endian\n");
	}
	else {
		printf("little endian\n");
	}

	return 0;
}
#endif


#if 0
int main() {

#if __BYTE_ORDER == __LITTLE_ENDIAN 
	printf("little endian\n");
#else
	printf("big endian\n");
#endif
}
#endif


#if 0
#define IS_BIGENDIAN()	\
	(((union {unsigned int i; unsigned char c; }){1}).c == 0)

void printMemory(void *value, size_t size) {
	unsigned char *p = (unsigned char *)value;
	for (size_t i = 0; i < size; i++) {
		printf("[%X]", p[i]);
	}
	printf("\n");
}

unsigned int toBigEndian(unsigned int value) {
	if (IS_BIGENDIAN()) {
		return value;
	}

	unsigned char *src = (unsigned char *)&value;

	unsigned int data = 0;
	unsigned char *dst = (unsigned char *)&data;

	dst[0] = src[3];
	dst[1] = src[2];
	dst[2] = src[1];
	dst[3] = src[0];
}

int main() {
	unsigned int data = 0x12345678;
	printMemory(&data, sizeof(data));

	data = toBigEndian(data);
	printMemory(&data, sizeof(data));

	return 0;
}
#endif

#include <arpa/inet.h>

#define IS_BIGENDIAN()	\
	(((union {unsigned int i; unsigned char c; }){1}).c == 0)

void printMemory(void *value, size_t size) {
	unsigned char *p = (unsigned char *)value;
	for (size_t i = 0; i < size; i++) {
		printf("[%X]", p[i]);
	}
	printf("\n");
}

int main() {

	unsigned int data = 0x12345678;
	printMemory(&data, sizeof(data));

	data = htonl(data);
	printMemory(&data, sizeof(data));

	// byte order 변환
	// htons : host to network short(2byte);
	// ntohs, ntohl, ...

	return 0;
}
