#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include<sys/stat.h>
#include<string.h>
typedef unsigned int  uint_t;

/* Send a message to a message queue */

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
		exit(0);
	}
	mqd = mq_open(argv[1],O_WRONLY);
	if ( mqd == -1 ) {
		printf("messague queue '%s' does not exist\n", argv[optind]);
		exit(-1);
	}
	mq_getattr(mqd,&attr);
	//printf("messages in queue = %ld\n", attr.mq_curmsgs);

	msg_len = strlen(argv[optind+1]);

	if ( msg_len > attr.mq_msgsize) {
		printf("error: message length greater than max message length(%ld)\n", attr.mq_msgsize);
		exit(-1);
	}

	if (mq_send(mqd,argv[optind+1],msg_len,prio) == -1) {
		perror("error :");
		exit(-2);
	}
	mq_close(mqd);
	exit(0);
}
