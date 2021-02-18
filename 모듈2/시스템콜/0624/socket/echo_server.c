#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#if 0
int main() {

	// 1. 서버용 전화기 생성
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		exit(1);
	}

	// 2. 전화번호 설정
	// 서버의 정보를 구조체에 저장
	struct sockaddr_in saddr = {0,};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);

	// 문자열형태의 주소를 32비트 정수값으로 변환
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// 3. 전화기에 전화번호 부여
	if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
		perror("bind");
		exit(1);
	}

	// 4. 동시 접속된 클라이언트를 위한 큐를 설정
	if (listen(ssock, 10) == -1) {
		perror("listen");
		exit(1);
	}

	printf("[server] running...\n");
	
	// 5. 클라이언트의 접속을 대기
	// 접속한 클라이언트의 정보를 저장할 구조체
	struct sockaddr_in caddr = {0,};
	int caddr_len = sizeof(caddr);

	// 접속된 클라이언트를 식별하기위한 파일디스크립터
	// 마지막은 길이값의 주소라는 사실 주의
	int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
	if (csock == -1) {
		perror("accept");
		return -1;
	}

	// 32비트 정수값을 문자열형태의 주소로 변환
	printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));

	char buf[BUFSIZ];
	while (1) {
		// 클라이언트 측에서 소켓에 무엇인가 쓰기를 기다림
		// 쓰는 순간 바로 읽어냄 
		int nRead = read(csock, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			exit(1);
		}
		else if (nRead == 0) {
			printf("[server] %s is disconnected...\n", inet_ntoa(caddr.sin_addr));
			break;
		}
		else {
			write(csock, buf, nRead);
		}
	}
	close(csock);
	close(ssock);
	exit(0);
}
#endif


int main() {

	// 1. 서버용 전화기 생성
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		exit(1);
	}

	// 2. 전화번호 설정
	// 서버의 정보를 구조체에 저장
	struct sockaddr_in saddr = {0,};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);

	// 문자열형태의 주소를 32비트 정수값으로 변환
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// 이 옵션을 안해놓으면 클라이언트로부터 FIN패킷을 받으려고 계속 해당 
	// 포트를 붙잡고 있음. 필수적으로 설정해야함
	// 서버 소켓이 주소와 바인딩하기 전에 설정
	int value = 1;
	if (setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value)) == -1) {
		perror("setsockopt");
		exit(1);
	}

	// 3. 전화기에 전화번호 부여
	if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
		perror("bind");
		exit(1);
	}

	// 4. 동시 접속된 클라이언트를 위한 큐를 설정
	if (listen(ssock, 10) == -1) {
		perror("listen");
		exit(1);
	}

	printf("[server] running...\n");
	
	// 5. 클라이언트의 접속을 대기
	// 접속한 클라이언트의 정보를 저장할 구조체
	struct sockaddr_in caddr = {0,};
	int caddr_len = sizeof(caddr);

	// 접속된 클라이언트를 식별하기위한 파일디스크립터
	// 마지막은 길이값의 주소라는 사실 주의
	int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
	if (csock == -1) {
		perror("accept");
		return -1;
	}

	// 32비트 정수값을 문자열형태의 주소로 변환
	printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));

	char buf[BUFSIZ];
	while (1) {
		// 클라이언트 측에서 소켓에 무엇인가 쓰기를 기다림
		// 쓰는 순간 바로 읽어냄 
		int nRead = read(csock, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			exit(1);
		}
		else if (nRead == 0) {
			printf("[server] %s is disconnected...\n", inet_ntoa(caddr.sin_addr));
			break;
		}
		else {
			write(csock, buf, nRead);
		}
	}
	close(csock);
	close(ssock);
	exit(0);
}
