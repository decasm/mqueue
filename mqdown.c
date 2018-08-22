#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

/*
 * Bring down (close) a message queue
 */
int main(int argc,char *argv[]) {
	int c;
	if (2 != argc) {
		printf("usage: mqdown <name>\n");
		exit(1);
	}
	// delete the queue
	if ((c = mq_unlink(argv[1])) == -1) {
		perror("error");
		exit(errno);
	}
	exit(0);
}
