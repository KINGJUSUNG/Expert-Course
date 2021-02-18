#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	
	if (argc != 2) {
		fprintf(stderr, "usgae: %s FIFO\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	int fd = open(*argv, O_WRONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	char buf[BUFSIZ];
	while (1) {
		int nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			exit(1);
		}
		else if (nRead == 0) {
			break;
		}
		write(fd, buf, nRead);
	}

	exit(0);
}
