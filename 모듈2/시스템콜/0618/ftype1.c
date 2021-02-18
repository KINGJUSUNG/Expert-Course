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
	
	switch (sb.st_mode & S_IFMT) {
		case S_IFBLK:  printf("block device\n");            break;
		case S_IFCHR:  printf("character device\n");        break;
		case S_IFDIR:  printf("directory\n");               break;
		case S_IFIFO:  printf("FIFO/pipe\n");               break;
		case S_IFLNK:  printf("symlink\n");                 break;
		case S_IFREG:  printf("regular file\n");            break;
		case S_IFSOCK: printf("socket\n");                  break;
		default:       printf("unknown?\n");                break;
	}

	exit(0);
}
