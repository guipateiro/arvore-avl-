CFLAGS = -Wall
LDFLAGS = -lm

all: avl 

avl: main.o arvoreavl.o
	gcc -o myavl main.o arvoreavl.o $(CFLAGS) $(LDFLAGS) -g

main.o: main.c arvoreavl.h
	gcc -c main.c $(CFLAGS)

aroreavl.o: arvoreavl.c arvoreavl.h
	gcc -c arvoreavl.c $(CFLAGS)	

clean:
	-rm -f *~ *.o
	
purge: clean
	-rm -f myavl
