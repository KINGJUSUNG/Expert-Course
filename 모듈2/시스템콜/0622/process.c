#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// 프로세스 아이디 : 리눅스에서 프로세스를 식별하기 위해 사용되는 값
// 일반적으로 0~32767 사이의 값을 사용

# if 0
int main(void) {
	
	pid_t pid = getpid();
	printf("pid: %d\n", pid);
	exit(0);
}
#endif


// 리눅스는 기존의 프로세스를 복제해서 새로운 프로세스를 생성
// 부모프로세스 : fork()를 호출한 프로세스
// 자식프로세스 : fork()에 의해 생성된 프로세스

// 자식프로세스는 부모프로세스의 대부분의 속성들을 복제하는데 안하는것이
// 1. 자식프로세스의 아이디
// 2. 자식프로세스의 부모아이디는 부모프로세스의 아이디가 됨
// 3. 자식 프로세스의 리소스 통계값은 모두 0으로 초기화됨
// 4. 파일락
// 5. 부모 프로세스의 시그널 처리 동작은 자식에게 상속되지만 
// 대기중(pending)인 시그널은 사라짐

#if 1
int main(void) {

	// fork()의 리턴값을 통해 부모, 자식 프로세스를 구분
	pid_t pid = fork();

	// parent process
	if (pid > 0) {

	}
	// child process
	else if (pid == 0) {

	}
	else {
		perror("fork");
		exit(1);
	}

	exit(0);
}
#endif


// 프로세스의 종료
// 정상종료 : exit or main함수의 반환(exit(main()));
//			: _exit(exit내부에서 호출되는 syscall)

// 비정상종료 : abort함수 호출(SIGABRT 시그널)
// 			  : 커널이 발생한 시그널 ex) 0으로 나눈 경우, 잘못된 메모리 참조

// 프로세스의 종료 처리
// 1. 프로세스가 연 파일을 모두 닫음
// 2. 프로세스가 사용한 메모리를 모두 가용 메모리 풀(pool)로 반환
// 3. exit함수는 표준 입출력 정리 루틴을 실행하고 _exit를 호출함
// 	  (열린 파일 스트림에 대하여 fclose()로 버퍼에 남은 데이터를 flush함)
// 4. _exit함수는 종료상태값은 부모에게 전달함


