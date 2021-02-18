#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#if 0
// 어떤 함수의 호출회수를 계산해보자
// 의도대로 나오지 않음

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int foo() {
	static int cnt = 0;
	pthread_mutex_lock(&mtx);
	//-------------------------
	++cnt;
	//-------------------------
	pthread_mutex_unlock(&mtx);
	return cnt;
}

// 스레드끼리 공유하지 않은 것은 바로 스택
// tid1, tid2 모두 해당 함수의 호출을 위해 별도의 스택메모리 생성
void *thread_main(void *arg) {
	foo();
	foo();
	int cnt = foo();
	printf("%d\n", cnt);
	return NULL;
}

int main(void) {

	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, thread_main, NULL);
	pthread_create(&tid2, NULL, thread_main, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
#endif


// pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
// 아래의 함수는 thread-safety하지 않음
// int foo() {
// 	static int cnt = 0;
// 	pthread_mutex_lock(&mtx);
// 	//-------------------------
// 	++cnt;
// 	//-------------------------
// 	pthread_mutex_unlock(&mtx);
// 	return cnt;
// }

// 즉 해당 문제는 mutex로 해결할 수 있는 성질이 아님
// _r : reentrant(재진입가능)
// 	  : 서로 다른 스레드가 같은 함수를 사용한다 하더라도 언제나 같은 실행결과를 보장
// 	  : thread_safety에서 강화된 버전

// 재진입 가능 함수를 구현하려면 아래의 조건을 만족해야함
// 1. 정적 또는 전역 변수를 사용하면 안됨
// 2. 정적 또는 전역 변수의 주소를 반환하면 안됨
// 3. 호출자가 호출 시에 제공한 매개변수(또는 저장 공간)만을 사용하여 동작
// 4. 다른 비 재진입 함수를 호출하면 안됨
void foo_r(int *cnt) {
	++(*cnt);
}

void *thread_main(void *arg) {
	int cnt = 0;
	foo_r(&cnt);
	foo_r(&cnt);
	foo_r(&cnt);
	printf("%d\n", cnt);
	return NULL;
}

int main(void) {

	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, thread_main, NULL);
	pthread_create(&tid2, NULL, thread_main, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}

