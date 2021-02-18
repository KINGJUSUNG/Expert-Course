#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usgae: %s FILENAME\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	int fd1 = open(*argv, O_RDONLY);
	if (fd1 < 0) {
		perror("open");
		exit(1);
	}

	int fd2 = open(*argv, O_RDONLY);
	if (fd2 < 0) {
		perror("open");
		exit(1);
	}

	// 같은 파일을 2번 열면 파일정보구조체를 공유하지 않음
	// 별도의 파일정보구조체가 생성됨
	// dup()는 다른가?

	char buf1[32];
	char buf2[32];

	read(fd1, buf1, 5);
	read(fd2, buf2, 5);

	printf("buf1: %s\n", buf1);
	printf("buf2: %s\n", buf2);

	exit(0);
}

