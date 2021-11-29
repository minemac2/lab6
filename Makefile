all: lab6 q final

lab6: lab6.c
	gcc -c lab6.c

q: q.c
	gcc -c q.c

final: 
	gcc lab6.o q.o




clean: 
	rm -f lab6.o q.o a.out
