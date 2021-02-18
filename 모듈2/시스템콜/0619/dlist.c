#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s DIRECTORY\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	DIR *dir = opendir(*argv);
	if (dir == NULL) {
		perror("opendir");
		exit(1);
	}

	// 디렉토리의 요소들을 가리킴
	struct dirent *p = readdir(dir);
	if (p) {
		printf("%s\n", p->d_name);
	}

	if (closedir(dir) < 0) {
		perror("closedir");
		exit(1);
	}

	exit(0);
}
#endif


#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s DIRECTORY\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	DIR *dir = opendir(*argv);
	if (dir == NULL) {
		perror("opendir");
		exit(1);
	}

	// 현재 디렉토리에 있는 내용을 읽어오기
	while (1) {
		errno = 0;
		struct dirent *p = readdir(dir);
		if (p == NULL) {
			if (errno != 0) {
				perror("readdir");
				exit(1);
			}
			else {
				break;
			}
		}
		printf("%s\n", p->d_name);
	}

	if (closedir(dir) < 0) {
		perror("closedir");
		exit(1);
	}

	exit(0);
}
#endif


# if 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>


int listDir(const char *dname) {

	if (dname == NULL || strlen(dname) == 0) {
		fprintf(stderr, "listDir: argument is null\n");
		return -1;
	}

	// 1. 해당 디렉터리로 이동
	if (chdir(dname) < 0) {
		perror("chdir");
		return -1;
	}

	// 2. 해당 디렉터리 경로 출력
	char curPath[256];
	if (getcwd(curPath, sizeof(curPath)) == NULL) {
		perror("getcwd");
		return -1;
	}
	printf("\n%s\n", curPath);

	// 3. 해당 디렉터리를 오픈
 	DIR *dir = opendir(".");
 	if (dir == NULL) {
 		perror("opendir");
		return -1;
 	}
 
	// 4. 디렉터리 안의 내용을 출력
 	while (1) {
 		errno = 0;
 		struct dirent *p = readdir(dir);
 		if (p == NULL) {
 			if (errno != 0) {
 				perror("readdir");
				return -1;
 			}
 			else {
 				break;
 			}
 		}

		// 중요함!!!
		if (strcmp(p->d_name, ".") && strcmp(p->d_name, "..")) {
			printf("%s\n", p->d_name);
			
			if (p->d_type == DT_DIR) {
				if (listDir(p->d_name) == -1) {
					fprintf(stderr, "listDir error\n");
					break;
				}
			}
		}
	}

	// 5. 현재 디렉터리를 닫고 상위 디렉토리로 이동
 	if (closedir(dir) < 0) {
 		perror("closedir");
		return -1;
 	}

	if (chdir("..") == -1) {
		perror("chdir");
		exit(1);
	}

	return 0;
}


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s DIRECTORY\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	listDir(*argv);

	exit(0);
}
#endif


#if 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

typedef struct Node {
	char dname[256];
	struct Node *next;
}Node;


int insert(Node *head, const char *dname) {

	if (head == NULL || dname == NULL) {
		fprintf(stderr, "insert: argument is null\n");
		return -1;
	}

	Node *node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("calloc");
		return -1;
	}
	strcpy(node->dname, dname);

	node->next = head->next;
	head->next = node;
	return 0;
}


int listDir(const char *dname) {

	if (dname == NULL || strlen(dname) == 0) {
		fprintf(stderr, "listDir: argument is null\n");
		return -1;
	}

	// 1. 해당 디렉터리로 이동
	if (chdir(dname) < 0) {
		perror("chdir");
		return -1;
	}

	// 2. 해당 디렉터리 경로 출력
	char curPath[256];
	if (getcwd(curPath, sizeof(curPath)) == NULL) {
		perror("getcwd");
		return -1;
	}
	printf("\n%s\n", curPath);

	// 3. 해당 디렉터리를 오픈
 	DIR *dir = opendir(".");
 	if (dir == NULL) {
 		perror("opendir");
		return -1;
 	}

	// 연결 리스트의 더미 헤드
	Node head = {0,};

	// 4. 디렉터리 안의 내용을 출력
 	while (1) {
 		errno = 0;

		// 내부적으로 offset을 가지고 있음
 		struct dirent *p = readdir(dir);
 		if (p == NULL) {
 			if (errno != 0) {
 				perror("readdir");
				return -1;
 			}
 			else {
 				break;
 			}
 		}

		// 중요함!!!
		if (strcmp(p->d_name, ".") && strcmp(p->d_name, "..")) {
			printf("%s\n", p->d_name);

			// 우선 디렉터리의 모든 파일을 먼저 찍은 뒤
			// 서브 디렉터리들 안의 파일을 출력
			if (p->d_type == DT_DIR) {
				insert(&head, p->d_name);
			}
		}
	}

	// 5. 하위 디렉터리 순회
	while (head.next != NULL) {
		Node *target = head.next;
		head.next = target->next;

		if (listDir(target->dname) == -1) {
			exit(1);
		}
		free(target);
	}

	// 6. 현재 디렉터리를 닫고 상위 디렉토리로 이동
 	if (closedir(dir) < 0) {
 		perror("closedir");
		return -1;
 	}

	if (chdir("..") == -1) {
		perror("chdir");
		exit(1);
	}

	return 0;
}


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s DIRECTORY\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	listDir(*argv);

	exit(0);
}
#endif


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>


int listDir(const char *dname) {

	if (dname == NULL || strlen(dname) == 0) {
		fprintf(stderr, "listDir: argument is null\n");
		return -1;
	}

	// 1. 해당 디렉터리로 이동
	if (chdir(dname) < 0) {
		perror("chdir");
		return -1;
	}

	// 2. 해당 디렉터리 경로 출력
	char curPath[256];
	if (getcwd(curPath, sizeof(curPath)) == NULL) {
		perror("getcwd");
		return -1;
	}
	printf("\n%s\n", curPath);

	// 3. 해당 디렉터리를 오픈
 	DIR *dir = opendir(".");
 	if (dir == NULL) {
 		perror("opendir");
		return -1;
 	}

	// 4. 디렉터리 안의 내용을 출력
 	while (1) {
 		errno = 0;

		// 내부적으로 offset을 가지고 있음
 		struct dirent *p = readdir(dir);
 		if (p == NULL) {
 			if (errno != 0) {
 				perror("readdir");
				return -1;
 			}
 			else {
 				break;
 			}
 		}

		// 중요함!!!
		if (strcmp(p->d_name, ".") && strcmp(p->d_name, "..")) {
			printf("%s\n", p->d_name);
		}
	}

	// 5. 하위 디렉터리 순회
	rewinddir(dir);
	while (1) {
		errno = 0;
		struct dirent *p = readdir(dir);
		if (p == NULL) {
			if (errno != 0) {
				perror("readdir");
				return -1;
			}
			else {
				break;
			}
		}

		if (p->d_type == DT_DIR) {
			if (strcmp(p->d_name, ".") && strcmp(p->d_name, "..")) {
				if (listDir(p->d_name) == -1) {
					exit(1);
				}
			}
		}
	}

	// 6. 현재 디렉터리를 닫고 상위 디렉토리로 이동
	if (closedir(dir) < 0) {
 		perror("closedir");
		return -1;
 	}

	if (chdir("..") == -1) {
		perror("chdir");
		exit(1);
	}

	return 0;
}


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s DIRECTORY\n", *argv);
		exit(1);
	}

	--argc;
	++argv;

	listDir(*argv);

	exit(0);
}

