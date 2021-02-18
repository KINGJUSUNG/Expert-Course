#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


// 참조계수 : 파일디스크립터 테이블에서 몇 개의 인덱스가 
// 		   	  파일을 가리키고 있는지를 의미

// 연결계수 : 파일이 어디에 속해있는가를 의미
//          : 일반파일은 속해있는 디렉토리로 인해 연결계수가 1임
//			: 디렉토리는 속해있는 디렉토리와 .디렉토리로 인해 연결계수가 2임

int main(int argc, char **argv) {
	
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILENAME\n", *argv);
		exit(1);
	}

	argc--;
	argv++;

	// 이미 존재하는 파일이므로 연결계수는 1임
	// 참조계수는 생성된 뒤 1로 세팅
	// 파일을 open하기 전에는 ref(참조계수)는 존재하지 않음
	// 또한 파일이 open해야 파일정보구조체가 생성됨
	int fd = open(*argv, O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	close(0);	// 키보드 닫기
	dup(fd);	// 참조 계수는 2가됨

	// 기존 파일디스크립터 삭제
	close(fd);	// 참조 계수는 1이됨

	// close()를 한다고해서 파일정보구조체가 무조건 삭제되지 않음
	// 파일정보구조체의 ref(참조 계수)가 0이 되어야 파일정보구조체가 삭제됨
	// ref는 파일정보구조체를 가리키고(참고하고)있는 
	// 파일디스크립터에서의 인덱스의 개수


	char buf[32];
	read(0, buf, 5);
	printf("buf: %s\n", buf);

	exit(0);
}

