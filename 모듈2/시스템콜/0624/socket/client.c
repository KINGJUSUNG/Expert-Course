#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>


void *thread_main(void *arg) {
	int sock = (int)arg;

	char buf[BUFSIZ];
	while (1) {
		int nRead = read(sock, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			break;
		}
		else if (nRead == 0) {
			break;
		}
		buf[nRead] = 0;
		write(1, buf, nRead);
	}
	close(sock);
	return NULL;
}

int main() {
	
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("socket");
		return -1;
	}

	struct sockaddr_in addr = {0,};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr("192.168.30.12"); 

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		perror("connect");
		return -1;
	}

	pthread_t tid;
	int ret = pthread_create(&tid, NULL, thread_main, (void*)sock);
	if (ret) {
		perror(strerror(ret));
		exit(1);
	}

	while (1) {
		char buf[BUFSIZ];
		int nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read1");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		write(sock, buf, nRead);
	}
	close(sock);
	return 0;
}

