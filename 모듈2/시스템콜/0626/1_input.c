// 1_input.c
#if 0
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	int fifo = open("./myfifo", O_RDONLY);
	if (fifo < 0) {
		perror("open");
		return -1;
	}

	char buf[BUFSIZ];
	while (1) {
		int nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		write(1, buf, nRead);

		nRead = read(fifo, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		write(1, buf, nRead);
	}

	close(fifo);
	return 0;
}
#endif

#if 1
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	int fd = open("./myfifo", O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}
	int max_fd = fd;

	fd_set read_fds;		// == unsigned int read_fds[32];	// 32 * 32 = 1024
	FD_ZERO(&read_fds);	// for (int i = 0; i < 32; i++) read_fds[i] = 0;
	FD_SET(0, &read_fds);
	FD_SET(fd, &read_fds);

	char buf[BUFSIZ];
	while (1) {
		fd_set temp_fds = read_fds;
		int ret = select(max_fd + 1, &temp_fds, NULL, NULL, NULL);
		if (ret < 0) {
			perror("select");
			return -1;
		}

		for (int i = 0; i < (max_fd + 1); i++) {
			if (FD_ISSET(i, &temp_fds)) {
				int nRead = read(i, buf, sizeof(buf));
				if (nRead < 0) {
					perror("read");
					return -1;
				}
				write(1, buf, nRead);
			}
		}
	}

	close(fd);
	return 0;
}
#endif
