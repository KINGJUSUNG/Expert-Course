#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// 어떤 프로세스에 시그널이 발생되었을 때, 시그널을 미리 등록해 두었다면
// 핸들러가 호출됨. 핸들러를 등록하지 않았다면 기본적으로 종료됨
// 만약 중요한 일을 하는 시적에 시그널을 받지 않고 보류시키고 싶다면 
// sigprocmask()를 사용하면 됨

// sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
// how의 값에 따라 동작 방식이 달라짐

// 1. SIG_SETMASK : 시그널 마스크를 set으로 변경
// 2. SIG_BLOCK: 시그널 마스크에 set에 포함된 시그널을 추가
// 3. SIG_UNBLOCK: 시그널 마스크에 set에 포함된 시그널을 제거

// oldset이 NULL이 아니라면 이전 시그널 모음을 oldset에 저장
// set이 NULL이라면 how를 무시하고 시그널 마스크를 oldset에 저장


void showMask() {

	sigset_t curMask;
	
	// 현재 시그널 마스크를 추출
	if (sigprocmask(0, NULL, &curMask) == -1) {
		perror("sigprocmask");
		return;
	}

	printf("blocked signal list: \n");

	if (sigismember(&curMask, SIGINT)) { printf("SIGINT "); }
	if (sigismember(&curMask, SIGQUIT)) { printf("SIGQUIT "); }
	if (sigismember(&curMask, SIGALRM)) { printf("SIGALRM "); }
}


void SIGINT_handler(int signo) {
	printf("SIGINT!!\n");
}


int main() {

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

	// 차단할 시그널 목록을 확인
	showMask();

	if (signal(SIGINT, SIGINT_handler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	// 이전 시그널로 복원하고 싶은 경우
	if (sigprocmask(SIG_SETMASK, &oldMask, NULL) == -1) {
		perror("sigprocmask");
		exit(1);
	}
	
	while (1) {
		;
	}

	exit(0);
}

