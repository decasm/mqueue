#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

/* Bring down (close) a message queue */

int main(int argc,char *argv[]) {
	int c;
	if (2 != argc) {
		printf("usage: mqdown <name>\n");
		exit(0);
	}
	if ((c = mq_unlink(argv[1])) == -1) {
		perror("error");
		exit(-1);
	}
	exit(0);
}
