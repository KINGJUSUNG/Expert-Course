#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILENAME\n", *argv);
		exit(1);
	}

	argc--;
	argv++;

	int fd = open(*argv, O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	// 키보드 닫기
	close(0);
	dup(fd);

	char buf1[32];
	read(fd, buf1, 5);

	char buf2[32];
	read(0, buf2, 5);

	printf("buf1: %s\n", buf1);
	printf("buf2: %s\n", buf2);

	// 파일을 2번 열면 새로운 파일정보구조체가 생성됨
	// 그러나 dup()의 경우 하나의 파일정보구조체를 공유함

	close(fd);
	exit(0);
}
