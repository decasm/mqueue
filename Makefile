
all:mqup mqdown mqsend mqrcv mqlen

mqup: mqup.c
	gcc -Wall -o mqup mqup.c -lrt

mqdown: mqdown.c
	gcc -Wall -o mqdown mqdown.c -lrt

mqsend: mqsend.c
	gcc -Wall -o mqsend mqsend.c -lrt

mqrcv: mqrcv.c
	gcc -Wall -o mqrcv mqrcv.c -lrt

mqlen: mqlen.c
	gcc -Wall -o mqlen mqlen.c -lrt

clean:
	rm -f *~ mq{up,down,send,rcv,len}

