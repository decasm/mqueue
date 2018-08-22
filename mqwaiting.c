#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include<sys/stat.h>
#include <string.h>
typedef unsigned int  uint_t;

/*
 * Print the number of messages waiting in the queue
 */
int main(int argc,char *argv[]) {
	mqd_t	mqd;
	struct mq_attr attr;

	if (2 != argc) {
		printf("usage: mqwaiting <name>\n");
		exit(1);
	}

	if ( (mqd = mq_open(argv[1],O_RDONLY)) == -1 ) {
		perror("error");
		exit(errno);
	}

	// get attributes and print number of messages
	mq_getattr(mqd,&attr);
	printf("%ld\n", attr.mq_curmsgs);

	mq_close(mqd);
	exit(0);
}
