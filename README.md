mqueue
======
Simple demo of Posix message queues.

Queue names must start with a '/'

mqup.c: create queue
	usage: mqup [-e] <name>
		-e: fail if <name> already exists;

mqsend.c: send message
	usage: mqsend <name> <message>

mqrcv.c: receive message
	usage: mqrcv [-n] <name>
		-n: Nonblocking - fail if no message available

mqwaiting.c: print the number of messages waiting in a queue
	usage: mqwaiting <name>

mqexists.c: does message queue exist
	usage: mqexists <name>
		exit(0) if it does
		exit(-1) it it does not
		prints a message to stdout either way

mqdown.c: destroy queue
	usage: mqdown <name>



Message queues have max and default limits. They can be seen in
/proc/sys/fs/mqueue. You can use sysctl to change them or just echo.
You can make changes permanent using /etc/sysctl.conf.

* /proc/sys/fs/mqueue/msg\_default -> default max messages in a queue (10)
* /proc/sys/fs/mqueue/msg\_max -> system max number of messages in a queue (10)
* /proc/sys/fs/mqueue/msgsize\_default -> default max message size (8192)
* /proc/sys/fs/mqueue/msgsize\_max -> system max message size (8192)


