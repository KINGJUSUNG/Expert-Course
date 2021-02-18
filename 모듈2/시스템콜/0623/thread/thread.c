#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

#if 0
void print(const char*str) {
	for (int i = 0; i < 10; i++) {
		printf("%s\n", str);
		sleep(1);
	}
}

int main(void) {

	print("\t\tdo something...");

	while (1) {
		printf(".\n");
		sleep(1);
	}
	exit(0);
}
#endif

#if 0
// 이전의 프로그램은 코드가 직렬적으로 수행됨
// 이제 병행적으로 수행되도록 멀티스레드 도입
void* print(void *arg) {
	const char *str = (const char *)arg;
	for (int i = 0; i < 10; i++) {
		printf("%s\n", str);
		sleep(1);
	}
}

int main(void) {

	// 스레드 생성(POSIX Thread)
	pthread_t tid;
	pthread_create(&tid, NULL, print, "\t\tdo something...");

	while (1) {
		printf(".\n");
		sleep(1);
	}
	exit(0);
}
#endif


// 자바와 같은 managed language는 메인 스레드가 종료된다 하더라도
// 워커 스레드가 구동중이면 프로세스는 종료되지 않음
// 그러나 pthread는 메인 스레드가 종료되면 이는 곧 프로세스의 종료이므로
// 워커 스레드가 존재한다 하더라도 프로세스는 종료됨
#if 0
void* print(void *arg) {
	const char *str = (const char *)arg;
	for (int i = 0; i < 10; i++) {
		printf("%s\n", str);
		sleep(1);
	}
}

int main(void) {
	pthread_t tid;
	// fork()와 비슷
	pthread_create(&tid, NULL, print, "\t\tdo something...");

	// wait()와 비슷
	// 만약 워커 스레드가 종료될 때까지 대기하려면 pthread_join()을 사용해야함
	pthread_join(tid, NULL);
	exit(0);
}
#endif


#if 0
// 프로세스가 생성될 때, 메모리를 복제하여 생성
int global = 0;

int main() {
	if (fork() == 0) {
		++global;	// COW(Copy On Write)
		printf("[child] global = %d\n", global);
		return 0;
	}

	wait(NULL);
	printf("[parent[ global = %d\n", global);
	return 0;
}
#endif


// 프로세스와 다르게 스레드는 모든 메모리를 공유함
// 스레드와 프로세스의 다른점 : 메모리 공유 유무

int global = 0;

void *thread_main(void *arg) {
	++global;
	printf("[worker thread] global = %d\n", global);
	return NULL;
}

int main() {
	pthread_t tid;
	pthread_create(&tid, NULL, thread_main, NULL);

	pthread_join(tid, NULL);
	printf("[main thread] global = %d\n", global);
	return 0;
}

