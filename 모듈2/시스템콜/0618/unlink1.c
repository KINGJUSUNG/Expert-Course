#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {

	// 파일의 참조계수가 생성되고 1이됨
	int fd = open("hello.txt", O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	// 파일의 연결계수를 1 감소시킴
	if (unlink("hello.txt") < 0) {
		perror("unlink");
		exit(1);
	}

	// 삭제하면 연결계수는 0, 참조계수는 1이됨
	// 이런 상황에서는 파일이 보이지는 않지만 파일에 대한 정보는 유효함

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
		else {
			write(1, buf, nRead);
		}
	}

	// 참조계수도 0이됨
	// 리눅스에서는 연결계수, 참조계수가 모두 0이 되어야 비로소 파일이 삭제됨
	close(fd);
	exit(0);
}

