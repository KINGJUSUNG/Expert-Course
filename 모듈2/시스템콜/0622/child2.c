#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#if 0

void sigHandler(int signo) {

	if (signo == SIGCHLD) {
		int exit_code;
		wait(&exit_code);
		printf("status: %d\n", WEXITSTATUS(exit_code));
	}
}


int main() {

	// 자식프로세스의 종료코드를 처리하기 위해 핸들러를 등록
	if (signal(SIGCHLD, sigHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	pid_t pid = fork();
	
	if (pid < 0) {
		perror("fork");
		exit(1);
	}
	else if (pid == 0) {
		for (int i = 0; i < 5; i++) {
			sleep(1);
			printf("[child] do something...\n");
		}
		return 10;
	}

	// parent process
	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}

	exit(0);
}

#endif

#if 0
void sigHandler(int signo) {

	if (signo == SIGCHLD) {
		int exit_code;
		wait(&exit_code);
		printf("status: %d\n", WEXITSTATUS(exit_code));
	}
}


int main() {

	// 자식프로세스의 종료코드를 처리하기 위해 핸들러를 등록
	if (signal(SIGCHLD, sigHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	for (int i = 0; i < 10; i++) {
		pid_t pid = fork();

		if (pid < 0) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			printf("\t\tcreated child: %d\n", i+1);
			sleep(5);
			return i+1;
		}
	}

	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}

	exit(0);
}
#endif


#if 0
void sigHandler(int signo) {

	if (signo == SIGCHLD) {
		int exit_code;

		while (wait(&exit_code) > 0) {
			printf("status: %d\n", WEXITSTATUS(exit_code));
		}
	}
}


int main() {

	// 자식프로세스의 종료코드를 처리하기 위해 핸들러를 등록
	if (signal(SIGCHLD, sigHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	for (int i = 0; i < 10; i++) {
		pid_t pid = fork();

		if (pid < 0) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			printf("\t\tcreated child: %d\n", i+1);
			sleep(5);
			return i+1;
		}
	}

	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}

	exit(0);
}
#endif

#if 0
void sigHandler(int signo) {

	if (signo == SIGCHLD) {
		int exit_code;

		while (wait(&exit_code) > 0) {
			printf("status: %d\n", WEXITSTATUS(exit_code));
		}
	}
}


int main() {

	// 자식프로세스의 종료코드를 처리하기 위해 핸들러를 등록
	if (signal(SIGCHLD, sigHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	for (int i = 0; i < 10; i++) {
		pid_t pid = fork();

		if (pid < 0) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			// 근데 이렇게 하면 또 자식이 죽는 동안 부모가 실행이 안됨
			// 즉 병행성 제어가 안됨
			// waitpid()로 해결해야함
			printf("\t\tcreated child: %d\n", i+1);
			sleep(i+1);
			return i+1;
		}
	}

	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}

	exit(0);
}
#endif


void sigHandler(int signo) {

	if (signo == SIGCHLD) {
		int exit_code;

		while (waitpid(-1, &exit_code, WNOHANG) > 0) {
			printf("status: %d\n", WEXITSTATUS(exit_code));
		}
	}
}


int main() {

	if (signal(SIGCHLD, sigHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	for (int i = 0; i < 10; i++) {
		pid_t pid = fork();

		if (pid < 0) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			printf("\t\tcreated child: %d\n", i+1);
			sleep(i+1);
			return i+1;
		}
	}

	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}

	exit(0);
}
