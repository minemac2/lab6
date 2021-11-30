all: lab6 q1 q2 final

lab6: lab6.c
	gcc -c lab6.c

q1: q1.c
	gcc -c q1.c

q2: q2.c
	gcc -c q2.c

final: 
	gcc lab6.o q1.o q2.o

clean: 
	rm -f lab6.o q1.o q2.o a.out
