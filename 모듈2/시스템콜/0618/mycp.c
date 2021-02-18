#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// ./mycp a b
// 복사할 파일이 존재할 경우, 기존 파일의 내용을 삭제
int main(int argc, char **argv) {
	
	if (argc != 3) {
		fprintf(stderr, "usgae : %s SRCFILE DSTFILE\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	int srcfd = open(*argv, O_RDONLY);
	if (srcfd == -1) {
		perror("open");
		exit(1);
	}

	++argv;

	int dstfd = open(*argv, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (dstfd == -1) {
		perror("open");
		exit(1);
	}

	char buf[BUFSIZ];
	while (1) {
		int nRead = read(srcfd, buf, BUFSIZ);
		if (nRead < 0) {
			perror("read");
			exit(1);
		}
		else if (nRead == 0) {
			break;
		}
		write(dstfd, buf, nRead);
	}

	close(srcfd);
	close(dstfd);

	exit(0);
}

