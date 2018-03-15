program: thomas.o
	gcc -o program thomas.o

thomas.c: thomas.c headers.h
	gcc -c thomas.c

clean:
	rm -f*.o program