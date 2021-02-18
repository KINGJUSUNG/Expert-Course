#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// gcc -O2 thread2.c -pthread
// 이렇게 최적화 컴파일을 할 경우
// thread_main()내에서 pflag는 어디에서도 값이 바뀌지 않으므로
// 컴파일러는 pflag를 캐싱해서 사용함
// 그러면 외부에서 수정을 해도 적용이 안되므로 버그 발생

// 즉 서로 다른 스레드에서 공유자원을 사용할 경우, 
// 그 자원은 최적화를 수행하지 않음

void *thread_main(void *arg) {
	volatile int *pflag = (int *)arg;
	while (*pflag) {
		;
	}
	printf("exit thread_main\n");
	return NULL;
}

int main() {
	int flag = 1;

	pthread_t tid;
	pthread_create(&tid, NULL, thread_main, &flag);

	getchar();
	flag = 0;

	pthread_join(tid, NULL);
	printf("exit main\n");
	exit(0);
}
