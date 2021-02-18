#if 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


// 알람 시그널 : 알람 함수에 의해 발생되는 시그널
// 알람 함수에게 시간(초)를 전달하고 지정된 시간이 지나면 알람 함수를 
// 수행한 프로세스에게 SIGALARM을 보냄

void SIGALRM_Handler(int signo) {
	printf("SIGALRM!\n");
	printf("signo: %d\n", signo);
}

void SIGINT_Handler(int signo) {
	printf("SIGINT!\n");
	printf("signo: %d\n", signo);
}


int main() {

	if (signal(SIGALRM, SIGALRM_Handler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	if (signal(SIGINT, SIGINT_Handler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	alarm(3);

	while (1) {
		;
	}

	return 0;
}
#endif


#if 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void sigHandler(int signo) {
	
	switch (signo) {
		
		case SIGALRM: 
			printf("SIGALRM!\n");
			alarm(1);
			break;

		case SIGINT:
			printf("SIGINT");
			break;
	}
}


void SIGALRM_Handler(int signo) {
	printf("SIGALRM!\n");
	printf("signo: %d\n", signo);
}


void SIGINT_Handler(int signo) {
	printf("SIGINT!\n");
	printf("signo: %d\n", signo);
}


int main() {

	if (signal(SIGALRM, SIGALRM_Handler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	if (signal(SIGINT, SIGINT_Handler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	alarm(3);

	while (1) {
		;
	}

	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// 시그널을 무시한다는 것은 핸들러 안에서 아무것도 하지 않는 것을 의미하는게 아니라
// 핸들러가 아무런 일을 하지 않는다고 하더라도 일단 핸들러가 호출되었다는 것은
// 처리를 한 것이나 다름 없음
// 시그널을 무시하려면 SIG_IGN
void sigHandler(int signo) {
	printf("sigHandler\n");
}

int main() {
	
	if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	while (1) {
		;
	}

	exit(0);
}
#endif


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


// signal()로 특정 시그널에 핸들러를 붙이는 순간
// 해당 시그널의 디폴트 기능은 해제됨

// 시그널 복원(해제)
void sigHandler(int signo) {

	printf("SIGINT\n");

	if (signal(SIGINT, SIG_DFL) == SIG_ERR) {
		perror("signal");
	}
}


int main() {
	
	if (signal(SIGINT, sigHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	while (1) {
		;
	}

	exit(0);
}

