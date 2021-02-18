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

	// 코드를 개선해보시오
	// Trwxrwxrwx
	// char perm[11] = {0,};
	// perm[0] = ' ';

	// 	perm[1] = (sb.st_mode & S_IRUSR) ? 'r' : '-';
	// 	perm[2] = (sb.st_mode & S_IWUSR) ? 'w' : '-';
	// 	perm[3] = (sb.st_mode & S_IXUSR) ? 'x' : '-';
	// 
	// 	perm[4] = (sb.st_mode & S_IRGRP) ? 'r' : '-';
	// 	perm[5] = (sb.st_mode & S_IWGRP) ? 'w' : '-';
	// 	perm[6] = (sb.st_mode & S_IXGRP) ? 'x' : '-';
	// 
	// 	perm[7] = (sb.st_mode & S_IROTH) ? 'r' : '-';
	// 	perm[8] = (sb.st_mode & S_IWOTH) ? 'w' : '-';
	// 	perm[9] = (sb.st_mode & S_IXOTH) ? 'x' : '-';

	char perm[] = "----------";
	char rwx[] = "rwx";

	for (int i = 0; i < 9; i++) {
		if ((sb.st_mode >> (8-i)) & 0x1) {
			perm[i+1] = rwx[i % 3];
		}
	}

	printf("%s\n", perm);
	exit(0);
}

