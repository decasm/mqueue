#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc,char *argv[]) {
	mqd_t	mqd;
	struct mq_attr	attr;
	if (optind != argc-1) {
		printf("usage: mqlen <name>\n");
		exit(0);
	}
	if ((mqd = mq_open(argv[optind],O_RDONLY)) == -1) {
		perror("error");
		exit(-1);
	}
	mq_getattr(mqd,&attr);
	printf("%ld\n",attr.mq_curmsgs);
	mq_close(mqd);
	exit(0);
}
