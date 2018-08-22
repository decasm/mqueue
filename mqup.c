#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

/* Permissions set to 644 */
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

/*
 * Bring up (open) a message queue.
 */
int main(int argc,char *argv[]) {
	int		c,flags;
	mqd_t	mqd;
	struct mq_attr *attr;

	flags = O_RDWR|O_CREAT;
	while ((c = getopt(argc,argv,"e")) != -1) {
		switch (c) {
			case 'e':
				flags |= O_EXCL;
				break;
		}
	}
	if (optind != argc-1) {
		printf("usage: mqup [-e] <name>\n");
		exit(1);
	}

	// set max number messages and max size (bytes) per message
	// these are the system defaults, this is a placeholder for changing them later
	attr = malloc(sizeof(*attr));
	attr->mq_maxmsg = 10l;
	attr->mq_msgsize = 8192l;

	// create the queue
	if ((mqd = mq_open(argv[optind],flags,FILE_MODE,attr)) == -1) {
		perror("error");
		exit(errno);
	}

	// get and print queue attributes
	mq_getattr(mqd,attr);
	printf("max #msgs = %ld,max #bytes/msg = %ld,#currently on queue = %ld\n",
		   attr->mq_maxmsg,attr->mq_msgsize,attr->mq_curmsgs);

	mq_close(mqd);
	exit(0);
}
