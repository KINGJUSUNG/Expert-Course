#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


off_t getFileSize(int fd) {
	
	if (fd < 0) {
		fprintf(stderr, "getFileSize: fd is wrong\n");
		return -1;
	}

	off_t oldPos = lseek(fd, 0, SEEK_CUR);
	if (oldPos == -1) {
		perror("lseek");
		return -1;
	}

	off_t fsize = lseek(fd, 0, SEEK_END);
	if (fsize == -1) {
		perror("lseek");
		return -1;
	}

	if (lseek(fd, oldPos, SEEK_SET) == -1) {
		perror("lseek");
		return -1;
	}

	return fsize;
}


int main(int argc, char **argv) {
	
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	int fd = open(*argv, O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	printf("fsize: %ld\n", getFileSize(fd));

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
		write(1, buf, nRead);
	}

	exit(0);
}

