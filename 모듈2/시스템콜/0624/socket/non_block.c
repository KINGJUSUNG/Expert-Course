#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#if 0
int main(void) {
	
	int fifo = open("myfifo", O_RDONLY);	// $ mkfifo myfifo
	if (fifo < 0) {
		perror("open");
		exit(1);
	}

	// 키보드로부터 입력받은 데이터와 파이프로부터 입력받은 데이터를
	// 출력하는 코드를 구현
	char buf[BUFSIZ];
	while (1) {

		// read()는 파일디스크립터로부터 어떤 데이터가 들어올때까지 block되어있음 
		// 그런데 중요한 것은 read()는 block, nonblock의 개념이 없음
		// block, nonblock은 파일의 속성이 결정하는 것임
		// 일반적으로 모든 파일의 기본 속성은 block상태임
		int nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			exit(1);
		}
		else if (nRead > 0) {
			buf[nRead-1] = '\0';
			printf("keyboard: %s\n", buf);
		}

		nRead = read(fifo, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			exit(1);
		}
		else if (nRead > 0) {
			buf[nRead-1] = '\0';
			printf("fifo: %s\n", buf);
		}
	}

	exit(0);
}
#endif


int main(void) {
	
	int fifo = open("myfifo", O_RDONLY);
	if (fifo < 0) {
		perror("open");
		exit(1);
	}

	// 키보드와 파이프의 속성을 non-block으로 변경
	if ((fcntl(0, F_SETFL, O_NONBLOCK) == -1) || (fcntl(fifo, F_SETFL, O_NONBLOCK) == -1)) {
		perror("fcntl");
		exit(1);
	}

	char buf[BUFSIZ];
	while (1) {

		int nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) {
			if (errno != EAGAIN) {
				perror("read");
				exit(1);
			}
		}
		else if (nRead > 0) {
			buf[nRead-1] = '\0';
			printf("keyboard: %s\n", buf);
		}

		nRead = read(fifo, buf, sizeof(buf));
		if (nRead < 0) {
			if (errno != EAGAIN) {
				perror("read");
				exit(1);
			}
		}
		else if (nRead > 0) {
			buf[nRead-1] = '\0';
			printf("fifo: %s\n", buf);
		}
	}

	exit(0);
}

