#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
	int pfd[2];
	if (pipe(pfd) < 0) {
		perror("pipe");
		exit(1);
	}
}

