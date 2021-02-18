#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s FIFO\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	// 파이프 생성
	if (mkfifo(*argv, 0666) == -1) {
		perror("mkfifo");
		exit(1);
	} 

	// 파이프 열기
	int fd = open(*argv, O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	char buf[BUFSIZ];
	while (1) {
		int nRead = read(fd, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			exit(1);
		}
		else if (nRead == 0) {
			break;
		}
		write(1, buf, nRead);
	}

	// 다 사용한 파이프는 삭제
	unlink(*argv);
	exit(0);
}

