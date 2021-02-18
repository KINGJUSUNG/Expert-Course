#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// 임계영역안에 오직 하나의 스레드만 들어갈 수 있도록 보장
// lock이라고 보면됨

// 1. 뮤텍스 초기화
// - 정적초기화(컴파일타임): 매크로
// - 동적초기화(런타임): 함수

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;	// 정적초기화
// pthread_mutex_init(pthread_mutex_t mtx, NULL);		// 동적초기화

int cnt = 0;

void *thread_main(void *arg) {
	for (int i = 0; i < 50000000; i++) {
		pthread_mutex_lock(&mtx);
		//-------------------------
		++cnt;
		sleep(60);
		//-------------------------
		pthread_mutex_unlock(&mtx);
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

