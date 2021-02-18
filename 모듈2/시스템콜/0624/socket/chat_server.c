#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>


#define MAX_CLIENT	(128)
int clients[MAX_CLIENT];
int cnt = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void broadcast_msg(char *msg, int len) {
	pthread_mutex_lock(&mtx);
	//------------------------------
	for (int i = 0; i < cnt; i++) {
		write(clients[i], msg, len);
	}
	//------------------------------
	pthread_mutex_unlock(&mtx);
}

void delete_client(int sock) {
	pthread_mutex_lock(&mtx);
	//------------------------------
	for (int i = 0; i < cnt; i++) {
		if (clients[i] == sock) {
			clients[i] = clients[--cnt];
		}
	}
	//------------------------------
	pthread_mutex_unlock(&mtx);
}

void add_client(int sock) {
	pthread_mutex_lock(&mtx);
	//------------------------------
	clients[cnt++] = sock;
	//------------------------------
	pthread_mutex_unlock(&mtx);
}

void *thread_main(void *arg) {
	
	int csock = (int)arg;
	add_client(csock);

	char buf[BUFSIZ];
	while (1) {
		int nRead = read(csock, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			break;
		}
		else if (nRead == 0) {
			break;
		}
		buf[nRead-1] = 0;
		if (!strcmp(buf, "quit")) {
			break;
		}
		broadcast_msg(buf, nRead);
	}
	close(csock);
	delete_client(csock);
	return NULL;
}

int main() {

	// PF_INET: IPv4 프로토콜
	// SOCK_STREAM: TCP 프로토콜
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		return -1;
	}

	// 소켓에 IP주소와 포트번호를 지정하기위해 사용하는 구조체
	struct sockaddr_in saddr = {0,}; 
	
	// 사용할 주소체계
	// AF_INET: IPv4의 주소체계 사용
	saddr.sin_family = AF_INET; 

	// 사용할 포트
	// host order를 netword order로 변경해서 저장
	saddr.sin_port = htons(8080); 

	// 사용할 IP주소
	// 현재 시스템에 할당된 모든 아이피로부터 접속을 허용
	saddr.sin_addr.s_addr = htonl(INADDR_ANY); 

	// sockaddr_in 구조체를 활용하여 소켓에 IP주소와 포트번호를 지정 
	if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
		perror("bind");
		return -1;
	}

	// 기존에 bind로 할당된 소켓 자원을 프로세스가 재사용할 수 있도록함
	int value = 1;
	if (setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value)) == -1) {
		perror("setsockopt");
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
		int *arg = (int *)csock;
		int ret = pthread_create(&tid, NULL, thread_main, arg);
		if (ret != 0) {
			perror(strerror(ret));
			exit(1);
		}

		// 스레드가 종료되면 자동으로 자원을 해제
		// pthread_join()을 사용하지 않아도 됨
		pthread_detach(tid);
	}

	close(ssock);
	return 0;
}

