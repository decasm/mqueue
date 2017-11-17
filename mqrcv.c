#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include<sys/stat.h>
#include <string.h>
typedef unsigned int  uint_t;

int main(int argc,char *argv[]) {
	int		c,flags,errsv;
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
		exit(0);
	}
	mqd = mq_open(argv[optind],flags);
	mq_getattr(mqd,&attr);
	buff = malloc(attr.mq_msgsize);
	if((n = mq_receive(mqd,buff,attr.mq_msgsize,&prio)) == -1) {
		errsv = errno;
		if ( errsv != EAGAIN ) {
			perror("error: ");
			exit(-1);
		}
		exit(0);
	}

	//printf("read %ld bytes,priority = %u\n",(long) n,prio);
	printf("%s\n", (char *)buff);

	mq_close(mqd);
	exit(0);
}
