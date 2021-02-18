#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// C표준 라이브러리는 파이프를 사용하여 서로 다른 프로세스의 통신을 
// 쉽게 할 수 있도록 popen()를 제공함
int main(int argc, char **argv) {
	
	if (argc != 3) {
		fprintf(stderr, "usage: %s cmd1 cmd2\n", *argv);
		exit(1);
	}

	const char *cmd1 = argv[1];
	const char *cmd2 = argv[2];

	FILE *src = popen(cmd1, "r");
	if (src == NULL) {
		perror("popen");
		exit(1);
	}

	FILE *dst = popen(cmd2, "w");
	if (dst == NULL) {
		perror("popen");
		exit(1);
	}

	char buf[BUFSIZ];
	while (1) {
		if (fgets(buf, sizeof(buf), src) == NULL) {
			if (ferror(src)) {
				perror("fgets");
				exit(1);
			}
			else if (feof(src)) {
				break;
			}
		}
		fputs(buf, dst);
	}

	return 0;
}
