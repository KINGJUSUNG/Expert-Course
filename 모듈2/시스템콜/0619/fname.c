#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


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

	if (S_ISLNK(sb.st_mode)) {
		char symlink[256];
		ssize_t ret = readlink(*argv, symlink, sizeof(symlink));
		symlink[ret] = '\0';
		printf("%s -> %s\n", *argv, symlink);
	}
	else {
		printf("%s\n", *argv);
	}

	exit(0);
}

