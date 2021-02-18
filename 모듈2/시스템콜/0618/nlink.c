#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


// ./a.out hello.txt
int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	struct stat sb = {0,};
	if (lstat(*argv, &sb) < 0) {
		perror("lstat");
		exit(1);
	}

	printf("연결계수 : %ld\n", sb.st_nlink);
	exit(0);
}

