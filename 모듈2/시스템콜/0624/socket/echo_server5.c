#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>


#define MAX_POOL	(3)
#define quit(msg) __quit((msg, __LINE__)

void __quit(const char *msg, int line) {
	char buf[BUFSIZ];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(1);
}

// pre_forked : 자식 프로세스를 미리 생성해놓음
void start_child(int ssock, int id) {
	
	printf("[server %d] running...\n", id);

	// 서버 3개중 하나가 종료되면
	// 대기 중이었던 클라이언트는 종료된 서버에 접속하게됨
	while (1) {
		struct sockaddr_in caddr = {0,};
		int caddr_len = sizeof(caddr);
		int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
		if (csock < 0) {
			perror("accept");
			exit(1);
		}

		printf("[server %d] %s is connected...\n", id, inet_ntoa(caddr.sin_addr));

		char buf[BUFSIZ];
		int nRead = read(csock, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			exit(1);
		}
		else if (nRead == 0) {
			exit(1);
		}
		else {
			write(csock, buf, nRead);
		}
		close(csock);
	}
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

	// MAX_POOL만큼의 자식 프로세스를 미리 생성함
	for (int i = 0; i < MAX_POOL; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			start_child(ssock, i);
		}
		else {
			;
		}
	}

	while (wait(NULL) != -1);

	close(ssock);
	return 0;
}


