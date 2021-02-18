#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#if 0
// 워커 스레드 종료 방법
// 1. 시작 함수가 종료
void *thread_main(void *arg) {

	for (int i = 0; i < 5; i++) {
		sleep(1);
		printf("[worker]...\n");
	}

	const char *msg = "hello, world";
	char *p = malloc(strlen(msg) + 1);
	strcpy(p, msg);

	// 스레드 함수 내의 지역 객체의 주소를 반환하면 안됨
	// 반환된 값은 pthread_join()의 두번째 인자로 읽어올 수 있음
	return p;
}

int main() {

	pthread_t t;
	pthread_create(&t, NULL, thread_main, NULL);

	char *p;
	pthread_join(t, (void**)&p);
	printf("msg from thread: %s\n", p);
	return 0;
}
#endif


// 2. pthread_exit() 사용
void *thread_main(void *arg) {

	for (int i = 0; i < 5; i++) {
		sleep(1);
		printf("[worker]...\n");
	}

	const char *msg = "hello, world";
	char *p = malloc(strlen(msg) + 1);
	strcpy(p, msg);

	pthread_exit(p);	// return p;
}

int main() {

	pthread_t t;
	pthread_create(&t, NULL, thread_main, NULL);

	char *p;
	pthread_join(t, (void**)&p);
	printf("msg from thread: %s\n", p);
	return 0;
}
