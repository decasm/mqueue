#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
typedef unsigned int  uint_t;

/*
 * Determine if message queue is up
 * Return 0 if queue is up, print message
 * Return -1 if queue is not up, print message
 */
int main(int argc,char *argv[]) {
	mqd_t	mqd;

	if (2 != argc) {
		printf("usage: mqexists <name>\n");
		exit(1);
	}

	if ( (mqd = mq_open(argv[1],O_RDONLY)) == -1 ) {
		perror("error");
		exit(errno);
	}

	// if mq_open returns -1 without the O_CREAT flag, the queue does not exist
	if ( mqd == -1 ) {
		printf("no - '%s' is not up\n", argv[1]);
		exit(2);
	}

	// otherwise it does exist
	printf("ok - '%s' is up\n", argv[1]);
	mq_close(mqd);
	exit(0);
}
