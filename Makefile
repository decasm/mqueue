
PACKAGE=mqueue
VERSION=1.1
PACKAGEDIR=$(PACKAGE)-$(VERSION)
BINS=mqup mqdown mqsend mqrcv mqwaiting mqexists

PREFIX ?= /usr

all:$(BINS)

mqup: mqup.c
	gcc -Wall -o mqup mqup.c -lrt

mqdown: mqdown.c
	gcc -Wall -o mqdown mqdown.c -lrt

mqsend: mqsend.c
	gcc -Wall -o mqsend mqsend.c -lrt

mqrcv: mqrcv.c
	gcc -Wall -o mqrcv mqrcv.c -lrt

mqwaiting: mqwaiting.c
	gcc -Wall -o mqwaiting mqwaiting.c -lrt

mqexists: mqexists.c
	gcc -Wall -o mqexists mqexists.c -lrt

install: all
	install -d "$(DESTDIR)$(PREFIX)/bin"
	install -m755 -t "$(DESTDIR)$(PREFIX)/bin" $(BINS)
	install -d "$(DESTDIR)$(PREFIX)/share/mqueue"
	install -m644 -t "$(DESTDIR)$(PREFIX)/share/mqueue" monitor.example sendqueue.example

dist:
	rm -rf dist
	mkdir -p dist/$(PACKAGEDIR)
	cp *.c monitor.example sendqueue.example README.md Makefile dist/$(PACKAGEDIR)
	tar -zcvf dist/$(PACKAGEDIR).tgz -C dist $(PACKAGEDIR)

clean:
	rm -fr *~ $(BINS) dist

