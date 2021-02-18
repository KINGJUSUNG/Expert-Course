#include <stdio.h>
#include <unistd.h>

// 표준입력으로부터 받은 데이터를 표준 출력으로 전송하는 프로그램
int main(int argc, char **argv) {

	char buf[4096];
	while (1) {

		// 키보드로부터 읽어와서 buf에 저장
		ssize_t nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) { perror("read");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		else {
			ssize_t nwritten = write(1, buf, nRead);
			if (nwritten < 0) {
				perror("write");
				return -1;
			}
			else if (nwritten != nRead) {
				fprintf(stderr, "write : %ld / %ld\n", nwritten, nRead);
				return -1;
			}
		}
	}

	return 0;
}

