#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

// 멀티 프로세스 기반의 서버는 안정적이지만 메모리 사용량이 많고
// 프로세스 간의 데이터 공유도 어려움
// 이를 해결하기위해 멀티 스레드를 도입

#define quit(msg) __quit((msg, __LINE__)

void __quit(const char *msg, int line) {
	char buf[BUFSIZ];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(1);
}

void *thread_main(void *arg) {

	int csock = (int)arg;

	char buf[BUFSIZ];
	int nRead = read(csock, buf, sizeof(buf));
	if (nRead < 0) {
		perror("read");
		close(csock);
		return NULL;
	}
	else if (nRead == 0) {
		close(csock);
		return NULL;
	}
	write(csock, buf, nRead);
	close(csock);
}


int main() {

	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		return -1;
	}

	struct sockaddr_in saddr = {0,};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	// saddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	// 현재 시스템에 할당된 모든 아이피로부터 접속을 허용
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int value = 1;
	if (setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value)) == -1) {
		perror("setsockopt");
		return -1;
	}

	if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
		perror("bind");
		return -1;
	}

	if (listen(ssock, 10) == -1) {
		perror("listen");
		return -1;
	}

	while (1) {
		struct sockaddr_in caddr = {0,};
		int caddr_len = sizeof(caddr);
		int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
		if (csock < 0) {
			perror("accept");
			exit(1);
		}

		printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));

		pthread_t tid;
		int ret = pthread_create(&tid, NULL, thread_main, (void*)csock);
		if (ret != 0) {
			perror("pthread_create");
			exit(1);
		}

		// 스레드가 종료되면 자동으로 자원을 해제
		// pthread_join()을 사용하지 않아도 됨
		pthread_detach(tid);
	}

	close(ssock);
	return 0;
}


