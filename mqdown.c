#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc,char *argv[]) {
	int c;
	if (1 != argc-1) {
		printf("usage: mqdown <name>\n");
		exit(0);
	}
	if ((c = mq_unlink(argv[1])) == -1) {
		perror("error");
		exit(-1);
	}
	exit(0);
}
