#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s FILENAME\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	struct stat sb;
	if (lstat(*argv, &sb) < 0) {
		perror("lstat");
		exit(1);
	}

	// epoch : 유닉스 타임. '1970년 1월 1일 0시 0분'부터 
	// 오늘까지의 시간을 초로 환산해서 나타낸 값
	printf("%lu\n", sb.st_mtime);

	// yyyy-MM-dd hh:mm:ss
	char mtime[32];
	struct tm *t = localtime(&sb.st_mtime);
	sprintf(mtime, "%04d-%02d-%02d %02d:%02d:%02d",
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec);

	printf("%s\n", mtime);
	
	exit(0);
}

