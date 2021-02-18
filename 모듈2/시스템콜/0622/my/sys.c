#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void mysystem(const char *command) {
	
	if (command == NULL) {
		fprintf(stderr, "system: argument is null\n");
		return;
	}

	char cmd[256] = {0,};
	strcpy(cmd, command);

	char exe[32];
	char *res = strtok(cmd, " ");
	strcpy(exe, res);

	int i;
	char *cmdbuf[32];
	cmdbuf[0] = res;
	for (i = 1; res != NULL; i++) {
		res = strtok(NULL, " ");
		cmdbuf[i] = res;
	}
	cmdbuf[i] = (char*)NULL;

	pid_t pid = fork();
	if (pid > 0) {
		waitpid(pid, NULL, 0);
	}
	else if (pid < 0) {
		perror("fork");
		exit(1);
	}
	else if (pid == 0) {
		execvp(exe, cmdbuf);
		exit(0);
	}
}


int main() {
	mysystem("mkdir a b");
	mysystem("clear");
	return 0;
}
