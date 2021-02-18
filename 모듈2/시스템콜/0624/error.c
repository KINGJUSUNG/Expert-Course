#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#if 0
int main() {

	FILE *fp = fopen("xxx", "r");
	if (fp == NULL) {
		perror("fopen");
		return 1;
	}

	char buf[BUFSIZ];
	fgets(buf, sizeof(buf), fp);

	fclose(fp);
	return 0;
}
#endif


int main() {

	pthread_t tid;

	int ret = pthread_join(tid, NULL);
	if (ret) {
		// fprintf(stderr, "pthread_join: %d\n", ret);
		// POSIX라이브러리는 errno라는 스레드별 전역변수를 쓰지않으므로
		// perror()로는 에러처리 불가
		// 아래와 같이 해야함
		fprintf(stderr, "pthread_join: %s\n", strerror(ret));
		exit(1);
	}


	exit(0);
}

