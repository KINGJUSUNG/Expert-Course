// msgq.c
// 에코 프로그램
// 서버

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#define TEXT_SIZE (128)
typedef struct {
	long to_mtype;
	long from_mtype;
	char text[TEXT_SIZE];
}msg_t;

int main(void) {

	// 큐를 생성
	int qid = msgget((key_t)7777, IPC_CREAT | 0666); 
	if (qid == -1) {
		perror("msgget");
		exit(1);
	}

	msg_t msg;
	while (1) {
		// 4번째 인자는 수신받을 데이터(구조체)의 mtype의 값을 의미
		// 데이터(구조체)의 mtype이 1인 데이터를 받겠다는 의미
		// 끝에 0은 수신받을 데이터가 없으면 대기하겠다는 의미
		int nRcv = msgrcv(qid, &msg, sizeof(msg_t) - sizeof(long), 1, 0);
		if (nRcv == -1) {
			perror("msgrcv");
			exit(1);
		}

		// 클라이언트는 두번째인자인 from_mtype에 자신의 pid를 넣어둠
		// 해당 프로그램은 에코 프로그램이므로
		// 받은 데이터를 다시 클라이언트에게 전송하기 위해
		msg.to_mtype = msg.from_mtype;
		msgsnd(qid, &msg, sizeof(msg_t) - sizeof(long), 0);
	}

	// 큐를 제거
	if (msgctl(qid, IPC_RMID, 0) == -1) {
		perror("msgctl");
		exit(1);
	}

	exit(0);
}

