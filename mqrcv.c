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
 * Receive a message from a message queue.
 * Pass "-n" to prevent blocking (NON_BLOCK)
 *     and have program exit if there is no message.
 */
int main(int argc,char *argv[]) {
	int		c,flags;
	mqd_t	mqd;
	ssize_t n;
	uint_t	prio;
	void *buff;

	struct mq_attr attr;
   
	flags = O_RDONLY;
	while ((c = getopt(argc,argv,"n")) != -1) {
		switch (c) {
			case 'n':
				flags |= O_NONBLOCK;
				break;
		}
	}
	if (optind != argc-1) {
		printf("usage: mqrcv [-n] <name>\n");
		exit(1);
	}
	if ( (mqd = mq_open(argv[optind],flags)) == -1 ) {
		perror("error");
		exit(errno);
	}
	mq_getattr(mqd,&attr);

	// allocate memory for message using size from attributes
	buff = malloc(attr.mq_msgsize);

	if((n = mq_receive(mqd,buff,attr.mq_msgsize,&prio)) == -1) {
		// EAGAIN means queue was empty, but O_NONBLOCK was set.
		// if EAGAIN, skip and exit normal
		// otherwise print error and non-normal exit
		if ( errno != EAGAIN ) {
			perror("error: ");
			exit(errno);
		}
		exit(0); // normal exit 
	}

	// print the message
	printf("%s\n", (char *)buff);
	free(buff);

	mq_close(mqd);
	exit(0);
}
