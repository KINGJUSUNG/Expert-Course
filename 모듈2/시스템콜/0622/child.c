#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#if 0
int main(void) {

	pid_t pid = fork();
	if (pid > 0) {}
	else if (pid == 0) {
		for (int i = 0; i < 5; i++) {
			sleep(1);
			printf("[child] do something...\n");
		}
		
		// 자식프로세스를 종료시킴
		// 문제는 이게 바로 종료되지않음
		// 좀비 프로세스가 되어버림

		// 좀비 프로세스를 양산하지 않기위해서는
		// 반드시 자식의 종료코드를 읽어야함

		exit(0);
	}
	else {
		perror("fork");
		exit(1);
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
int main() {
	pid_t pid = fork();
	if (pid > 0) {
	}
	else if (pid == 0) {
		for (int i = 0; i < 5; i++) {
			sleep(1);
			printf("[child] do something...\n");
		}
		
		// 자식프로세스를 종료시킴
		// 문제는 이게 바로 종료되지않음
		// 좀비 프로세스가 되어버림

		// 좀비 프로세스를 양산하지 않기위해서는
		// 반드시 자식의 종료코드를 읽어야함
		
		return 100;
	}
	else {
		perror("fork");
		exit(1);
	}

	// 자식의 종료코드를 읽어내는 함수
	// 해당 코드를 추가하면 좀비 프로세스가 없어짐
	int exit_code;

	// ppt참고
	wait(&exit_code);
	printf("exit code from child: %d\n", WEXITSTATUS(exit_code));

	// parent process
	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}

	exit(0);
}
#endif


int main() {
	
	pid_t pid = fork();
	
	if (pid > 0) {
		;
	}
	else if (pid == 0) {
		for (int i = 0; i < 5; i++) {
			sleep(1);
			printf("[child] do something...\n");
		}
		abort();
	}
	else {
		perror("fork");
		exit(1);
	}

	int exit_code;

	// wait()를 통해 좀비 프로세스를 삭제
	// 문제는 부모가 자식이 종료될 때까지 기다려야함
	wait(&exit_code);

	if ((exit_code & 0xFF) == 0) {	// 정상 종료
		printf("exit_code = %d\n", WEXITSTATUS(exit_code));
	}
	else {	// 비정상 종료
		printf("exit_code = %d\n", WTERMSIG(exit_code));
	}

	// parent process
	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}

	exit(0);
}

