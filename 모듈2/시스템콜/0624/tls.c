#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#if 0
pthread_key_t idx;

void destructor(void *arg) {
	printf("destructor()\n");
	free(arg);
}

int foo() {
	int *pInt = pthread_getspecific(idx);	// int *pInt = TLS[idx];

	// 최초 할당 시
	if (pInt == NULL) {
		pInt = malloc(sizeof(int));
		*pInt = 0;
		pthread_setspecific(idx, pInt);		// TLS[idx] = pInt;
	}
	return ++(*pInt);
}

void *thread_main(void *arg) {
	foo();
	foo();
	int cnt = foo();
	printf("%ld: %d\n", pthread_self(), cnt);
	return NULL;
}

int main(void) {
	
	// TLS, dtor : 원소가 void*인 포인터 배열 ex) void *TLS[128]; void *dtor[128];
	// 각 스레드마다 자신만의 TLS, dtor배열을 가지게됨
	// 스레드마다 고유의 전역공간을 가지기위해 사용하는 기법
	
	// TLS의 장점 : 기존 함수의 인터페이스를 변경하지 않고도 
	// 				thread-safety한 함수를 구현 가능
	// TLS의 단점 : 사용자가 TSL에 대한 KEY(index)를 생성 및 관리
	// 			  : 포인터만 저장 가능
	// 			  : 메모리에 대한 동적할당 오버헤드 발생
	// 			  : 메모리 누구 가능성 존재
	// => 이를 해결하기 위해 정적 TLS사용

	// 비어있는 가장 작은 인덱스를 발급
	// 해당 인덱스는 TLS, dtor배열 모두에 적용됨
	// dtor배열의 해당 인덱스에는 자원 해제를 위한 함수의 주소를 할당
	pthread_key_create(&idx, destructor);

	pthread_t t1, t2;
	pthread_create(&t1, NULL, thread_main, NULL);
	pthread_create(&t2, NULL, thread_main, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_key_delete(idx);

	return 0;
}
#endif


__thread int cnt = 0;	// 정적 TLS

int foo() {
	return ++cnt;
}

void *thread_main(void *arg) {
	foo();
	foo();
	int cnt = foo();
	printf("%ld: %d\n", pthread_self(), cnt);
	return NULL;
}

int main(void) {
	
	pthread_t t1, t2;
	pthread_create(&t1, NULL, thread_main, NULL);
	pthread_create(&t2, NULL, thread_main, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}
