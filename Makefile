CFLAGS = -Wall
LDFLAGS = -lm

all: mosaico

gustavo: avl.c
	gcc -o avl avl.c $(CFLAGS) -g

guilherme: arvoreavl.c
	gcc -o arvoreavl arvoreavl.c $(CFLAGS)

clean:
	-rm -f *~ *.o
	
purge: clean
	-rm -f mosaico
