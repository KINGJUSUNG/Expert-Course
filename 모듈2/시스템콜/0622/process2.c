#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 맨 처음 fork()를 호출하면 실제 복제가 일어나지는 않음. 코드를 공유만 하고 있음
// 그러다가 자식에서 부모와 공유하고 있는 무언가를 변경하면 실제로 복제가 발생함
#if 0
const char *global = "global";

int main(void) {
	const char *local = "local";
	const char **str = malloc(sizeof(char*));
	if (str == NULL) {
		perror("malloc");
		exit(1);
	}
	*str = "heap";


	// fork()의 리턴값을 통해 부모, 자식 프로세스를 구분
	pid_t pid = fork();

	// parent process
	if (pid > 0) {
		printf("[parent] %s, %s, %s\n", global, local, *str);
	}
	// child process
	else if (pid == 0) {
		global = "GLOBAL";
		local = "LOCAL";
		*str = "HEAP";
		printf("[child] %s, %s, %s\n", global, local, *str);
	}
	else {
		perror("fork");
		exit(1);
	}

	exit(0);
}
#endif

// fork 후, 자식프로세스는 부모프로세스가 열고 있는 파일디스크립터 테이블도 복제함
// 하지만 자식프로세스가 해당 파일을 닫는다 하더라도 부모에게는 영향이 없음
#if 0
int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usgae : %s FILENAME\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	int fd = open(*argv, O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	pid_t pid = fork();
	if (pid > 0) {
		sleep(3);
		printf("[parent] ");

		char buf[10];
		int nRead = read(fd, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			exit(1);
		}

		buf[nRead] = '\0';
		printf("%s\n", buf);
	}
	else if (pid == 0) {
		close(fd);
		exit(0);
	}
	else {
		perror("fork");
		exit(1);
	}

	close(fd);
	exit(0);
}
#endif


// 파일디스크립터 테이블은 복제되지만 
// 파일정보구조체는 부모와 자식이 공유함
// 즉 오프셋 같은 것은 공유함
int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usgae : %s FILENAME\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	int fd = open(*argv, O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	pid_t pid = fork();
	if (pid > 0) {
		printf("[parent] ");

		char buf[10];
		int nRead = read(fd, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			exit(1);
		}

		buf[nRead] = '\0';
		printf("%s\n", buf);
	}
	else if (pid == 0) {
		printf("[child] ");

		char buf[10];
		int nRead = read(fd, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			exit(1);
		}

		buf[nRead] = '\0';
		printf("%s\n", buf);
	}
	else {
		perror("fork");
		exit(1);
	}

	close(fd);
	exit(0);
}
