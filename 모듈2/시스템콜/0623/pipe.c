#include <unistd.h>
#include <stdio.h>

// 디스크립터는 서로 다른 프로세스끼리 공유가 안됨
// pipe를 사용하면 공유가능
// 따라서 pipe는 부모, 자식 간의 통신에서 주로 사용됨
enum { READ, WRITE };
int main() {
	int pfd[2]; // int pipe(int pipefd[2]);
	if (pipe(pfd) == -1) {
		perror("pipe");
		return -1;
	}
	write(pfd[WRITE], "hello", 5);

	char buf[BUFSIZ];
	int nRead = read(pfd[READ], buf, sizeof(buf));
	if (nRead < 0) {
		perror("read");
		return -1;
	}
	buf[nRead] = '\0';
	printf("%s\n", buf);

	return 0;
}

