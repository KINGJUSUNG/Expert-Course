#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int readLine(int fd, void *buf, size_t size) {
	
	if (fd < 0 || buf == NULL || size == 0) {
		return -1;
	}

	int totalRead = 0;
	char *ptr = (char*)buf;
	while (1) {
		char ch;
		int nRead = read(fd, &ch, sizeof(ch));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			if (totalRead == 0) { 	// 읽은 데이터가 없는 경우
				return 0;
			}
			else {					// 읽은 데이터가 있는 경우
				break;
			}
		}
		else {							// 읽은 데이터가 있는 경우
			if (totalRead < size - 1) {	// 버퍼의 크기를 넘지 않도록 함
										// -1은 NULL문자가 들어갈 공간을 확보하는 것
				*ptr++ = ch;
				++totalRead;
			}
			if (ch == '\n') {		// fgets()와 같이 개행을 포함시킴
				break;
			}
		}
	}
	*ptr = '\0';					// fgets()와 같이 NULL로 끝나도록함
	return totalRead;
}

int main() {
	
	int fd = open("myfifo", O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	char buf[BUFSIZ];

	int nRead = readLine(fd, buf, sizeof(buf));
	if (nRead < 0) {
		fprintf(stderr, "readLine error\n");
		exit(1);
	}
	fputs(buf, stdout);
	close(fd);
	exit(0);
}


