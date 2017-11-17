#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include<sys/stat.h>
#include<string.h>
typedef unsigned int  uint_t;

int main(int argc,char *argv[]) {
	int msg_len = 0;
	struct mq_attr attr;
	mqd_t	mqd;
	// void    *ptr;
	//char str[30] = "かいせき";
	//size_t	len;
	uint_t	prio = 0;
	if (argc != 3) {
		printf("usage: mqsend <name> <message>\n");
		exit(0);
	}

	if ((mqd = mq_open(argv[1],O_WRONLY)) == -1) {
		perror("error");
		exit(errno);
	}

	mq_getattr(mqd,&attr);

	msg_len = strlen(argv[2]);

	if ( msg_len > attr.mq_msgsize) {
		perror("error:");
		exit(-1);
	}

	if (mq_send(mqd,argv[2],msg_len,prio) == -1) {
		perror("error: mq_send: ");
		exit(errno);
	}
	mq_close(mqd);
	exit(0);
}
