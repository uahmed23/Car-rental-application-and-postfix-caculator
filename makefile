CFLAGS = -Wall -std=c99 -pedantic

all: q1 q2

q1: q1.c a2.h lists.o
	gcc $(CFLAGS) -include a2.h -c q1.c
	gcc $(CFLAGS) lists.o q1.o -o q1

q2: q2.c a2.h stacks.o
	gcc $(CFLAGS) -include a2.h -c q2.c
	gcc $(CFLAGS) stacks.o q2.o -o q2

lists.o: lists.c a2.h
	gcc $(CFLAGS) -include a2.h -c lists.c -o lists.o

stacks.o: stacks.c a2.h
	gcc $(CFLAGS) -include a2.h -c stacks.c -o stacks.o

clean:rm -i *.o
