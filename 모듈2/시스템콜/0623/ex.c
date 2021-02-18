// $ ls | wc
// $ ./a.out ls wc
// ls와 wc 사이의 입출력은 라인 단위로 수행
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

enum { READ, WRITE };
int main(int argc, char **argv) {

 	if (argc != 3) {
 		fprintf(stderr, "usage: %s cmd1 cmd2\n", argv[0]);
 		exit(1);
 	}

	int pfd[2];
	if (pipe(pfd) == -1) {
		perror("pipe");
		exit(1);
	}

	pid_t pid = fork();
	if (pid > 0) {
		close(pfd[READ]);
		close(1);
		dup(pfd[WRITE]);
		close(pfd[WRITE]);
		execlp(argv[1], argv[1], (char*)NULL);
	}
	else if (pid == 0) {
		close(pfd[WRITE]);
		close(0);
		dup(pfd[READ]);
		close(pfd[READ]);
		execlp(argv[2], argv[2], (char*)NULL);
	}
	else {
		perror("fork");
		exit(1);
	}
}
