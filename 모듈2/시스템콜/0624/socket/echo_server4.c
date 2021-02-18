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


#define quit(msg) __quit((msg, __LINE__)

void __quit(const char *msg, int line) {
	char buf[BUFSIZ];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(1);
}


void sigHandler(int signo) {
	if (signo == SIGCHLD) {
		int exit_code;

		while (waitpid(-1, &exit_code, WNOHANG) > 0) {
			printf("status: %d\n", WEXITSTATUS(exit_code));
		}
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
	printf("[server] running...\n");

	if (signal(SIGCHLD, sigHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	// quit적용시켜라
	while (1) {
		struct sockaddr_in caddr = {0,};
		int caddr_len = sizeof(caddr);

		int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
		if (csock < 0) {
			perror("accept");
			return -1;
		}

		printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));

		pid_t pid = fork();
		if (pid > 0) {
			close(csock);
		}
		else if (pid == 0) {
			close(ssock);
			char buf[BUFSIZ];
			int nRead = read(csock, buf, sizeof(buf));
			if (nRead < 0) {
				perror("read");
				return -1;
			}
			else if (nRead == 0) {
				close(csock);
				return -1;
			}
			else {
				write(csock, buf, nRead);
				close(csock);
			}
			return getpid();
		}
	}

	close(ssock);
	return 0;
}


