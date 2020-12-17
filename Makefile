CFLAGS = -Wall
LDFLAGS = -lm

all: mosaico

gustavo: main.o avl.o
	gcc -o avl main.o avl.o $(CFLAGS) $(LDFLAGS)

main.o: main.c avl.h
	gcc -c main.c -o main.o $(CFLAGS)

avl.o: avl.c avl.h
	gcc -c avl.c $(CFLAGS)

guilherme: arvoreavl.c
	gcc -o arvoreavl arvoreavl.c $(CFLAGS)

clean:
	-rm -f *~ *.o
	
purge: clean
	-rm -f mosaico
