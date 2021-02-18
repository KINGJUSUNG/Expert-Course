#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// int socket(int domain, int type, int protocol);

// domain: 프로토콜 패밀리(접두어로 PF)
// PF_INET: IPv4 프로토콜
// PF_INET6: IPv6 프로토콜

// type: 여러가지가 있음
// SOCK_STREAM: TCP 프로토콜 사용(연결지향, 신뢰성 있는 전송)
// SOCK_DGRAM: UDP 프로토콜 사용

// ./a.out 192.168.0.1
int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage : %s IPADDRESS\n", *argv);
		exit(1);
	}

	// 1. 전화기를 준비
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("socket");
		exit(1);
	}

	// 2. 전화할 상태방의 전화번호를 설정
	// IP Address : 네트워크에서 장치들이 서로 인식하고 
	// 				통신을 하기 위해서 사용하는 특수한 번호
	// 32비트 정수: 2^32 = 약42억 => IPv4
	// 64비트 정수: 2^64 = ?	  => IPv6
	struct sockaddr_in addr = {0,};
	addr.sin_family = AF_INET;	// IPv4의 주소체계를 사용
	
	// port: 컴퓨터 상에서 구동중인 서비스를 식별하는 정수
	// 16비트 정수 : 0~65535(0~1023: 잘 알려진 서비스들의 번호)
	// 이 때, host order를 netword order로 반드시 바꿔서 보내야함
	addr.sin_port = htons(13);			

	// 문자열 형태의 주소를 4바이트의 정수 형태로 변환
	addr.sin_addr.s_addr = inet_addr(argv[1]);

	// 3. 통화 버튼 누르기
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		perror("connect");
		exit(1);
	}

	// 서버와 연결이 확립되면 서버는 클라이언트에게 
	// 현재 시간을 문자열 형태로 전송하고 연결을 끊음
	char buf[BUFSIZ];
	int nRead = read(sock, buf, sizeof(buf));
	if (nRead < 0) {
		perror("read");
		exit(1);
	}
	else if (nRead == 0) {
		// 상대방이 연결을 끊음
		close(sock);
		exit(1);
	}
	buf[nRead] = '\0';
	printf("%s\n", buf);
	close(sock);

	exit(0);
}

