ALL: main

main: main.o logtree.o
	gcc main.o logtree.o -o main

main.o: main.c logtree.c logtree.h
	gcc -c main.c

logtree.o: logtree.c logtree.h
	gcc -c logtree.c

clean:
	rm -f *.o main