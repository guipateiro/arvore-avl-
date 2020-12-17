CFLAGS = -Wall
LDFLAGS = -lm

all: gustavo

run1: gustavo
	./avl

run2:guilherme
	./avl		

gustavo: main1.o avl1.o
	gcc -o avl main.o avl.o $(CFLAGS) $(LDFLAGS)

main1.o: main.c avl.h
	gcc -c main.c $(CFLAGS)

avl1.o: avl.c avl.h
	gcc -c avl.c $(CFLAGS)

guilherme: main2.o avl2.o
	gcc -o avl main.o arvoreavl.o $(CFLAGS) $(LDFLAGS)

main2.o: main.c arvoreavl.h
	gcc -c main.c $(CFLAGS)

avl2.o: arvoreavl.c arvoreavl.h
	gcc -c arvoreavl.c $(CFLAGS)	

clean:
	-rm -f *~ *.o
	
purge: clean
	-rm -f mosaico
