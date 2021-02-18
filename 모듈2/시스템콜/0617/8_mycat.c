#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// $ ./a.out hello.txt

int main(int argc, char **argv) {
	
	if (argc != 2) {
		fprintf(stderr, "usgae: %s FILENAME\n", *argv);
		return -1;
	}

	--argc;
	++argv;

	int fd = open(*argv, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	char buf[4096];
	while (1) {
		ssize_t nRead = read(fd, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		else {
			write(1, buf, nRead);
		}
	}

	close(fd);
	return 0;
}

