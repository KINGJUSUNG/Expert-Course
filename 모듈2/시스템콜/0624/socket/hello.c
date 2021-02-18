#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s IPADDRESS\n", *argv);
		exit(1);
	}

	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("socket");
		exit(1);
	}

	struct sockaddr_in addr = {0,};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr(argv[1]);

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		perror("connect");
		exit(1);
	}

	char buf[BUFSIZ];
	int nRead = read(sock, buf, sizeof(buf));
	if (nRead < 0) {
		perror("read");
		exit(1);
	}
	else if (nRead == 0) {
		printf("disconnected...\n");
		close(sock);
		exit(1);
	}
	buf[nRead] = '\0';
	printf("%s\n", buf);
	close(sock);
	exit(0);
}

