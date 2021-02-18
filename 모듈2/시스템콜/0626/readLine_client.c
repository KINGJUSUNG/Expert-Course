#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	
	int fd = open("myfifo", O_WRONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	getchar(); write(fd, "he", 2);
	getchar(); write(fd, "ll", 2);
	getchar(); write(fd, "o\n", 2);

	close(fd);
	exit(0);
}

