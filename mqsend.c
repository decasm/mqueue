#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include<sys/stat.h>
#include<string.h>
typedef unsigned int  uint_t;

/*
 * Send a message to a message queue
 */
int main(int argc,char *argv[]) {
	int msg_len = 0,c;
	struct mq_attr attr;
	mqd_t	mqd;
	uint_t	prio = 0;

	while ((c = getopt(argc,argv,"p:")) != -1) {
		switch (c) {
			case 'p':
				prio  = atoi(optarg);
				break;
		}
	}

	if (argc != 3 && argc != 5) {
		printf("usage: mqsend [-p priority] <name> <message>\n");
		exit(1);
	}

	if ( (mqd = mq_open(argv[optind],O_WRONLY)) == -1 ) {
		printf("messague queue '%s' does not exist\n", argv[optind]);
		exit(2);
	}

	// check the message size, ensure less than max message size
	mq_getattr(mqd,&attr);
	msg_len = strlen(argv[optind+1]);
	if ( msg_len > attr.mq_msgsize) {
		printf("error: message length greater than max message length(%ld)\n", attr.mq_msgsize);
		exit(3);
	}

	// send message
	if (mq_send(mqd,argv[optind+1],msg_len,prio) == -1) {
		perror("error :");
		exit(4);
	}
	mq_close(mqd);
	exit(0);
}
