// 사람의 이름과 나이를 저장하는 코드를 구현

# if 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct Person {
	char name[32];
	int age;
}Person;


// 현재 코드의 단점은 파일의 입출력에 대하여 버퍼 입출력과 빈번한
// 함수 호출로 인해 성능이 떨어질 수 있다는 것임

int dumpFile(const char *fname) {

	if (fname == NULL) {
		fprintf(stderr, "dumpFile: argument is null\n");
		return -1;
	}

	int fd = open(fname, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	Person buf;
	while (1) {
		ssize_t nRead = read(fd, &buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		else {
			printf("name: %s, age: %d\n", buf.name, buf.age);
		}
	}

	close(fd);
	return 0;
}


int writePerson(const char *fname, Person *person) {
	
	if (fname == NULL || person == NULL) {
		fprintf(stderr, "writePerson: argument is null\n");
		return -1;
	}

	int fd = open(fname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	if (write(fd, person, sizeof(Person)) < 0) {
		perror("write");
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s FILENAME\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	Person arr[] = {
		{"a", 10},
		{"b", 20},
		{"c", 30},
		{"d", 40},
	};

	for (int i = 0; i < 4; i++) {
		writePerson(*argv, &arr[i]);
	}

	dumpFile(*argv);

	exit(0);
}
#endif



// 이를 해결하기위해 nmap()를 활용
// 파일에 대하여 nmap()을 사용하면 참조계수가 1 증가함
// 따라서 close()를 하더라도 파일이 유지됨
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef struct Person {
	char name[32];
	int age;
}Person;


off_t getFileSize(int fd) {
	
	if (fd < 0) {
		fprintf(stderr, "getFileSize: fd is wrong\n");
		return -1;
	}

	off_t oldPos = lseek(fd, 0, SEEK_CUR);
	if (oldPos == -1) {
		perror("lseek");
		return -1;
	}

	off_t fsize = lseek(fd, 0, SEEK_END);
	if (fsize == -1) {
		perror("lseek");
		return -1;
	}

	if (lseek(fd, oldPos, SEEK_SET) == -1) {
		perror("lseek");
		return -1;
	}

	return fsize;
}


int dumpFile(const char *fname) {

	if (fname == NULL) {
		fprintf(stderr, "dumpFile: argument is null\n");
		return -1;
	}

	int fd = open(fname, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	long fsize = getFileSize(fd);
	if (fsize < 0) {
		close(fd);
		return -1;
	}

	Person *p = mmap(NULL, fsize, PROT_READ, MAP_PRIVATE, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		close(fd);
	}

	for (int i = 0; i < (fsize/sizeof(Person)); i++) {
		printf("name: %s, age: %d\n", p[i].name, p[i].age);
	}

	if (munmap(p, fsize) == -1) {
		perror("munmap");
		exit(1);
	}

	close(fd);
	return 0;
}


int writePerson(const char *fname, Person *person) {
	
	if (fname == NULL || person == NULL) {
		fprintf(stderr, "writePerson: argument is null\n");
		return -1;
	}

	int fd = open(fname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	if (write(fd, person, sizeof(Person)) < 0) {
		perror("write");
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s FILENAME\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	Person arr[] = {
		{"a", 10},
		{"b", 20},
		{"c", 30},
		{"d", 40},
	};

	for (int i = 0; i < 4; i++) {
		writePerson(*argv, &arr[i]);
	}

	dumpFile(*argv);

	exit(0);
}
