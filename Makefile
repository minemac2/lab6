all: lab6 queue sortThread final

lab6: lab6.c
	gcc -c lab6.c

queue: queue.c
	gcc -c queue.c

sortThread: sortThread.c
	gcc -c sortThread.c

final: 
	gcc lab6.o queue.o sortThread.o

clean: 
	rm -f lab6.o queue.o a.out
