// client2.c
// 에코 프로그램
// 클라이언트

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define TEXT_SIZE (128)
typedef struct {
	long to_mtype;	// 어디에 데이터를 보낼지를 명시해주므로 반드시 들어가야함
	long from_mtype;
	char text[TEXT_SIZE];
}msg_t;

int main() {

	int qid = msgget((key_t)7777, 0);
	if (qid == -1) {
		perror("msgget");
		exit(1);
	}

	msg_t msg;

	while (1) {
		
		// msgrcv()의 4번째 인자의 값
		msg.to_mtype = 1; // 서버식별자

		msg.from_mtype = getpid();
		int nRead = read(0, msg.text, sizeof(msg.text));
		if (nRead < 0) {
			perror("read");
			exit(1);
		}
		else if (nRead == 0) {
			break;
		}
		msg.text[nRead-1] = '\0';
		msgsnd(qid, &msg, sizeof(msg_t)-sizeof(long), 0);

		memset(msg.text, '\0', sizeof(msg.text));
		
		// 끝에 0은 수신받을 데이터가 없으면 대기하겠다는 의미
		int nRcv = msgrcv(qid, &msg, sizeof(msg_t)-sizeof(long), getpid(), 0);
		if (nRcv == -1) {
			perror("msgrcv");
			exit(1);
		}
		printf("%s\n", msg.text);
	}

	exit(0);
}

