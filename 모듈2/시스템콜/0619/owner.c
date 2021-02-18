#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>


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

	printf("uid: %d\n", sb.st_uid);
	printf("gid: %d\n", sb.st_gid);

	struct passwd *pswd = getpwuid(sb.st_uid);
	if (pswd == NULL) {
		perror("getpwuid");
		exit(1);
	}

	struct group *grp = getgrgid(sb.st_gid);
	if (grp == NULL) {
		perror("getgrgid");
		exit(1);
	}

	printf("%s %s\n", pswd->pw_name, *argv);
	printf("%s %s\n", grp->gr_name, *argv);

	exit(0);
}

