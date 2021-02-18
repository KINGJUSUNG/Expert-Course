#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


// ./a.out a.txt
// ls -l a.txt
// -rw-r--r-- 1 linux linux 309 Jun 19 11:16 ex1.c

int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	struct stat sb;
	if (lstat(*argv, &sb) < 0) {
		perror("lstat");
		exit(1);
	}

	char lsbuf[128] = {0,};

	char perm[] = "----------";
	char rwx[] = "rwx";

	for (int i = 0; i < 9; i++) {
		if ((sb.st_mode >> (8-i)) & 0x1) {
			perm[i+1] = rwx[i%3];
		}
	}
	
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

	char mtime[32];
	struct tm *t = localtime(&sb.st_mtime);
	sprintf(mtime, "%04d-%02d-%02d %02d:%02d:%02d",
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec);

	sprintf(lsbuf, "%s %ld %s %s %ld %s %s\n",
			perm, sb.st_nlink,pswd->pw_name, grp->gr_name, sb.st_size, mtime, *argv);

	printf("%s\n", lsbuf);
	exit(0);
}
