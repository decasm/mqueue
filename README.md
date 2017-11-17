mqueue
======
Simple demo of Posix message queues.

All queue names must start with a '/'

mqup.c: create queue
	usage: mqup [-e] <qname>
		-e: (exclusive) fail if <qname> already exists

mqdown.c: destroy queue
	usage: mqdown <qname>

mqsend.c: send message
	usage: mqsend <qname> <message>

mqrcv.c: receive message
	usage: mqrcv [-n] <qname>
		-n: Nonblocking - exit if no message available

mqlen.c: print number of message in queue
	usage: mqlen <qname>

