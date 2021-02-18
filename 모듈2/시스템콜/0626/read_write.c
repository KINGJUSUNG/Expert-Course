#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 반환값: 읽은 바이트 수, -1(오류)
ssize_t readn(int fd, void *buf, size_t size) {
	
	if (fd < 0 || buf == NULL || count == 0) {
		return -1;
	}
	char *ptr = (char*)buf;
	ssize_t totalRead = 0;

	while (totalRead < size) {
		ssize_t nRead = read(fd, ptr, size - totalRead);
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			return totalRead;
		}
		totalRead += nRead;
		ptr += nRead;
	}

	return totalRead;
}

// 반환값: 쓴 바이트 수, -1(오류)
ssize_t writen(int fd, const void *buf, size_t count) {

	if (fd < 0 || buf == NULL || count == 0) {
		return -1;
	}

	const char *ptr = (const char*)buf;
	ssize_t totalWritten = 0;

}

int main() {
	char buf[BUFSIZ];
	int nRead = readn(0, buf, 5);
	printf("buf: %s", buf);
	printf("nRead: %d\n", nRead);
	writen(1, buf, 3);
	return 0;
}

