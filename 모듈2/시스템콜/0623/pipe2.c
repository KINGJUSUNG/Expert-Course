#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

enum { READ, WRITE };
int main(void) {
	int pfd[2];
	if (pipe(pfd) == -1) {
		perror("pipe");
		exit(1);
	}
	
	// 부모는 키보드로 부터 입력받은 내용을 파이프에
	// 자식은 파이프로부터 입력받은 내용을 표준출력에
	// 부모는 EOF를 만날때까지 입력받음

	char buf[BUFSIZ];
	pid_t pid = fork();
	if (pid > 0) {
		// 부모는 읽기 디스크립터 필요없음
		close(pfd[READ]);
		while (1) {
			int nRead = read(0, buf, sizeof(buf));
			if (nRead < 0) {
				perror("read");
				exit(1);
			}
			else if (nRead == 0) {
				break;
			}
			write(pfd[WRITE], buf, nRead);
		}
		close(pfd[WRITE]);
	}
	else if (pid == 0) {
		// 자식은 쓰기 디스크립터 필요없음
		close(pfd[WRITE]);
		while (1) {
			int nRead = read(pfd[READ], buf, sizeof(buf));
			if (nRead < 0) {
				perror("read");
				exit(1);
			}
			else if (nRead == 0) {
				break;
			}
			buf[nRead] = '\0';
			write(1, buf, nRead);
		}
		close(pfd[READ]);
	}
	else {
		perror("fork");
		exit(1);
	}
	return 0;

}
