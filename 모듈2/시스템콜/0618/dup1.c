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

	int fd = open(*argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	// 파일디스크립터 테이블에서 1번 인덱스가 비어있게됨
	// 명심해야 할것은 그래도 1번 인덱스는 여전히 표준출력임
	// 즉 printf() 같은 함수들은 1번 인덱스가 어디를 가리키는지는 신경쓰지않음
	// 그냥 1번이 가리키는 곳에 출력함
	close(1);

	// dup()는 파일디스크립터 테이블에서
	// 비어있는 가장 작은 인덱스가
	// fd가 가리키는 것을 가리키도록함
	// 즉 1번인덱스는 fd가 가리키는것을 가리키게됨
	dup(fd);

	// 해당 문자열은 표준 출력으로 출력됨
	// 그런데 표준 출력은 fd의 파일정보구조체를 가리키고 있으므로
	// fd에 문자열이 출력됨
	printf("hello, world");

	close(fd);
	exit(0);
}
