ALL: main

main: main.o logtree.o fila_fifo.o escalonador.o
	gcc main.o logtree.o fila_fifo.o escalonador.o -o main

main.o: main.c logtree.c logtree.h fila_fifo.c fila_fifo.h escalonador.c escalonador.h
	gcc -c main.c

escalonador.o: escalonador.c escalonador.h fila_fifo.c fila_fifo.h logtree.c logtree.h
	gcc -c escalonador.c

logtree.o: logtree.c logtree.h
	gcc -c logtree.c

fila_fifo.o: fila_fifo.c fila_fifo.h
	gcc -c fila_fifo.c

clean:
	rm -f *.o main