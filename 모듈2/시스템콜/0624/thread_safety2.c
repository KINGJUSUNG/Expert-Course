#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#if 0
// strtok()내부에 static임시변수가 존재함
// delimeter에 '\0'을 넣은 뒤 다음 위치를 가리키는 변수
// 따라서 재진입 가능하지 않음
void *thread_main1(void *arg) {
	
	char str[] = "010-1234-5678";
	char *p = strtok(str, "-");
	while (p != NULL) {
		printf("[%s]\n", p);
		p = strtok(NULL, "-");
	}
	return NULL;
}

void *thread_main2(void *arg) {
	
	char str[] = "192.168.30.105";
	char *p = strtok(str, ".");
	while (p != NULL) {
		printf("[%s]\n", p);
		p = strtok(NULL, ".");
	}
	return NULL;
}

int main() {

	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, thread_main1, NULL);
	pthread_create(&tid2, NULL, thread_main2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	exit(0);
}
#endif

#if 0
// strtok()의 재진입가능버전인 strtok_r()를 사용하여 문제해결가능
// 문제는 strtok_r()를 모르는 사람은? tls를 사용해서 해결
void *thread_main1(void *arg) {
	
	char str[] = "010-1234-5678";
	char *saveptr;
	char *p = strtok_r(str, "-", &saveptr);
	while (p != NULL) {
		printf("[%s]\n", p);
		p = strtok_r(NULL, "-", &saveptr);
	}
	return NULL;
}

void *thread_main2(void *arg) {
	
	char str[] = "192.168.30.105";
	char *saveptr;
	char *p = strtok_r(str, ".", &saveptr);
	while (p != NULL) {
		printf("[%s]\n", p);
		p = strtok_r(NULL, ".", &saveptr);
	}
	return NULL;
}

int main() {

	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, thread_main1, NULL);
	pthread_create(&tid2, NULL, thread_main2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	exit(0);
}
#endif
