#include <stdio.h>
#include <pthread.h>

#if 0
// 여러 스레드가 공유자원에 접근하려고 하는 것을 race condition이라고 함
// 그리고 공유자원에 접근하는 영역을 임계영역(critical section)이라고 함
// 아래의 문제를 해결하기 위해서는 한번에 하나의 스레드만 접근하도록 하면됨
int cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 50000000; i++) {
		++cnt;
	}

	return NULL;
}

int main() {
	pthread_t tid[2];
	for (int i = 0; i < 2; i++) {
		pthread_create(&tid[i], NULL, thread_main, NULL);
	}

	for (int i = 0;  i < 2; i++) {
		pthread_join(tid[i], NULL);
	}

	printf("%d\n", cnt);
	return 0;
}
#endif


// 해당 코드는 정확하게 작동하지 않음
// c언어는 원자적인 연산을 지원하지 않음
// lock변수와 관련된 연산들도 전부 둘 이상의 명령어로 쪼개짐
int lock = 0;
int cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 50000000; i++) {
		while (lock != 0);
		lock = 1;

		++cnt;

		lock = 0;
	}

	return NULL;
}

int main() {
	pthread_t tid[2];
	for (int i = 0; i < 2; i++) {
		pthread_create(&tid[i], NULL, thread_main, NULL);
	}

	for (int i = 0;  i < 2; i++) {
		pthread_join(tid[i], NULL);
	}

	printf("%d\n", cnt);
	return 0;
}

