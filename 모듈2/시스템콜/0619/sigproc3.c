#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void sigHandler(int signo) {
	if (signo == SIGINT) {
		printf("cought SIGINT\n");
		if (signal(SIGINT, SIG_DFL) == SIG_ERR) {
			perror("signal");
			exit(1);
		}
	}
}


int main() {

	if (signal(SIGINT, sigHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	// 시그널 마스크 데이터 생성 및 초기화
	sigset_t newMask;
	if (sigemptyset(&newMask) == -1) {
		perror("sigemptyset");
		exit(1);
	}

	// 차단할 시그널을 설정
	if (sigaddset(&newMask, SIGINT) == -1) {
		perror("sigaddset");
		exit(1);
	}

	// 차단할 시그널을 추가
	sigset_t oldMask;
	if (sigprocmask(SIG_BLOCK, &newMask, &oldMask) == -1) {
		perror("sigprocmask");
		exit(1);
	}

	printf("press CTRL+C\n");
	sleep(10);

	sigset_t pendingMask;
	if (sigpending(&pendingMask) == -1) {
		perror("sigpending");
		exit(1);
	}

	int ret = sigismember(&pendingMask, SIGINT);
	if (ret == -1) {
		perror("sigismember");
		exit(1);
	}
	else if (ret == 1) {
		printf("\nSIGINT is pending...\n");
	}

	// 이전 시그널마스크로 복원
	if (sigprocmask(SIG_SETMASK, &oldMask, NULL) == -1) {
		perror("sigprocmask");
		exit(1);
	}
	
	printf("SIGINT unblocked!!\n");
	printf("press CTRL+C\n");
	sleep(10);

	exit(0);
}

