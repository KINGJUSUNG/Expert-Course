#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// 아래의 코드를 select를 사용한 코드로 변경해 보세요 :D

void __quit(const char *msg, int line) {
	char buf[BUFSIZ];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(1);
}
#define err_quit(msg)	__quit(msg, __LINE__)

int main() {
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1)
		err_quit("socket");

	struct sockaddr_in saddr = {0,};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
																					

	int value = 1;
	if (setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value)) == -1)
		err_quit("setsockopt");
	
	if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
		err_quit("bind");

	if (listen(ssock, 10) == -1)
		err_quit("listen");
	printf("[server] running...\n");

	// 서버 소켓 등록
	int max_fd = ssock;
	fd_set read_fds;
	FD_ZERO(&read_fds);
	FD_SET(ssock, &read_fds);
	
	char buf[BUFSIZ];
	while (1) {
		fd_set temp_fds = read_fds;
		int nfds = max_fd + 1;
		int ret = select(nfds, &temp_fds, NULL, NULL, NULL);
		if (ret < 0)
			err_quit("select");
		else if (ret == 0)	// timeout
			continue;

		for (int i = 0; i < nfds; i++) {
			if (FD_ISSET(i, &temp_fds)) {
				if (i == ssock) {
					struct sockaddr_in caddr = {0,};
					int caddr_len = sizeof(caddr);
					int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
					if (csock < 0)
						err_quit("accept");
					printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));

					FD_SET(csock, &read_fds);
					if (csock > max_fd)
						max_fd = csock;
				}
				else {
					int nRead = read(i, buf, sizeof(buf));
					if (nRead < 0) {
						err_quit("read");
					}
					else if (nRead == 0) {
						close(i);
						FD_CLR(i, &read_fds);
					}
					else {
						write(i, buf, nRead);
						close(i);
						FD_CLR(i, &read_fds);
					}
				}
			}
		}
	}	// end of while

	close(ssock);
	return 0;
}

