#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// exec류 함수들은 다른 프로세스를 실행시킬 때 현재 프로세스 메모리공간에 
// 기계어 코드를 덮어 써버림. 따라서 원래 프로세스는 사라짐

// 1) execl() : 마지막 l은 list의 약자
//			  : 실행할 명령행의 인자를 리스트 형태로 전달
// 			  : 경로는 반드시 상대경로나 절대경로를 사용해야함

#if 1
int main() {
	if (execl("./test", "test", "hello", "world", (char*)NULL) == -1) {
		perror("execl");
	}
	printf("dead code..\n");
	return 0;
}
#endif

// 2) execv()
#if 0
int main() {
	char *args[] = {"test", "hello", "world", (char*)NULL};
	if (execv("./test", args) == -1) {
		perror("execv");
	}
	printf("dead code..\n");
	return 0;
}
#endif

// 3) execlp
// 4) execvp
// execl, execv와 동일하지만 다른점이 있다면 path로부터 명령어를 찾음
// int main() {
// 	execlp("vim", "vim", "./test.c", (char *)NULL);
// 	return 0;
// }
