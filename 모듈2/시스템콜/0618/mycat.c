#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// ./a.out hello.txt
int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s FILENAME\n", *argv);
		return -1;
	}

	argc--;
	argv++;

	int fd = open(
			*argv, 
			O_WRONLY | O_TRUNC | O_CREAT, 
			S_IRUSR | S_IWUSR | S_IROTH);

	if (fd < 0) {
		perror("open");
		return -1;
	}

	// BUFSIZ : 최적화된 버퍼의 크기가 정의된 매크로(stdio.h)
	char buf[BUFSIZ];
	while (1) {
		ssize_t nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		write(fd, buf, nRead);
	}

	if (close(fd) == -1) {
		perror("close");
		exit(-1);
	}

	return 0;
}

